#ifndef RVEMUX_MACHINE_DECODER_HPP
#define RVEMUX_MACHINE_DECODER_HPP

#include "Basic/Types.hpp"

namespace rvemux {

class Instruction;

class Decoder {
public:
  static void decode(Instruction &Inst, u32 RawData);
};

} // namespace rvemux

#endif // RVEMUX_MACHINE_DECODER_HPP