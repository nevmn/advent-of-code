add_library(aoc2015common io.c alloc.c misc.c array.c)

target_include_directories(aoc2015common PUBLIC ${CMAKE_SOURCE_DIR}/include)