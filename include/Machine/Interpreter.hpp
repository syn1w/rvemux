#ifndef RVEMUX_MACHINE_INTERPRETER_HPP
#define RVEMUX_MACHINE_INTERPRETER_HPP

#include "Basic/Types.hpp"

namespace rvemux {

class ProgramState;
class Decoder;

class Executor {
public:
  virtual void executeBlock(ProgramState &State) = 0;
  virtual ~Executor() {}
};

class InterpreteExecutor : public Executor {
public:
  void executeBlock(ProgramState &State) override;
};

class JITExecutor : public Executor {
public:
  void executeBlock(ProgramState &State) override;
};

} // namespace rvemux

#endif // RVEMUX_MACHINE_INTERPRETER_HPP