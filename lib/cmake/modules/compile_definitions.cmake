# -------------------------------------------------------------------------------------- #
# Configuration of macros and settings for the build                                     #
#                                                                                        #
# This script sets and propagates necessary parameters                                   #
# to the library via compiler definitions.                                               #
# -------------------------------------------------------------------------------------- #

list(APPEND EYA_TARGET_PUBLIC_COMPILE_DEFINITIONS
        # Definition of the operating system name used in the build.
        # The CMAKE_SYSTEM_NAME variable contains the OS name (e.g., Windows, Linux, Darwin).
        EYA_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}

        # Definition of the system processor architecture for the build.
        # The CMAKE_SYSTEM_PROCESSOR variable contains the processor architecture (e.g., x86_64, armv7).
        EYA_SYSTEM_PROCESSOR="${CMAKE_SYSTEM_PROCESSOR}"

        # EYA_RUNTIME_EXCEPTION_CATCH_STACK_MAX defines the maximum
        # number of preserved catch stack frames in the library.
        EYA_RUNTIME_EXCEPTION_CATCH_STACK_MAX=255

        # The EYA_DYNAMIC_BLOCK_GROWTH_FACTOR macro defines the memory growth factor
        # for dynamic data structures during reallocation. This coefficient determines
        # how much the data structure size will increase with each memory reallocation.
        #
        # To use a floating-point growth factor (e.g., 1.5),
        # multiply it by 1000 to work with integers
        # and avoid using the `float` type.
        #
        # This improves performance and reduces memory usage,
        # which is critical for microcontrollers and embedded systems.
        #
        # Example: To set a growth factor of 1.5, use:
        #    #define EYA_DYNAMIC_BLOCK_GROWTH_FACTOR 1500  # Equivalent to 1.5 * 1000
        #
        # New memory size calculation uses integer multiplication followed by division:
        # const EYA_usize_t new_capacity = (capacity * EYA_DYNAMIC_BLOCK_GROWTH_FACTOR) / 1000;
        #
        # For integer growth factors (e.g., 2), this also works:
        #    #define EYA_DYNAMIC_BLOCK_GROWTH_FACTOR 2000  # Equivalent to 2.0 * 1000
        #
        # Both approaches eliminate the need for `float` type usage,
        # reducing potential precision-related errors and performance overhead.
        EYA_DYNAMIC_BLOCK_GROWTH_FACTOR=1500
)