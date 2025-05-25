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

        # The EYA_MEMORY_STD_STREAM_ALIGNMENT macro defines the memory alignment requirement
        # for streaming operations using SIMD instructions. This value ensures optimal performance
        # when working with vectorized memory operations by aligning data blocks to match
        # the processor's cache line size and SIMD register width.
        #
        # This alignment is critical for non-temporal store instructions (e.g., _mm512_stream_si512)
        # which bypass cache to reduce pollution during large memory transfers.
        #
        # Default value corresponds to AVX-512 architecture requirements (64 bytes).
        # For embedded systems, proper alignment improves memory throughput
        # and prevents potential alignment-related performance penalties.
        EYA_MEMORY_STD_STREAM_ALIGNMENT=64

        # The EYA_MEMORY_STD_SMALL_BLOCK_THRESHOLD macro sets the maximum size threshold
        # for considering memory blocks as "small". Blocks below this size are processed
        # using simple byte/word/dword/qword operations without SIMD optimizations.
        #
        # This optimization reduces overhead from alignment checks and vector operations
        # for small data transfers, improving performance for common microcontroller use cases
        # where small memory operations are frequent.
        #
        # Example: With threshold 64, any copy/set operation with size ≤64 bytes
        #          will use basic integer register operations
        EYA_MEMORY_STD_SMALL_BLOCK_THRESHOLD=64

        # The EYA_MEMORY_STD_STREAM_THRESHOLD macro defines the minimum data size required
        # to activate streaming memory operations with non-temporal hints. These operations
        # optimize large memory transfers (typically ≥32MB) by avoiding cache pollution
        # and leveraging full memory bandwidth.
        #
        # Streaming instructions are most effective for bulk data transfers in high-performance
        # scenarios, though less critical for small embedded systems. The threshold prevents
        # using non-temporal stores for small/medium transfers where cache reuse is beneficial.
        #
        # Default value (32MB) balances between cache efficiency and memory bandwidth utilization
        # for modern processor architectures.
        EYA_MEMORY_STD_STREAM_THRESHOLD=33554432
)