cmake_minimum_required(VERSION 3.31)

project(aoc2015 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

file(GLOB SOURCES "day*.c" "day*.h")

add_executable(aoc2015 main.c common.h ${SOURCES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBMD REQUIRED IMPORTED_TARGET libmd)

target_link_libraries(aoc2015 PRIVATE PkgConfig::LIBMD)
target_compile_options(aoc2015 PRIVATE -Wall -Wpedantic -Wextra
                                       -Wno-unused-function)
