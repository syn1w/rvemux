#ifndef RVEMUX_MACHINE_STATE_HPP
#define RVEMUX_MACHINE_STATE_HPP

#include "Basic/Types.hpp"
#include "Machine/Register.hpp"

namespace rvemux {

struct ProgramState {
  // General purpose registers
  u64 GPRegs[GPRegister::NumGPRegKinds];
  // Program counter
  u64 PC;

  enum ExitReasonKind {
    None,
    DirectBranch,
    IndirectBranch,
    Syscall,
  } ExitReason;
};

} // namespace rvemux

#endif // RVEMUX_MACHINE_STATE_HPP