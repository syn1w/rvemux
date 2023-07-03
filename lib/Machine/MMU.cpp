#include "Machine/MMU.hpp"

#include "Basic/Error.hpp"

#include <cassert>
#include <cerrno>
#include <cstring>
#include <memory>
#include <sys/mman.h>
#include <unistd.h>

namespace rvemux {

static constexpr u64 GuestMemoryOffset = 0x0888'0000'0000ULL;

static u64 toHost(u64 guestAddr) { return guestAddr + GuestMemoryOffset; }
static u64 toGuest(u64 hostAddr) { return hostAddr - GuestMemoryOffset; }

static u64 roundDown(u64 x, u64 k) { return x & (-k); }
static u64 roundUp(u64 x, u64 k) { return (x + k - 1) & -k; }

static void checkRV64ELF(const Elf64_Ehdr *Ehdr) {
  // Check magic number
  const u8 *ELF64Ident = Ehdr->e_ident;
  if (ELF64Ident[EI_MAG0] != ELFMAG0 || ELF64Ident[EI_MAG1] != ELFMAG1 ||
      ELF64Ident[EI_MAG2] != ELFMAG2 || ELF64Ident[EI_MAG3] != ELFMAG3) {
    fatalf("bad elf file format");
  }

  if (ELF64Ident[EI_CLASS] != ELFCLASS64 || Ehdr->e_machine != EM_RISCV)
    fatalf("only riscv64 elf file is supported");
}

static void loadProgramHeader(Elf64_Phdr &Phdr, const Elf64_Ehdr *Ehdr,
                              Elf64_Half Idx, FILE *Fp) {
  const u64 Offset = Ehdr->e_phoff + Ehdr->e_phentsize * Idx;
  if (std::fseek(Fp, Offset, SEEK_SET) != 0)
    fatalf("seek file failed");

  static constexpr std::size_t SizeProgramHeader = sizeof(Elf64_Phdr);
  if (std::fread(&Phdr, 1, SizeProgramHeader, Fp) != SizeProgramHeader)
    fatalf("read program header failed: too small");
}

void MemManagerUnit::loadELF(const char *Program) {
  FILE *Fp = std::fopen(Program, "rb");
  if (!Fp)
    return;

  std::shared_ptr<void> X{nullptr, [Fp](void *) { std::fclose(Fp); }};

  static constexpr std::size_t SizeELF64Header = sizeof(Elf64_Ehdr);
  u8 Buf[SizeELF64Header];
  if (std::fread(Buf, 1, SizeELF64Header, Fp) != SizeELF64Header)
    fatalf("'%s' is not a valid elf64 file: too small");

  const Elf64_Ehdr *Ehdr = reinterpret_cast<const Elf64_Ehdr *>(Buf);
  checkRV64ELF(Ehdr);

  Entry = Ehdr->e_entry;

  // Load program header
  for (Elf64_Half Idx = 0; Idx < Ehdr->e_phnum; ++Idx) {
    Elf64_Phdr Phdr;
    loadProgramHeader(Phdr, Ehdr, Idx, Fp);

    // Program Header types: RISCV_ATTRIBUT/LOAD
    // We only load 'LOAD' program headers
    if (Phdr.p_type != PT_LOAD)
      continue;

    // Program Header:
    // Offset, VirtAddr, PhysAddr, FileSize, MemSize, Flags, Align

    loadSegment(Phdr, Fp);
  }
}

static int programFlagsToMmapProt(u32 Flags) {
  return (Flags & PF_R ? PROT_READ : 0) | (Flags & PF_W ? PROT_WRITE : 0) |
         (Flags & PF_X ? PROT_EXEC : 0);
}

void MemManagerUnit::loadSegment(const Elf64_Phdr &Phdr, FILE *Fp) {
  u64 Offset = Phdr.p_offset;
  u64 VirtAddr = toHost(Phdr.p_vaddr);
  u64 PageSize = getpagesize();
  u64 AlignedOffset = roundDown(Offset, PageSize);
  u64 AlignedAddr = roundDown(VirtAddr, PageSize);

  // The parameters addr and offset of mmap need page alignment
  //               Memory                      File
  //      +--+-------------------+             +--+
  //      |  | <- Phdr.FileSize  |             |  | <- Phdr.FileSize
  // V -> +--+                   |        O -> +--+
  //      |  |                FileSize         |  |
  //      |  | <- Diff(V - A)    |             |  | <- Diff (V - A)
  //      |  |                   |             |  |
  // A -> +--+-------------------+        A -> +--+
  //      |  |                                 |  |
  u64 FileSize = Phdr.p_filesz + (VirtAddr - AlignedAddr);
  u64 MemSize = Phdr.p_memsz + (VirtAddr - AlignedAddr);

  int Prot = programFlagsToMmapProt(Phdr.p_flags);

  int Fd = fileno(Fp);
  u64 Addr = (u64)mmap((void *)AlignedAddr, FileSize, Prot,
                       MAP_PRIVATE | MAP_FIXED, Fd, AlignedOffset);

  assert(Addr == AlignedAddr && "Addr must be equal to AlignedVirtAddr");

  u64 RemainingBSS = roundUp(MemSize, PageSize) - roundUp(FileSize, PageSize);
  if (RemainingBSS > 0) {
    // Allocate bss memory
    u64 AlignedBSSVirtAddr = AlignedAddr + roundUp(FileSize, PageSize);
    u64 BSSAddr = (u64)mmap((void *)AlignedBSSVirtAddr, RemainingBSS, Prot,
                            MAP_ANONYMOUS | MAP_PRIVATE | MAP_FIXED, -1, 0);
    assert(AlignedBSSVirtAddr == BSSAddr &&
           "BSSAddr must be equal to AlignedBSSVirtAddr");
  }

  HostAlloc = std::max(HostAlloc, (AlignedAddr + roundUp(MemSize, PageSize)));
  GuestAlloc = toGuest(HostAlloc);
  BaseAddr = GuestAlloc;
}

} // namespace rvemux