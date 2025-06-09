add_subdirectory(common)

foreach (DAY RANGE 1 8)
    add_subdirectory(day${DAY})
endforeach ()
