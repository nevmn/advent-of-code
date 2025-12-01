cmake_minimum_required(VERSION 3.31)

project(aoc2015 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include("${CMAKE_MODULE_PATH}/PadString.cmake")

add_executable(aoc2015 main.c)

foreach (DAY RANGE 1 18)
    pad_string(PADDED_DAY ${DAY} 2)
    configure_file(${CMAKE_SOURCE_DIR}/templates/day.h.in ${CMAKE_SOURCE_DIR}/include/day${PADDED_DAY}.h)
endforeach ()

add_subdirectory(lib)

enable_testing()
add_subdirectory(tests)

file(COPY ${CMAKE_SOURCE_DIR}/input DESTINATION ${CMAKE_BINARY_DIR})

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBMD REQUIRED IMPORTED_TARGET libmd)
pkg_check_modules(LIBJQ REQUIRED IMPORTED_TARGET libjq)

target_link_libraries(aoc2015 PRIVATE PkgConfig::LIBMD PkgConfig::LIBJQ libaoc2015)

target_compile_options(aoc2015 PRIVATE -Wall -Wpedantic -Wextra
        -Wno-unused-function)
#target_compile_options(aoc2015 PRIVATE -fsanitize=address -fsanitize=undefined)
#target_link_options(aoc2015 PRIVATE -fsanitize=address -fsanitize=undefined)
include_directories(aoc2015 ${CMAKE_SOURCE_DIR}/include)
