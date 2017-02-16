function(add_example SUBSYSTEM NAME)
  add_executable(${NAME} "${SUBSYSTEM}/${NAME}.cpp")
endfunction()

add_subdirectory("examples")
