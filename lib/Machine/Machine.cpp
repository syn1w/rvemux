#include "Machine/Machine.hpp"

#include "Machine/Interpreter.hpp"

#include <cassert>
#include <memory>

namespace rvemux {

void Machine::loadProgram(const char *Program) {
  MMU.loadELF(Program);

  State.PC = MMU.getEntry();
}

ProgramState::ExitReasonKind Machine::step() {
  std::unique_ptr<Executor> TheExecutor =
      std::make_unique<InterpreteExecutor>();
  while (true) {
    TheExecutor->executeBlock(State);
    if (State.ExitReason == ProgramState::IndirectBranch ||
        State.ExitReason == ProgramState::DirectBranch)
      continue;

    break;
  }

  assert(State.ExitReason == ProgramState::Syscall &&
         "Exit reason must be syscall");
  return ProgramState::Syscall;
}

} // namespace rvemux