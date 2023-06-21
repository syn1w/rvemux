#include "Basic/Error.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>

namespace rvemux {

#define LIGHT_RED "\x1b[1;31m"
#define ANSI_RESET "\x1b[0m"

[[noreturn]] void fatalf(const char *Fmt, ...) {
  std::va_list List;
  va_start(List, Fmt);
  std::fputs(LIGHT_RED "error: " ANSI_RESET, stderr);
  std::vfprintf(stderr, Fmt, List);
  std::fputc('\n', stderr);
  va_end(List);
  std::exit(1);
}

} // namespace rvemux