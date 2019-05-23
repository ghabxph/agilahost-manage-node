cmake_minimum_required(VERSION 3.11)

set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

project(HOSTING_NODE CXX)

file(GLOB_RECURSE SOURCE src/*.cpp)
file(GLOB_RECURSE INCLUDE src/*.hpp)

include_directories(
  src
  src/include
)

add_executable(
  node
  ${SOURCE}
  ${INCLUDE}
)

