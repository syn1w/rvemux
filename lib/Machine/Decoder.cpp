#include "Machine/Decoder.hpp"

#include "Basic/Error.hpp"
#include "Basic/Utils.hpp"

namespace rvemux {

static u32 quadrant(u32 RawData) {
  // See 16.8 in https://riscv.org/wp-content/uploads/2019/06/riscv-spec.pdf
  // RVC Instruction Set Listings
  // inst[1:0]
  return RawData & 0x3;
}

void Decoder::decode(Instruction &Inst, u32 RawData) {
  u32 Quadrant = quadrant(RawData);
  switch (Quadrant) {
  case 0x0:
    fatalf("Not implemented");
  case 0x1:
    fatalf("Not implemented");
  case 0x2:
    fatalf("Not implemented");
  case 0x3:
    fatalf("Not implemented");
  default:
    UNREACHABLE("Unknown quadrant");
  }
}

} // namespace rvemux