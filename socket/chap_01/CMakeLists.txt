cmake_minimum_required(VERSION 3.28)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  chap_01
  VERSION 0.0.1
  LANGUAGES C
)

add_subdirectory(client)
add_subdirectory(server)
