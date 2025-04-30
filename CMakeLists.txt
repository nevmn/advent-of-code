cmake_minimum_required(VERSION 3.31)

project(aoc2015 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(
  aoc2015
  main.c
  day1.c
  day1.h
  day2.c
  day2.h
  day3.c
  day3.h
  common.h)

target_compile_options(aoc2015 PRIVATE -Wall -Wpedantic -Wextra
                                       -Wno-unused-function)

# target_link_libraries(aoc2015 PRIVATE -static)
