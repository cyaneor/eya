##
# @file config.cmake
# @brief CMake script for generating type limits and configuration headers.
#
# This script provides two key functions:
# - @ref generate_limits: Computes minimum and maximum values for given C numeric types
#   and exposes them as CMake variables.
# - @ref generate_config: Generates a configuration header file (`config.h`) containing
#   constants that describe platform-specific type sizes and limits.
#
# The generated configuration is tightly integrated with the custom numeric types
# defined in @ref numeric_types.h.
##

##
# @brief Generate numeric limits for a given C type.
#
# This function calculates the minimum and maximum values of a specified C type
# (e.g., `int`, `unsigned long long`, `wchar_t`, `__int128`) based on its size
# and whether it is signed or unsigned.
#
# @param type
#   The C type to evaluate (e.g., `"int"`, `"unsigned long"`, `"void *"`).
#
# @param size
#   The size of the type in bytes, as detected by CMake's `check_type_size`.
#
# @param min_var
#   The name of the variable in which the computed minimum value will be stored.
#
# @param max_var
#   The name of the variable in which the computed maximum value will be stored.
#
# @note
#   - The function uses platform assumptions about signedness of certain types
#     (e.g., `char` and `wchar_t`).
#   - Unsupported type/size combinations will trigger a CMake `FATAL_ERROR`.
#
# @see generate_config
##
function(generate_limits type size min_var max_var)
    # Initialize min and max variables
    set(min_value "")
    set(max_value "")

    # Determine limits based on size and signed/unsigned assumption
    if ("${type}" STREQUAL "size_t") # Unsigned
        set(min_value 0)
        if (${size} EQUAL 4)
            set(max_value "4294967295U")
        elseif (${size} EQUAL 8)
            set(max_value "18446744073709551615ULL")
        else ()
            message(FATAL_ERROR "Unsupported size ${size} for ${type}")
        endif ()
    elseif ("${type}" STREQUAL "ssize_t") # Signed version of size_t
        if (${size} EQUAL 4)
            set(min_value "(-2147483648)")
            set(max_value "2147483647")
        elseif (${size} EQUAL 8)
            set(min_value "(-9223372036854775808LL)")
            set(max_value "9223372036854775807LL")
        else ()
            message(FATAL_ERROR "Unsupported size ${size} for ${type}")
        endif ()
    elseif ("${type}" MATCHES "void\\ *\\*") # Unsigned
        set(min_value 0)
        if (${size} EQUAL 4)
            set(max_value "0xFFFFFFFFU")
        elseif (${size} EQUAL 8)
            set(max_value "0xFFFFFFFFFFFFFFFFULL")
        else ()
            message(FATAL_ERROR "Unsupported size ${size} for ${type}")
        endif ()
    elseif ("${type}" STREQUAL "char")
        # Assuming char is signed (platform-dependent)
        set(min_value "(-128)")
        set(max_value "127")
    elseif ("${type}" STREQUAL "unsigned char")
        set(min_value 0)
        set(max_value "255")
    elseif ("${type}" STREQUAL "wchar_t")
        # Assuming wchar_t is signed
        if (${size} EQUAL 2)
            set(min_value "(-32768)")
            set(max_value "32767")
        elseif (${size} EQUAL 4)
            set(min_value "(-2147483648L)")
            set(max_value "2147483647L")
        else ()
            message(FATAL_ERROR "Unsupported size ${size} for ${type}")
        endif ()
    elseif ("${type}" STREQUAL "short")
        set(min_value "(-32768)")
        set(max_value "32767")
    elseif ("${type}" STREQUAL "unsigned short")
        set(min_value 0)
        set(max_value "65535")
    elseif ("${type}" STREQUAL "int")
        set(min_value "(-2147483648LL)")
        set(max_value "2147483647")
    elseif ("${type}" STREQUAL "unsigned int")
        set(min_value 0)
        set(max_value "4294967295U")
    elseif ("${type}" STREQUAL "long")
        if (${size} EQUAL 4)
            set(min_value "(-2147483648LL)")
            set(max_value "2147483647LL")
        elseif (${size} EQUAL 8)
            set(min_value "(-9223372036854775808LL)")
            set(max_value "9223372036854775807LL")
        else ()
            message(FATAL_ERROR "Unsupported size ${size} for ${type}")
        endif ()
    elseif ("${type}" STREQUAL "unsigned long")
        if (${size} EQUAL 4)
            set(min_value 0)
            set(max_value "4294967295UL")
        elseif (${size} EQUAL 8)
            set(min_value 0)
            set(max_value "18446744073709551615ULL")
        else ()
            message(FATAL_ERROR "Unsupported size ${size} for ${type}")
        endif ()
    elseif ("${type}" STREQUAL "long long")
        set(min_value "(-9223372036854775808LL)")
        set(max_value "9223372036854775807LL")
    elseif ("${type}" STREQUAL "unsigned long long")
        set(min_value 0)
        set(max_value "18446744073709551615ULL")
    else ()
        message(FATAL_ERROR "Unsupported type ${type} or size ${size}")
    endif ()

    # Set the output variables in the parent scope
    set(${min_var} "${min_value}" PARENT_SCOPE)
    set(${max_var} "${max_value}" PARENT_SCOPE)
