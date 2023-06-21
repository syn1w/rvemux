set(BASIC_INCLUDE_DIR
  ${CMAKE_SOURCE_DIR}/include/Basic
)

add_library(Basic
  Error.cpp

  ${BASIC_INCLUDE_DIR}/Error.hpp
  ${BASIC_INCLUDE_DIR}/Types.hpp
)

target_include_directories(Basic
  PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)