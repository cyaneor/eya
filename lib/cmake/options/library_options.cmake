# -------------------------------------------------------------------------------------- #
# Configuration options for building and managing library parameters                     #
#                                                                                        #
# This script defines various configuration options,                                     #
# allowing them to be passed to the compiler as definitions.                             #
#                                                                                        #
# These options affect library behavior by defining build configuration,                 #
# symbol import/export, allocator usage, and multithreaded variable handling.            #
# -------------------------------------------------------------------------------------- #

# Option:
#
#     EYA_LIBRARY_OPTION_SHARED_BUILD
#
# Description:
#
#     This CMake option, EYA_LIBRARY_OPTION_SHARED_BUILD,
#     controls the build configuration for creating a shared library.
#
#     When enabled (ON),
#     it specifies that the project should be built as a shared library.
#
#     Shared libraries are dynamically linked libraries
#     that can be loaded by programs at runtime
#     when their functionality is required.
#
#     This parameter is useful for splitting code into modules
#     that can be loaded by multiple applications simultaneously.
#
# Usage:
#
#     ON: Specifies the project should be built as a shared library.
#     OFF: Disables shared library build,
#          resulting in a static library or other binary artifact.
#
# Note:
#
#     The choice between shared and static libraries
#     affects how the resulting code will be linked
#     with other programs.
#
#     Shared libraries offer greater runtime flexibility
#     but may introduce additional complexity.
#
option(EYA_LIBRARY_OPTION_SHARED_BUILD
        "Build as shared dynamic library." ON)

# Option:
#
#     EYA_LIBRARY_OPTION_STATIC_BUILD
#
# Description:
#
#     This CMake option, EYA_LIBRARY_OPTION_STATIC_BUILD,
#     controls the build configuration for creating a static library.
#
#     When enabled (ON),
#     it specifies that the project should be built as a static library.
#
#     Static libraries are linked into applications during compilation
#     and included in the final binary. They don't require
#     external library files at program execution.
#
#     This parameter is useful when creating self-contained executables
#     and avoiding runtime dependencies.
#
# Usage:
#
#     ON: Specifies the project should be built as a static library.
#     OFF: Disables static library build,
#          resulting in a shared library or other binary artifact.
#
# Note:
#
#     Static libraries may improve performance in some cases
#     by eliminating runtime loading overhead,
#     but increase final binary size.
#
option(EYA_LIBRARY_OPTION_STATIC_BUILD
        "Build as static library." OFF)

# Option:
#
#     EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_USE_STDLIB
#
# Description:
#
#     This CMake option determines whether to use standard library
#     functions for runtime allocator initialization in the EYA project.
#
#     When enabled (ON), runtime allocator initialization
#     uses standard library functions.
#
# Usage:
#
#     ON: Use standard library for runtime allocator initialization.
#     OFF: Require custom initialization procedures.
#
# Note:
#
#     Standard library usage simplifies development through
#     portable implementations. Disable for custom environments
#     or specialized allocators.
#
option(EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_USE_STDLIB
        "Use stdlib functions for runtime allocator initialization." ON)

# Option:
#
#     EYA_LIBRARY_OPTION_RUNTIME_TERMINATE_USE_STDLIB
#
# Description:
#
#     Determines whether to initialize default termination handler (`abort()`)
#     using the C standard library in the EYA framework.
#
#     - ON: Global handler `m_runtime_terminate` initialized with `abort()`
#     - OFF: Handler set to `nullptr`, requiring explicit setup
#            via `eya_runtime_terminate_set()`
#
# Usage:
#
#     ON (default):
#         Use `abort()` for termination handling.
#         Provides predictable behavior but may be unsuitable
#         for embedded systems.
#
#     OFF:
#         Requires explicit handler setup via `eya_runtime_terminate_set()`.
#         Useful for custom termination logic (logging, restarting, etc.).
#
# Note:
#
#     Handler behavior can be overridden at runtime using
#     `eya_runtime_terminate_set()` even when enabled.
#
option(EYA_LIBRARY_OPTION_RUNTIME_TERMINATE_USE_STDLIB
        "Initialize termination handler (m_runtime_terminate) as abort()." ON)

# Option:
#
#     EYA_LIBRARY_OPTION_MEMORY_ALLOCATOR_INIT_ALLOCATED
#
# Description:
#
#     This CMake option determines whether newly allocated memory
#     in the SE project should be zero-initialized.
#
#     When enabled (ON, default), allocated memory blocks
#     are automatically filled with zeros to prevent exposure
#     of uninitialized memory contents.
#
# Usage:
#
#     ON: Zero-initialize allocated memory for security
#         and predictable behavior.
#     OFF: Skip initialization for performance-critical scenarios
#          with manual memory management.
#
# Note:
#
#     Zeroing memory prevents security risks but incurs
#     performance overhead. Disable when optimization is critical.
#
option(EYA_LIBRARY_OPTION_MEMORY_ALLOCATOR_INIT_ALLOCATED
        "Zero-initialize newly allocated memory regions." ON)

