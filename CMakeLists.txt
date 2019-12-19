cmake_minimum_required(VERSION 3.15)
project(cpp-training)

set(CMAKE_CXX_STANDARD 17)

message(STATUS "Use *.cpp file globbing")
file(GLOB SRCS "*.cpp")

enable_testing()
foreach(SRC_PATH ${SRCS})
  get_filename_component(SRC ${SRC_PATH} NAME)
  message(STATUS "\tAdd example ${SRC}")
  string(REGEX REPLACE ".cpp$" ".exe" EXE ${SRC})
  string(REGEX REPLACE ".cpp$" "" TEST ${SRC})
  add_executable(${EXE} ${SRC})
  add_test(NAME ${TEST} COMMAND ${EXE})
endforeach()
