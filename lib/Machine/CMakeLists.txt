set(MACHINE_INCLUDE_DIR
  ${CMAKE_SOURCE_DIR}/include/Machine
)

add_library(Machine
  Machine.cpp
  MMU.cpp

  ${MACHINE_INCLUDE_DIR}/Machine.hpp
  ${MACHINE_INCLUDE_DIR}/ProgramState.hpp
)

target_include_directories(Machine
  PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(Machine
  PRIVATE
  Basic
)