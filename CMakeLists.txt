cmake_minimum_required(VERSION 3.31)

project(aoc2015 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
add_subdirectory(lib)

enable_testing()
add_subdirectory(tests)

file(COPY ${CMAKE_SOURCE_DIR}/input DESTINATION ${CMAKE_BINARY_DIR})

add_executable(aoc2015 main.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBMD REQUIRED IMPORTED_TARGET libmd)

target_link_libraries(aoc2015 PRIVATE PkgConfig::LIBMD aoc2015common)

foreach (DAY RANGE 1 7)
    configure_file(${CMAKE_SOURCE_DIR}/templates/day.h.in ${CMAKE_SOURCE_DIR}/include/day${DAY}.h)
    configure_file(${CMAKE_SOURCE_DIR}/templates/libCMakeLists.txt.in ${CMAKE_SOURCE_DIR}/lib/day${DAY}/CMakeLists.txt)
    target_link_libraries(aoc2015 PRIVATE aoc2015day${DAY}solver)
endforeach ()

target_compile_options(aoc2015 PRIVATE -Wall -Wpedantic -Wextra
        -Wno-unused-function)
#target_compile_options(aoc2015 PRIVATE -fsanitize=address -fsanitize=undefined)
#target_link_options(aoc2015 PRIVATE -fsanitize=address -fsanitize=undefined)
include_directories(aoc2015 ${CMAKE_SOURCE_DIR}/include)
