cmake_minimum_required(VERSION 3.8)

project(rvemux
  VERSION 0.1.0
  DESCRIPTION "RISC-V emulator in C++"
  LANGUAGES C CXX
)

# [CMake Build Type]
if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, default to Debug.")
  set(CMAKE_BUILD_TYPE Debug)
endif (NOT CMAKE_BUILD_TYPE)

string(TOUPPER "${CMAKE_BUILD_TYPE}" UPCASE_CMAKE_BUILD_TYPE)
if (CMAKE_BUILD_TYPE AND
    NOT UPCASE_CMAKE_BUILD_TYPE MATCHES "^(DEBUG|RELEASE|RELWITHDEBINFO|MINSIZEREL)$")
  message(FATAL_ERROR "Invalid value for CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif()

# [Disable in-source build]
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not allowed.")
endif()

# [C/C++ Standard]
set(CMAKE_C_STANDARD 11 CACHE STRING "C standard to conform to")
set(CMAKE_CXX_STANDARD 14 CACHE STRING "C++ standard to conform to")

# [CMake Module]
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
)

# [Dump CompileCommands]
# Generate a CompilationDatabase (compile_commands.json file) for our build,
# for use by clang_complete, YouCompleteMe, etc.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# [Output Dir]
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(tools)