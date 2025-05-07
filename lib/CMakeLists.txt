add_subdirectory(common)

foreach (DAY RANGE 1 6)
    add_subdirectory(day${DAY})
endforeach ()
