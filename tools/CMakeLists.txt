add_executable(rvemux
  rvemux.cpp
)

target_include_directories(rvemux
  PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(rvemux
  PRIVATE
  Basic
  Machine
)