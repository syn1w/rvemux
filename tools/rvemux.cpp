#include "Basic/Error.hpp"
#include "Machine/Machine.hpp"

#include <cstdio>

using namespace rvemux;

int main(int Argc, char **Argv) {
  if (Argc < 2)
    fatalf("no input files");

  Machine M;
  M.loadProgram(Argv[1]);
  printf("entry: 0x%lx\n", M.getEntry());
  printf("host alloc: 0x%lx\n", M.getMMU().getHostAlloc());
  printf("guest alloc: 0x%lx\n", M.getMMU().getGuestAlloc());
  printf("base address: 0x%lx\n", M.getMMU().getBaseAddress());

  return 0;
}
