#ifndef RVEMUX_BASIC_UTILS_HPP
#define RVEMUX_BASIC_UTILS_HPP

namespace rvemux {
namespace details {

[[noreturn]] void unreachableInternal(const char *Msg, const char *Filename,
                                      unsigned Lineno);

} // namespace details
} // namespace rvemux

#define UNREACHABLE(Msg)                                                       \
  rvemux::details::unreachableInternal(Msg, __FILE__, __LINE__)

#endif // RVEMUX_BASIC_UTILS_HPP