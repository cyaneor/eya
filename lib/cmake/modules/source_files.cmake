# -------------------------------------------------------------------------------------- #
# Library Source Files Configuration                                                     #
#                                                                                        #
# This section defines the core source files that comprise the EYA library:              #
# - Runtime components (exception handling, memory management, termination)              #
# - Memory subsystem implementations (standard, raw, typed, range-based)                 #
# - Core utilities (address handling, error management, versioning)                      #
# - Numeric type support (fixed-size types and their limits)                             #
#                                                                                        #
# Note: All paths are relative to EYA_LIB_SOURCE_DIR base directory                      #
# -------------------------------------------------------------------------------------- #

list(APPEND EYA_TARGET_SOURCE_FILES
        # Runtime
        ${EYA_LIB_SOURCE_DIR}/eya/runtime_exception_catch_stack.c
        ${EYA_LIB_SOURCE_DIR}/eya/runtime_allocator.c
        ${EYA_LIB_SOURCE_DIR}/eya/runtime_terminate.c
        
        # Error
        ${EYA_LIB_SOURCE_DIR}/eya/error.c

        # Memory
        ${EYA_LIB_SOURCE_DIR}/eya/array.c
        ${EYA_LIB_SOURCE_DIR}/eya/memory.c
        ${EYA_LIB_SOURCE_DIR}/eya/memory_std.c
        ${EYA_LIB_SOURCE_DIR}/eya/memory_raw.c
        ${EYA_LIB_SOURCE_DIR}/eya/memory_range.c
        ${EYA_LIB_SOURCE_DIR}/eya/memory_typed.c
        ${EYA_LIB_SOURCE_DIR}/eya/allocated_array.c
        ${EYA_LIB_SOURCE_DIR}/eya/allocated_range.c
        ${EYA_LIB_SOURCE_DIR}/eya/memory_allocator.c

        # Other
        ${EYA_LIB_SOURCE_DIR}/eya/eya.c
        ${EYA_LIB_SOURCE_DIR}/eya/version.c
        )