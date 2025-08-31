# ---------------------------------------------------------------------------------------- #
# Type Size Detection Function                                                             #
#                                                                                          #
# This function determines the sizes of fundamental data types on the target platform      #
# and returns them as a list of compiler definitions.                                      #
#                                                                                          #
# Parameters:                                                                              #
#   OUTPUT_VAR - Name of the output variable that will receive the list of definitions     #
#                                                                                          #
# Detects sizes for:                                                                       #
#   - Pointer types (void*)                                                                #
#   - Character types (char, wchar_t)                                                      #
#   - Integer types (short, int, long, long long, __int128)                                #
# ---------------------------------------------------------------------------------------- #

function(get_type_sizes OUTPUT_VAR)
    # We turn on the Checktypesize module, which allows you to check the size of data types
    include(CheckTypeSize)

    # Check the size of the pointer on VOID (VOID*) and retain the result in the variable sizeof_void_p
    check_type_size("void *" SIZEOF_VOID_P)

    # Check the size of the "Char" type and retain the result in the variable sizeof_char
    check_type_size("char" SIZEOF_CHAR)

    # Check the size of the "Wchar_t" type and retain the result in the variable sizeof_wchar
    check_type_size("wchar_t" SIZEOF_WCHAR)

    # Check the size of the "Short" type and retain the result in the variable sizeof_short
    check_type_size("short" SIZEOF_SHORT)

    # Check the size of the type "int" and retain the result in the variable sizeof_int
    check_type_size("int" SIZEOF_INT)

    # Check the size of the LONG type and retain the result in the variable sizeof_long
    check_type_size("long" SIZEOF_LONG)

    # Check the size of the Long Long type and retain the result in the variable sizeof_llong
    check_type_size("long long" SIZEOF_LLONG)

    # Check the size of the type "__int128" and retain the result in the variable sizeof_int128
    check_type_size("__int128" SIZEOF_INT128)

    # If the size of the pointer on VOID was determined,
    # add the definition for its size to the compilation list
    if (${HAVE_SIZEOF_VOID_P})
        list(APPEND ${OUTPUT_VAR} EYA_VOID_P_SIZE=${SIZEOF_VOID_P})
    endif ()

    # If the size of the type Char was determined,
    # add the definition for its size to the compilation list
    if (${HAVE_SIZEOF_CHAR})
        list(APPEND ${OUTPUT_VAR} EYA_CHAR_SIZE=${SIZEOF_CHAR})
    endif ()

    # If the size of the type Wchar_t was determined,
    # add the definition for its size to the compilation list
    if (${HAVE_SIZEOF_WCHAR})
        list(APPEND ${OUTPUT_VAR} EYA_WCHAR_SIZE=${SIZEOF_WCHAR})
    endif ()

    # If the size of the Short type was determined,
    # add the definition for its size to the compilation list
    if (${HAVE_SIZEOF_SHORT})
        list(APPEND ${OUTPUT_VAR} EYA_SHORT_SIZE=${SIZEOF_SHORT})
    endif ()

    # If the size of the intent was determined,
    # add the definition for its size to the compilation list
    if (${HAVE_SIZEOF_INT})
        list(APPEND ${OUTPUT_VAR} EYA_INT_SIZE=${SIZEOF_INT})
    endif ()

    # If the size of the LONG type was determined,
    # add the definition for its size to the compilation list
    if (${HAVE_SIZEOF_LONG})
        list(APPEND ${OUTPUT_VAR} EYA_LONG_SIZE=${SIZEOF_LONG})
    endif ()

    # If the size of the Long Long type was determined,
    # add the definition for its size to the compilation list
    if (${HAVE_SIZEOF_LLONG})
        list(APPEND ${OUTPUT_VAR} EYA_LLONG_SIZE=${SIZEOF_LLONG})
    endif ()

    # If the size of the __int128 type was determined,
    # add the definition for its size to the compilation list
    if (${HAVE_SIZEOF_INT128})
        list(APPEND ${OUTPUT_VAR} EYA_INT128_SIZE=${SIZEOF_INT128})
    endif ()

    # Update the variable in parent scope
    set(${OUTPUT_VAR} ${${OUTPUT_VAR}} PARENT_SCOPE)
endfunction()