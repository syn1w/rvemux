#include "Basic/Utils.hpp"

#include <cstdio>
#include <cstdlib>

namespace rvemux {
namespace details {

#if defined __has_builtin
#if __has_builtin(__builtin_unreachable)
#define RVEMUX_BUILTIN_UNREACHABLE __builtin_unreachable()
#endif // __has_builtin(__builtin_unreachable)
#endif // defined __has_builtin

#if !defined(RVEMUX_BUILTIN_UNREACHABLE) && defined(_MSC_VER)
#define RVEMUX_BUILTIN_UNREACHABLE __assume(false)
#endif // !defined(BUILTIN_UNREACHABLE) && defined(_MSC_VER)

#ifndef RVEMUX_BUILTIN_UNREACHABLE
#define RVEMUX_BUILTIN_UNREACHABLE
#endif

[[noreturn]] void unreachableInternal(const char *Msg, const char *Filename,
                                      unsigned Lineno) {
#ifndef NDEBUG // DEBUG
  if (Msg)
    std::fprintf(stderr, "%s\n", Msg);
  std::fputs("Unreachable executed", stderr);
  if (Filename)
    std::fprintf(stderr, " at %s:%u", Filename, Lineno);
  std::fputs("!\n", stderr);
#endif
  std::abort();
  RVEMUX_BUILTIN_UNREACHABLE;
}

} // namespace details
} // namespace rvemux