endfunction()

##
# @brief Generate configuration header with type sizes and limits.
#
# This function:
# - Detects platform-specific type sizes using `check_type_size`.
# - Uses @ref generate_limits to compute min/max values for each supported type.
# - Writes results into `config.h`, defining macros for each type's size,
#   minimum, and maximum values.
#
# The generated header provides a consistent interface for numeric limits across
# platforms and is aligned with the typedefs defined in @ref numeric_types.h.
#
# Example output in `config.h`:
# @code{.c}
#   #define EYA_INT_T_SIZE 4
#   #define EYA_SINT_T_MIN (-2147483648LL)
#   #define EYA_SINT_T_MAX 2147483647
#   #define EYA_UINT_T_MIN 0
#   #define EYA_UINT_T_MAX 4294967295U
# @endcode
#
# @note
#   The header is written to `${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h`.
#
# @see generate_limits
# @see numeric_types.h
##
function(generate_config)
    include(CheckTypeSize)

    # Check sizes
    check_type_size("size_t" SIZEOF_SIZE_T)
    check_type_size("void *" SIZEOF_VOID_P)
    check_type_size("char" SIZEOF_CHAR)
    check_type_size("wchar_t" SIZEOF_WCHAR_T)
    check_type_size("short" SIZEOF_SHORT)
    check_type_size("int" SIZEOF_INT)
    check_type_size("long" SIZEOF_LONG)
    check_type_size("long long" SIZEOF_LLONG)

    file(WRITE ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "/**\n")
    file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h " * @file config.h\n")
    file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h " * @brief Auto-generated configuration header\n")
    file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h " *\n")
    file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h " * This file defines platform-specific limits and sizes for the current target system.\n")
    file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h " * It is generated automatically by CMake, do not edit manually.\n")
    file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h " */\n\n")

    file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_CONFIG_H\n")
    file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#define EYA_CONFIG_H\n")
    file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

    if (${HAVE_SIZEOF_VOID_P})
        generate_limits(" void * " ${SIZEOF_VOID_P} VOID_P_MIN VOID_P_MAX)
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_PTR_T_SIZE\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_PTR_T_SIZE ${SIZEOF_VOID_P}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_PTR_T_SIZE\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_PTR_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_PTR_T_MIN ${VOID_P_MIN}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_PTR_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_PTR_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_PTR_T_MAX ${VOID_P_MAX}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_PTR_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")
    endif ()

    if (${HAVE_SIZEOF_SIZE_T})
        generate_limits("ssize_t" ${SIZEOF_SIZE_T} SSIZE_T_MIN SSIZE_T_MAX)
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_SIZE_T_SIZE\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_SIZE_T_SIZE ${SIZEOF_SIZE_T}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_SIZE_T_SIZE\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_SSIZE_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_SSIZE_T_MIN ${SSIZE_T_MIN}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_SSIZE_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_SSIZE_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_SSIZE_T_MAX ${SSIZE_T_MAX}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_SSIZE_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        generate_limits("size_t" ${SIZEOF_SIZE_T} SIZE_T_MIN SIZE_T_MAX)
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_USIZE_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_USIZE_T_MIN ${SIZE_T_MIN}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_USIZE_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_USIZE_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_USIZE_T_MAX ${SIZE_T_MAX}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_USIZE_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")
    endif ()

    if (${HAVE_SIZEOF_CHAR})
        generate_limits("char" ${SIZEOF_CHAR} CHAR_MIN CHAR_MAX)
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_CHAR_T_SIZE\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_CHAR_T_SIZE ${SIZEOF_CHAR}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_CHAR_T_SIZE\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_SCHAR_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_SCHAR_T_MIN ${CHAR_MIN}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_SCHAR_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_SCHAR_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_SCHAR_T_MAX ${CHAR_MAX}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_SCHAR_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        generate_limits("unsigned char" 1 UCHAR_MIN UCHAR_MAX)
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_UCHAR_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_UCHAR_T_MIN ${UCHAR_MIN}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_UCHAR_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_UCHAR_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_UCHAR_T_MAX ${UCHAR_MAX}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_UCHAR_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")
    endif ()

    if (${HAVE_SIZEOF_WCHAR_T})
        generate_limits("wchar_t" ${SIZEOF_WCHAR_T} WCHAR_MIN WCHAR_MAX)
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_WCHAR_T_SIZE\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_WCHAR_T_SIZE ${SIZEOF_WCHAR_T}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_WCHAR_T_SIZE\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_WCHAR_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_WCHAR_T_MIN ${WCHAR_MIN}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_WCHAR_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_WCHAR_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_WCHAR_T_MAX ${WCHAR_MAX}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_WCHAR_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")
    endif ()

    if (${HAVE_SIZEOF_SHORT})
        generate_limits("short" ${SIZEOF_SHORT} SHORT_MIN SHORT_MAX)
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_SHORT_T_SIZE\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_SHORT_T_SIZE ${SIZEOF_SHORT}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_SHORT_T_SIZE\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_SSHORT_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_SSHORT_T_MIN ${SHORT_MIN}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_SSHORT_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_SSHORT_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_SSHORT_T_MAX ${SHORT_MAX}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_SSHORT_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        generate_limits("unsigned short" ${SIZEOF_SHORT} USHORT_MIN USHORT_MAX)
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_USHORT_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_USHORT_T_MIN ${USHORT_MIN}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_USHORT_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_USHORT_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_USHORT_T_MAX ${USHORT_MAX}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_USHORT_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")
    endif ()

    if (${HAVE_SIZEOF_INT})
        generate_limits("int" ${SIZEOF_INT} INT_MIN INT_MAX)
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_INT_T_SIZE\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_INT_T_SIZE ${SIZEOF_INT}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_INT_T_SIZE\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_SINT_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_SINT_T_MIN ${INT_MIN}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_SINT_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_SINT_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_SINT_T_MAX ${INT_MAX}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_SINT_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        generate_limits("unsigned int" ${SIZEOF_INT} UINT_MIN UINT_MAX)
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_UINT_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_UINT_T_MIN ${UINT_MIN}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_UINT_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_UINT_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_UINT_T_MAX ${UINT_MAX}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_UINT_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")
    endif ()

    if (${HAVE_SIZEOF_LONG})
        generate_limits("long" ${SIZEOF_LONG} LONG_MIN LONG_MAX)
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_LONG_T_SIZE\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_LONG_T_SIZE ${SIZEOF_LONG}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_LONG_T_SIZE\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_SLONG_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_SLONG_T_MIN ${LONG_MIN}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_SLONG_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_SLONG_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_SLONG_T_MAX ${LONG_MAX}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_SLONG_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        generate_limits("unsigned long" ${SIZEOF_LONG} ULONG_MIN ULONG_MAX)
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_ULONG_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_ULONG_T_MIN ${ULONG_MIN}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_ULONG_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_ULONG_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_ULONG_T_MAX ${ULONG_MAX}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_ULONG_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")
    endif ()

    if (${HAVE_SIZEOF_LLONG})
        generate_limits("long long" ${SIZEOF_LLONG} LLONG_MIN LLONG_MAX)
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_LLONG_T_SIZE\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_LLONG_T_SIZE ${SIZEOF_LLONG}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_LLONG_T_SIZE\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_SLLONG_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_SLLONG_T_MIN ${LLONG_MIN}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_SLLONG_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_SLLONG_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_SLLONG_T_MAX ${LLONG_MAX}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_SLLONG_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        generate_limits("unsigned long long" ${SIZEOF_LLONG} ULLONG_MIN ULLONG_MAX)
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_ULLONG_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_ULLONG_T_MIN ${ULLONG_MIN}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_ULLONG_T_MIN\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")

        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#ifndef EYA_ULLONG_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "    #define EYA_ULLONG_T_MAX ${ULLONG_MAX}\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_ULLONG_T_MAX\n")
        file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "\n")
    endif ()

    file(APPEND ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/config.h "#endif // EYA_CONFIG_H\n")
endfunction()