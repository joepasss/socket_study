cmake_minimum_required(VERSION 3.29.5)
project(error_handling)

add_library(error_handling STATIC error_handling.c)

target_include_directories(error_handling PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
