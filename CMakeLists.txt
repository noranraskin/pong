cmake_minimum_required(VERSION 3.24)
project(Pong C)

set(CMAKE_C_STANDARD 11)
find_package(raylib CONFIG REQUIRED)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(src)

add_executable(Pong
        src/main.c
        src/main.h src/game.c src/game.h src/menu.c src/menu.h)

target_include_directories(Pong PRIVATE ${raylib_INCLUDE_DIRS})
target_link_libraries(Pong PRIVATE ${raylib_LIBRARIES})
target_link_libraries(Pong PRIVATE ${CURSES_LIBRARIES})