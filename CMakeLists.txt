cmake_minimum_required(VERSION 3.29)
project(Ping-Pong)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib REQUIRED)

# Link necessary macOS frameworks using CMake's framework support
find_library(COCOA_FRAMEWORK Cocoa)
find_library(IOKIT_FRAMEWORK IOKit)
find_library(OPENGL_FRAMEWORK OpenGL)

add_executable(Ping-Pong main.cpp)

target_link_libraries(Ping-Pong raylib ${OPENGL_FRAMEWORK} ${COCOA_FRAMEWORK} ${IOKIT_FRAMEWORK})