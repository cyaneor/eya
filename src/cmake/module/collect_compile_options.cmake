# -------------------------------------------------------------------------------------- #
# Compiler Flag Configuration for Build Tools                                            #
#                                                                                        #
# This script sets compiler-specific flags based on detected compiler (GCC, Clang, MSVC) #
# and CMake options prefixed with EYA_COMPILE_OPTION_. Each enabled option translates to  #
# appropriate compiler-specific flags for the target build configuration.                #
# -------------------------------------------------------------------------------------- #

# Retrieve all variables in current CMake directory
get_property(CMAKE_OPTIONS DIRECTORY PROPERTY VARIABLES)
foreach (CMAKE_OPTION IN ITEMS ${CMAKE_OPTIONS})
    if (CMAKE_OPTION MATCHES "^EYA_COMPILE_OPTION_.*")
        # Optimization Level Handling
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_OPTIMIZATION")
            if (${CMAKE_OPTION} STREQUAL "ON")
                # Set maximum optimization for all compilers
                if (CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS -O3)
                elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS /O2)  # MSVC equivalent of -O3
                endif ()
            else ()
                # Disable optimizations
                if (CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS -O0)
                elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS /Od)
                endif ()
            endif ()
            continue()
        endif ()

        # Debug Symbols Configuration
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_DEBUG")
            if (${CMAKE_OPTION} STREQUAL "ON")
                # Compiler-specific debug flags
                if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS -g)
                elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS /Zi)
                endif ()
            endif ()
            continue()
        endif ()

        # Instruction Set Optimizations
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_SSE2")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS -msse2)
                elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS /arch:SSE2)
                endif ()
            endif ()
            continue()
        endif ()

        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_AVX2")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS -mavx2)
                elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS /arch:AVX2)
                endif ()
            endif ()
            continue()
        endif ()

        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_AVX512")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS -mavx512f -mavx512bw -mavx512vl)
                elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS /arch:AVX512)
                endif ()
            endif ()
            continue()
        endif ()

        # Link-Time Optimization
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_LTO")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS -flto)
                elseif (CMAKE_C_COMPILER_ID STREQUAL "Clang")
                    # Verify LLD availability for LTO
                    find_program(LLD_LINKER lld)
                    if (LLD_LINKER)
                        list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS -flto)
                        list(APPEND EYA_TARGET_PRIVATE_LINK_OPTIONS -fuse-ld=lld)
                    else ()
                        message(WARNING "LLD linker not found - disabling LTO for Clang")
                    endif ()
                elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS /GL)
                    list(APPEND EYA_TARGET_PRIVATE_LINK_OPTIONS /LTCG)
                endif ()
            endif ()
            continue()
        endif ()

        # Loop Unrolling
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_UNROLL_LOOPS")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS -funroll-loops)
                # MSVC automatically handles loop unrolling with /O2
                endif ()
            endif ()
            continue()
        endif ()

        # Security Features
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_NO_STACK_PROTECTOR")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS -fno-stack-protector)
                elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS /GS-)
                endif ()
            endif ()
            continue()
        endif ()

        # Position Independent Code
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_PIC")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (${EYA_LIBRARY_OPTION_STATIC_BUILD})
                    message(FATAL_ERROR "PIC incompatible with static builds")
                endif ()

                if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS -fPIC)
                # MSVC always uses PIC for 64-bit targets
                endif ()
            endif ()
            continue()
        endif ()

        # Language Features
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_FNO_RTTI")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS -fno-rtti)
                elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS /GR-)
                endif ()
            endif ()
            continue()
        endif ()

        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_FNO_EXCEPTIONS")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS -fno-exceptions)
                elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS /EHsc-)
                endif ()
            endif ()
            continue()
        endif ()

        # Thread Safety
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_THREAD_SAFETY")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
                    list(APPEND EYA_TARGET_PRIVATE_COMPILE_OPTIONS -pthread)
                # MSVC handles thread safety through runtime libraries
                endif ()
            endif ()
            continue()
        endif ()
    endif ()
endforeach ()

# Display enabled compilation options
message(STATUS "Active compilation features:")
foreach (CMAKE_OPTION IN ITEMS ${CMAKE_OPTIONS})
    if (CMAKE_OPTION MATCHES "^EYA_COMPILE_OPTION_.*" AND ${CMAKE_OPTION} STREQUAL "ON")
        message(STATUS "  • ${CMAKE_OPTION}")
        list(APPEND EYA_TARGET_PUBLIC_COMPILE_DEFINITIONS ${CMAKE_OPTION})
    endif ()
endforeach ()