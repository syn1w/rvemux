set(MACHINE_INCLUDE_DIR
  ${CMAKE_SOURCE_DIR}/include/Machine
)

add_library(Machine
  Decoder.cpp
  Instruction.cpp
  Interpreter.cpp
  Machine.cpp
  MMU.cpp

  ${MACHINE_INCLUDE_DIR}/Decoder.hpp
  ${MACHINE_INCLUDE_DIR}/Instruction.hpp
  ${MACHINE_INCLUDE_DIR}/Interpreter.hpp
  ${MACHINE_INCLUDE_DIR}/Machine.hpp
  ${MACHINE_INCLUDE_DIR}/MMU.hpp
  ${MACHINE_INCLUDE_DIR}/ProgramState.hpp
  ${MACHINE_INCLUDE_DIR}/Register.hpp
)

target_include_directories(Machine
  PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(Machine
  PRIVATE
  Basic
)