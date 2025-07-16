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

# Check the size of the type "Size_t" and retain the result in the variable sizeof_size
# check_type_size("size_t" SIZEOF_SIZE)

# Check the size of the type "__int128" and retain the result in the variable sizeof_int128
check_type_size("__int128" SIZEOF_INT128)

# If the size of the pointer on VOID was determined, 
# add the definition for its size to the compilation list
if (${HAVE_SIZEOF_VOID_P})
    list(APPEND EYA_TARGET_PUBLIC_COMPILE_DEFINITIONS EYA_VOID_P_SIZE=${SIZEOF_VOID_P})
endif ()

# If the size of the type Char was determined, 
# add the definition for its size to the compilation list
if (${HAVE_SIZEOF_CHAR})
    list(APPEND EYA_TARGET_PUBLIC_COMPILE_DEFINITIONS EYA_CHAR_T_SIZE=${SIZEOF_CHAR})
endif ()

# If the size of the type Wchar_t was determined, 
# add the definition for its size to the compilation list
if (${HAVE_SIZEOF_WCHAR})
    list(APPEND EYA_TARGET_PUBLIC_COMPILE_DEFINITIONS EYA_WCHAR_T_SIZE=${SIZEOF_WCHAR})
endif ()

# If the size of the Short type was determined, 
# add the definition for its size to the compilation list
if (${HAVE_SIZEOF_SHORT})
    list(APPEND EYA_TARGET_PUBLIC_COMPILE_DEFINITIONS EYA_SHORT_T_SIZE=${SIZEOF_SHORT})
endif ()

# If the size of the intent was determined, 
# add the definition for its size to the compilation list
if (${HAVE_SIZEOF_INT})
    list(APPEND EYA_TARGET_PUBLIC_COMPILE_DEFINITIONS EYA_INT_T_SIZE=${SIZEOF_INT})
endif ()

# If the size of the LONG type was determined, 
# add the definition for its size to the compilation list
if (${HAVE_SIZEOF_LONG})
    list(APPEND EYA_TARGET_PUBLIC_COMPILE_DEFINITIONS EYA_LONG_T_SIZE=${SIZEOF_LONG})
endif ()

# If the size of the Long Long type was determined, 
# add the definition for its size to the compilation list
if (${HAVE_SIZEOF_LLONG})
    list(APPEND EYA_TARGET_PUBLIC_COMPILE_DEFINITIONS EYA_LLONG_T_SIZE=${SIZEOF_LLONG})
endif ()

# If the size of the type SIZE_T was determined,
# add the definition for its size to the compilation list
# if (${HAVE_SIZEOF_SIZE})
#     list(APPEND EYA_TARGET_PUBLIC_COMPILE_DEFINITIONS EYA_SIZE_T_SIZE=${SIZEOF_SIZE})
# endif ()

# If the size of the __int128 type was determined, 
# add the definition for its size to the compilation list
if (${HAVE_SIZEOF_INT128})
    list(APPEND EYA_TARGET_PUBLIC_COMPILE_DEFINITIONS EYA_INT128_T_SIZE=${SIZEOF_INT128})
endif ()
