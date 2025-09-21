# Configures platform_limits.h with architecture-specific type sizes
# Uses either user-defined EYA_*_SIZE values or auto-detection
function(generate_platform_limits)
    include(CheckTypeSize)
    include(CheckIncludeFile)

    if (DEFINED EYA_PTR_T_SIZE)
        set(SIZEOF_VOID_P ${EYA_PTR_T_SIZE})
        set(HAVE_SIZEOF_VOID_P 1)
    else ()
        check_type_size("void *" SIZEOF_VOID_P)
        if (NOT HAVE_SIZEOF_VOID_P)
            message(FATAL_ERROR "Cannot determine size of void* pointer type.")
        endif ()
    endif ()

    if (DEFINED EYA_SIZE_T_SIZE)
        set(SIZEOF_SIZE_T ${EYA_SIZE_T_SIZE})
        set(HAVE_SIZEOF_SIZE_T 1)
    else ()
        check_type_size("size_t" SIZEOF_SIZE_T)
        if (NOT HAVE_SIZEOF_SIZE_T)
            message(FATAL_ERROR "Cannot determine size of size_t type.")
        endif ()
    endif ()

    configure_file(
            ${EYA_CMAKE_EXTENSION_CONFIGS_DIR}/platform_limits.h.in
            ${EYA_LIB_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/platform_limits.h
            @ONLY
    )
endfunction()