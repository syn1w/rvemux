#include "Machine/Machine.hpp"

#include "Basic/Error.hpp"

namespace rvemux {

void Machine::loadProgram(const char *Program) {
  MMU.loadELF(Program);

  State.PC = MMU.getEntry();
}

} // namespace rvemux