#include "Machine/Interpreter.hpp"

#include "Machine/Decoder.hpp"
#include "Machine/Instruction.hpp"
#include "Machine/MMU.hpp"
#include "Machine/ProgramState.hpp"

namespace rvemux {

void InterpreteExecutor::executeBlock(ProgramState &State) {
  Instruction Inst;
  while (true) {
    u64 HostPC = MemManagerUnit::toHost(State.PC);
    u32 RawData = *reinterpret_cast<const u32 *>(HostPC);
    Decoder::decode(Inst, RawData);
    Inst.execute(State);
    // Zero register is always 0
    State.GPRegs[GPRegister::Zero] = 0;

    if (Inst.Break)
      break;

    State.PC += Inst.IsRVC ? 2 : 4;
  }
}

void JITExecutor::executeBlock(ProgramState &State) {
  // TODO
}

} // namespace rvemux