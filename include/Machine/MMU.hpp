#ifndef RVEMUX_MACHINE_MMU_HPP
#define RVEMUX_MACHINE_MMU_HPP

#include "Basic/Types.hpp"

#include <cstdio>
#include <elf.h>

namespace rvemux {

class MemManagerUnit {
public:
  static constexpr u64 GuestMemoryOffset = 0x0888'0000'0000ULL;

  static u64 toHost(u64 guestAddr) { return guestAddr + GuestMemoryOffset; }
  static u64 toGuest(u64 hostAddr) { return hostAddr - GuestMemoryOffset; }

  static u64 roundDown(u64 x, u64 k) { return x & (-k); }
  static u64 roundUp(u64 x, u64 k) { return (x + k - 1) & -k; }

public:
  void loadELF(const char *Program);

  u64 getEntry() const { return Entry; }
  u64 getHostAlloc() const { return HostAlloc; }
  u64 getGuestAlloc() const { return GuestAlloc; }
  u64 getBaseAddress() const { return BaseAddr; }

private:
  void loadSegment(const Elf64_Phdr &Phdr, FILE *Fp);

private:
  u64 Entry = 0x0;

  // [ ELF | HostAlloc ] --------------> [ ELF |-------|      ]
  //                         to guest          ^       ^
  //                                           |       |
  //                                          Base GuestAlloc
  u64 HostAlloc = 0x0;
  u64 GuestAlloc = 0x0;
  u64 BaseAddr = 0x0;
};

} // namespace rvemux

#endif // RVEMUX_MACHINE_MMU_HPP