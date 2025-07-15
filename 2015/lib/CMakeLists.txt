file(GLOB SOURCES "common/*.c")

foreach (DAY RANGE 1 13)
    pad_string(PADDED_DAY ${DAY} 2)
    list(APPEND SOURCES "day${PADDED_DAY}.c")
endforeach ()

add_library(libaoc2015 ${SOURCES})

target_include_directories(libaoc2015 PUBLIC ${CMAKE_SOURCE_DIR}/include)
