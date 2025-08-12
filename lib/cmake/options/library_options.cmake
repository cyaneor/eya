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