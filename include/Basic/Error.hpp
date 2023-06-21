#ifndef RVEMUX_BASIC_ERROR_HPP
#define RVEMUX_BASIC_ERROR_HPP

namespace rvemux {

[[noreturn]] void fatalf(const char *Fmt, ...);

} // namespace rvemux

#endif // RVEMUX_BASIC_ERROR_HPP