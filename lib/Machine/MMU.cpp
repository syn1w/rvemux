#include "Machine/MMU.hpp"

#include "Basic/Error.hpp"

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <elf.h>
#include <memory>

namespace rvemux {

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

void MemManagerUnit::loadELF(const char *Program) {
  FILE *Fp = std::fopen(Program, "rb");
  if (!Fp)
    return;

  std::shared_ptr<void> X{nullptr, [Fp](void *) { std::fclose(Fp); }};

  static constexpr std::size_t SizeELF64Header = sizeof(Elf64_Ehdr);
  u8 Buf[SizeELF64Header];
  if (std::fread(Buf, 1, SizeELF64Header, Fp) != SizeELF64Header)
    fatalf("'%s' is not a valid elf64 file: too small");

  Elf64_Ehdr *Ehdr = reinterpret_cast<Elf64_Ehdr *>(Buf);
  checkRV64ELF(Ehdr);

  Entry = Ehdr->e_entry;
}

} // namespace rvemux