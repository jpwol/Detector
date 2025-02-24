cmake_minimum_required(VERSION 3.10)
project(detector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SRC_FILES "src/*.cpp")

set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin")
make_directory(${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

add_executable(detector ${SRC_FILES})

target_include_directories(detector PRIVATE include)
target_link_libraries(detector PRIVATE SDL2main SDL2)
