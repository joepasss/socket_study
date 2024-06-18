cmake_minimum_required(VERSION 3.28)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  chap_02_01
  VERSION 0.0.1
  LANGUAGES C)

set(LIB_DIR "../lib")
add_subdirectory(${LIB_DIR} ${CMAKE_BINARY_DIR}/lib)

set(SOURCES src/server.c src/client.c)

set(EXECUTABLES server client)

list(LENGTH SOURCES num_sources)
math(EXPR num_executables "${num_sources} -1")

foreach(i RANGE 0 ${num_executables})
  list(GET SOURCES ${i} source_file)
  list(GET EXECUTABLES ${i} exe_name)
  add_executable(${exe_name} ${source_file})
  target_link_libraries(${exe_name} PRIVATE error_handling)
endforeach()
