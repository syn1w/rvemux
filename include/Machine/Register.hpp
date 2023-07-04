#ifndef RVEMUX_MACHINE_REGISTER_HPP
#define RVEMUX_MACHINE_REGISTER_HPP

#include "Basic/Types.hpp"

namespace rvemux {

struct GPRegister {
  // clang-format off
  enum GPRegisterKind {
    Zero, RA,
    SP, GP, TP,
    T0, T1, T2,
    S0, S1,
    A0, A1, A2, A3, A4, A5, A6, A7,
    S2, S3, S4, S5, S6, S7, S8, S9, S10, S11,
    T3, T4, T5, T6,
    NumGPRegKinds,
  };
  // clang-format on
};

} // namespace rvemux

#endif // RVEMUX_MACHINE_REGISTER_HPP