# Option:
#
#     EYA_LIBRARY_OPTION_THREAD_LOCAL
#
# Description:
#
#     This CMake option determines whether static variables
#     should be declared with `thread` specifier for thread-local storage.
#
#     When enabled (ON, default), static variables are allocated
#     per-thread, enhancing thread safety by preventing data races.
#
# Usage:
#
#     ON: Use thread-local storage for static variables.
#     OFF: Use standard static variables shared between threads.
#
# Note:
#
#     Thread-local storage improves thread safety but increases
#     memory usage and may affect performance. Choose based on
#     application concurrency requirements.
#
option(EYA_LIBRARY_OPTION_THREAD_LOCAL
        "Use thread modifier for all static variables." ON)

# Option:
#
#     EYA_LIBRARY_OPTION_RUNTIME_EXCEPTION_CATCH_STACK_MAX
#
# Description:
#
#     This CMake option defines the maximum depth of the runtime exception
#     handling stack per thread. It controls the size of the thread-local array
#     `m_runtime_exceptions[]` used to store exception frames.
#
#     The value determines how many nested exceptions can be simultaneously
#     tracked and handled within a single thread.
#
# Usage:
#
#     - Higher values allow deeper exception nesting but consume more memory.
#     - Lower values conserve memory but may cause stack overflow in complex
#       exception handling scenarios.
#     - Must be > 0 (zero would disable exception handling).
#
# Default:
#
#     255 (provides reasonable depth for most applications)
#
# Note:
#
#     The stack is thread-local (THREAD_LOCAL), so this memory is allocated
#     separately for each thread. Consider thread count and memory constraints
#     when adjusting this value.
#
option(EYA_LIBRARY_OPTION_RUNTIME_EXCEPTION_CATCH_STACK_MAX
        "Max stack size for exception catching" 255)

# Option:
#
#     EYA_LIBRARY_OPTION_ARRAY_OPTIMIZE_RESIZE
#
# Description:
#
#     This CMake option controls whether array resizing operations should be optimized
#     to only occur when necessary. The optimization prevents unnecessary memory
#     reallocations when the new size would fit within the current capacity.
#
# Usage:
#
#     ON: Enable resize optimization (only resize when capacity exceeded)
#     OFF: Disable optimization (resize on every call)
#
# Note:
#
#     Disabling optimization (OFF) may impact performance due to frequent reallocations,
#     but ensures minimal memory usage by always resizing to exact requested size.
#
option(EYA_LIBRARY_OPTION_ARRAY_OPTIMIZE_RESIZE
        "Optimize array resizing to only reallocate when capacity is exceeded" ON)

# Option:
#
#     EYA_LIBRARY_OPTION_ARRAY_DEFAULT_SHRINK_RATIO
#
# Description:
#
#     This CMake option defines the default shrink ratio used to determine
#     when to shrink the array capacity. When the array size becomes less than
#     or equal to the current capacity divided by this ratio, the array will
#     be shrunk to fit its current size.
#
# Usage:
#
#     Positive integer value (default: 2)
#     Higher values trigger shrinking more aggressively
#     Lower values make shrinking less frequent
#
# Note:
#
#     Setting this too high may cause frequent reallocations,
#     while setting too low may waste memory with underutilized capacity.
#
option(EYA_LIBRARY_OPTION_ARRAY_DEFAULT_SHRINK_RATIO 2
        "Default ratio for determining when to shrink array capacity")

# Option:
#
#     EYA_LIBRARY_OPTION_ARRAY_DEFAULT_GROWTH_RATIO
#
# Description:
#
#     This CMake option defines the default growth multiplier for array expansion
#     as a fixed-point value where 1000 = 1.0x (no growth).
#     A value of 1500 means the array will grow by 1.5x (1500/1000) of its current capacity.
#
# Usage:
#
#     Positive integer value in per mille (default: 1500 for 1.5x growth)
#     Higher values increase growth factor (more memory, fewer reallocations)
#     Lower values decrease growth factor (less memory, more reallocations)
#
# Note:
#
#     This uses integer arithmetic to avoid floating-point operations,
#     making it suitable for embedded systems.
#
option(EYA_LIBRARY_OPTION_ARRAY_DEFAULT_GROWTH_RATIO
        1500 "Default growth multiplier for array expansion (fixed-point, per mille)")