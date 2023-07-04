#ifndef RVEMUX_MACHINE_INSTRUCTION_HPP
#define RVEMUX_MACHINE_INSTRUCTION_HPP

#include "Basic/Types.hpp"

namespace rvemux {

class ProgramState;

class Instruction {
public:
  void execute(ProgramState &State);

public:
  i8 RD;
  i8 RS1;
  i8 RS2;
  i32 Imm;

  enum InstructionKind {
    Addi,
    NumInstKinds,
  } Kind;

  bool IsRVC;
  bool Break;
};

} // namespace rvemux

#endif // RVEMUX_MACHINE_INSTRUCTION_HPP