#ifndef RVEMUX_MACHINE_MACHINE_HPP
#define RVEMUX_MACHINE_MACHINE_HPP

#include "Basic/Types.hpp"
#include "MMU.hpp"
#include "ProgramState.hpp"

namespace rvemux {

class Machine {
public:
  void loadProgram(const char *Program);

  u64 getEntry() const { return MMU.getEntry(); }

private:
  MemManagerUnit MMU;
  ProgramState State;
};

} // namespace rvemux

#endif // RVEMUX_MACHINE_MACHINE_HPP