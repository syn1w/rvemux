add_custom_target(TestExamples
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/test/examples
  ${CMAKE_BINARY_DIR}/test/examples
)

add_custom_command(TARGET TestExamples
  POST_BUILD
  COMMAND ${Python3_EXECUTABLE}
  ${CMAKE_BINARY_DIR}/test/examples/gen_tests.py ${CMAKE_SOURCE_DIR}
  COMMENT "Generating test examples"
  USES_TERMINAL
)