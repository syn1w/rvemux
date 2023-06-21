#ifndef RVEMUX_MACHINE_MMU_HPP
#define RVEMUX_MACHINE_MMU_HPP

#include "Basic/Types.hpp"

namespace rvemux {

class MemManagerUnit {
public:
  void loadELF(const char *Program);

  u64 getEntry() const { return Entry; }

private:
  u64 Entry = 0x0;
};

} // namespace rvemux

#endif // RVEMUX_MACHINE_MMU_HPP