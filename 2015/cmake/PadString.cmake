function(pad_string OUT_VAR INPUT WIDTH)
    set(CHAR "0")
    if (${ARGC} GREATER 3)
        set(CHAR "${ARGV3}")
    endif ()

    string(LENGTH "${INPUT}" LEN)
    math(EXPR PADLEN "${WIDTH} - ${LEN}")

    set(PAD "")
    if (PADLEN GREATER 0)
        foreach (_ RANGE 1 ${PADLEN})
            set(PAD "${CHAR}${PAD}")
        endforeach ()
    endif ()

    set(${OUT_VAR} "${PAD}${INPUT}" PARENT_SCOPE)
endfunction()

