cmake_minimum_required(VERSION 3.31)

project(aoc2015day1 LANGUAGES C)

add_executable(aoc2015day1 day1.c)

target_link_libraries(aoc2015day1 PRIVATE aoc2015day1solver)