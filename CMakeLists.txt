cmake_minimum_required(VERSION 3.24)
project(Pong C)

set(CMAKE_C_STANDARD 11)
find_package(raylib CONFIG REQUIRED)
include_directories(src)

add_executable(Pong
        src/main.c
        src/main.h)

target_include_directories(Pong PRIVATE ${raylib_INCLUDE_DIRS})
target_link_libraries(Pong PRIVATE ${raylib_LIBRARIES})