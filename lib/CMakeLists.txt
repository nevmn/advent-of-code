add_subdirectory(common)

foreach (DAY RANGE 1 7)
    add_subdirectory(day${DAY})
endforeach ()
