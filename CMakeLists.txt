cmake_minimum_required(VERSION 3.16)
project(GENTT)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR links)

set(IMPL_DIR ${SRC_DIR}/impl)
set(UTILS ${SRC_DIR}/utils)

file(GLOB SOURCES 
  ${IMPL_DIR}/*.cpp
  ${UTILS}/*.cpp
  ${SRC_DIR}/main.cpp
)

include_directories(include)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main 
  ${SOURCES}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set(OPTS )

# target_compile_options(hello PRIVATE OPTS)
