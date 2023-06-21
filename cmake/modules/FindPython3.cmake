macro(FindPython3)
  # Use PYTHON_HOME as a hint to find Python 3.
  set(Python3_ROOT_DIR "${PYTHON_HOME}")
  find_package(Python3 COMPONENTS Interpreter)
  if (Python3_Interpreter_FOUND)
    set(PYTHON3_FOUND TRUE)
    mark_as_advanced(Python3_EXECUTABLE)
  endif ()
endmacro ()

FindPython3()

if (NOT Python3_EXECUTABLE)
  message(FATAL_ERROR "Python3 not found")
else ()
  message(STATUS "Found Python3: ${Python3_EXECUTABLE}")
endif ()