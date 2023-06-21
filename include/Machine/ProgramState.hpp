#ifndef RVEMUX_MACHINE_STATE_HPP
#define RVEMUX_MACHINE_STATE_HPP

#include "Basic/Types.hpp"

namespace rvemux {

static constexpr std::size_t NumGPRegisters = 32;

struct ProgramState {
  // General purpose registers
  u64 GPRegs[NumGPRegisters];
  // Program counter
  u64 PC;
};

} // namespace rvemux

#endif // RVEMUX_MACHINE_STATE_HPP