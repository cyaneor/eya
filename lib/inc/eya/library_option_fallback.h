/**
 * @file library_option_fallback.h
 * @brief Complete library configuration system
 *
 * This header contains all configurable options for the library,
 * organized into logical sections.
 *
 * It builds upon the core definitions from library_option.h
 * to provide a complete configuration system.
 *
 * Configuration sections:
 * 1. Build options - Static vs shared library compilation
 * 2. Allocator behavior - Memory management customization
 * 3. Array parameters - Customization of array implementation
 * 4. Runtime settings - Exception handling and system behavior
 *
 * All options are disabled by default for maximum control and minimal footprint.
 * Each option is thoroughly documented with its effects and considerations.
 *
 * @see library_option.h for the core definitions and basic options
 */

#ifndef EYA_LIBRARY_OPTION_FALLBACK_H
#define EYA_LIBRARY_OPTION_FALLBACK_H

#include "library_option.h"

// --------------------------------------------------------------------------------------------- //
//                                             BUILD                                             //
// --------------------------------------------------------------------------------------------- //

/**
 * @def EYA_LIBRARY_OPTION_SHARED_BUILD
 * @brief Configuration macro for shared library build mode
 *
 * @details Determines whether the library is being built as a shared library (DLL/SO).
 *          Defaults to `EYA_LIBRARY_OPTION_OFF` (disabled).
 *
 * When enabled (`EYA_LIBRARY_OPTION_ON`):
 * - Symbols are marked for export/import depending on build context
 * - Requires proper compiler attributes for shared library visibility
 *
 * @note Mutually exclusive with static build mode.
 *       Should not be enabled simultaneously with `EYA_LIBRARY_OPTION_STATIC_BUILD`.
 *
 * @see EYA_ATTRIBUTE_SYMBOL
 */
#ifndef EYA_LIBRARY_OPTION_SHARED_BUILD
#    define EYA_LIBRARY_OPTION_SHARED_BUILD EYA_LIBRARY_OPTION_OFF
#endif // EYA_LIBRARY_OPTION_SHARED_BUILD

/**
 * @def EYA_LIBRARY_OPTION_STATIC_BUILD
 * @brief Static library build configuration
 *
 * This macro defines whether to build as a static library.
 * Defaults to `EYA_LIBRARY_OPTION_OFF` (disabled).
 *
 * @see EYA_LIBRARY_OPTION_SHARED_BUILD for the complementary option
 * @see EYA_LIBRARY_OPTION_OFF for the default value
 * @see EYA_LIBRARY_OPTION_ON for enabled state
 */
#ifndef EYA_LIBRARY_OPTION_STATIC_BUILD
#    define EYA_LIBRARY_OPTION_STATIC_BUILD EYA_LIBRARY_OPTION_OFF
#endif // EYA_LIBRARY_OPTION_STATIC_BUILD

// --------------------------------------------------------------------------------------------- //
//                                            THREAD                                             //
// --------------------------------------------------------------------------------------------- //

/**
 * @def EYA_LIBRARY_OPTION_THREAD_LOCAL
 * @brief Controls whether thread-local storage is enabled in the library
 *
 * @details Defaults to `EYA_LIBRARY_OPTION_OFF` (disabled) for maximum compatibility.
 *
 * When enabled (EYA_LIBRARY_OPTION_ON):
 * - Certain library variables will be declared as thread-local
 * - Each thread gets its own copy of these variables
 * - Requires compiler support for thread-local storage
 *
 * When disabled (EYA_LIBRARY_OPTION_OFF):
 * - All threads share the same global variables
 * - May improve performance on systems without efficient TLS support
 *
 * @note Requires C11 or compiler-specific TLS support (like __thread or __declspec(thread))
 * @see EYA_ATTRIBUTE_THREAD_LOCAL for the actual implementation macro
 */
#ifndef EYA_LIBRARY_OPTION_THREAD_LOCAL
#    define EYA_LIBRARY_OPTION_THREAD_LOCAL EYA_LIBRARY_OPTION_OFF
#endif

// --------------------------------------------------------------------------------------------- //
//                                           ALLOCATOR                                           //
// --------------------------------------------------------------------------------------------- //

/**
 * @def EYA_LIBRARY_OPTION_MEMORY_ALLOCATOR_INIT_ALLOCATED
 * @brief Configuration option for memory initialization behavior
 *
 * Controls whether to fill newly allocated memory
 * with zeros or leave it uninitialized.
 * Defaults to `EYA_LIBRARY_OPTION_OFF` (uninitialized memory).
 *
 * When enabled (EYA_LIBRARY_OPTION_ON):
 * - All allocated memory will be initialized to zero
 * - Provides safer operation with predictable initial values
 * - Prevents exposure of potentially sensitive data
 *
 * When disabled (EYA_LIBRARY_OPTION_OFF):
 * - Memory contents remain undefined after allocation
 * - Provides faster allocation performance
 * - Requires explicit initialization by the user
 */
#ifndef EYA_LIBRARY_OPTION_MEMORY_ALLOCATOR_INIT_ALLOCATED
#    define EYA_LIBRARY_OPTION_MEMORY_ALLOCATOR_INIT_ALLOCATED EYA_LIBRARY_OPTION_OFF
#endif // EYA_LIBRARY_OPTION_MEMORY_ALLOCATOR_INIT_ALLOCATED

/**
 * @def EYA_LIBRARY_OPTION_ARRAY_OPTIMIZE_RESIZE
 * @brief Configuration option for array resize optimization behavior
 *
 * This macro controls whether array resizing operations should be optimized
 * to only occur when necessary. Defaults to `EYA_LIBRARY_OPTION_OFF` (disabled).
 *
 * @see eya_array_resize() where this option is implemented
 *
 * - EYA_LIBRARY_OPTION_ON  Enable resize optimization (only resize when capacity exceeded)
 * - EYA_LIBRARY_OPTION_OFF Disable optimization (resize on every call)
 *
 * @warning Disabling optimization (EYA_LIBRARY_OPTION_OFF) may impact performance
 *          due to frequent reallocations, but ensures minimal memory usage.
 */
#ifndef EYA_LIBRARY_OPTION_ARRAY_OPTIMIZE_RESIZE
#    define EYA_LIBRARY_OPTION_ARRAY_OPTIMIZE_RESIZE EYA_LIBRARY_OPTION_OFF
#endif // EYA_LIBRARY_OPTION_ARRAY_OPTIMIZE_RESIZE

// --------------------------------------------------------------------------------------------- //
//                                             ARRAY                                             //
// --------------------------------------------------------------------------------------------- //

/**
 * @def EYA_LIBRARY_OPTION_ARRAY_DEFAULT_SHRINK_RATIO
 * @brief Default ratio used to determine when to shrink the array capacity
 *
 * This macro defines the default shrink ratio used by eya_array_shrink().
 * When the array size becomes less than or equal to the current capacity divided by this ratio,
 * the array will be shrunk to fit its current size.
 * Default value is 2 (disabled automatic shrinking).
 */
#ifndef EYA_LIBRARY_OPTION_ARRAY_DEFAULT_SHRINK_RATIO
#    define EYA_LIBRARY_OPTION_ARRAY_DEFAULT_SHRINK_RATIO 2
#endif // EYA_LIBRARY_OPTION_ARRAY_DEFAULT_SHRINK_RATIO

/**
 * @def EYA_LIBRARY_OPTION_ARRAY_DEFAULT_GROWTH_RATIO
 * @brief Default growth multiplier for array expansion (fixed-point, per mille)
 *
 * Defines the growth factor as a fixed-point value where 1000 = 1.0x (no growth).
 * A value of 1500 means the array will grow by 1.5x (1500/1000) of its current capacity.
 * Default value is 1500 (1.5x growth factor).
 * Used in integer arithmetic to avoid floating-point operations in embedded systems.
 */
#ifndef EYA_LIBRARY_OPTION_ARRAY_DEFAULT_GROWTH_RATIO
#    define EYA_LIBRARY_OPTION_ARRAY_DEFAULT_GROWTH_RATIO 1500
#endif // EYA_LIBRARY_OPTION_ARRAY_DEFAULT_GROWTH_RATIO

// --------------------------------------------------------------------------------------------- //
//                                            RUNTIME                                            //
// --------------------------------------------------------------------------------------------- //

/**
 * @def EYA_LIBRARY_OPTION_RUNTIME_EXCEPTION_CATCH_STACK_MAX
 * @brief Maximum depth of the exception handling stack
 *
 * Defines the maximum number of simultaneously handled exceptions per thread.
 * Default value is 255 if not otherwise defined.
 *
 * @warning Changing this value may affect per-thread memory consumption,
 *          since the m_runtime_exceptions array has THREAD_LOCAL storage.
 */
#ifndef EYA_LIBRARY_OPTION_RUNTIME_EXCEPTION_CATCH_STACK_MAX
#    define EYA_LIBRARY_OPTION_RUNTIME_EXCEPTION_CATCH_STACK_MAX 255
#endif // EYA_LIBRARY_OPTION_RUNTIME_EXCEPTION_CATCH_STACK_MAX

/**
 * @def EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_USE_STDLIB
 * @brief Configuration option for default runtime allocator initialization
 *
 * Controls whether to initialize the thread-local runtime allocator with
 * standard library's malloc/free functions. Defaults to `EYA_LIBRARY_OPTION_OFF` (disabled).
 *
 * When enabled (EYA_LIBRARY_OPTION_ON):
 * - Includes <stdlib.h> and pointer utilities
 * - Initializes allocator with standard malloc() and free()
 * - Provides immediate out-of-the-box memory allocation capability
 *
 * When disabled (EYA_LIBRARY_OPTION_OFF):
 * - Leaves allocator uninitialized (zero-initialized)
 * - Requires manual allocator setup before use
 * - Useful for custom memory management scenarios
 *
 * @warning When disabled, using uninitialized allocator will cause undefined behavior
 * @see eya_memory_allocator_t for allocator structure definition
 */
#ifndef EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_USE_STDLIB
#    define EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_USE_STDLIB EYA_LIBRARY_OPTION_OFF
#endif // EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_USE_STDLIB

/**
 * @def EYA_LIBRARY_OPTION_RUNTIME_TERMINATE_USE_STDLIB
 * @brief Configuration option for standard library termination behavior
 *
 * Controls whether to initialize the runtime termination handler
 * with standard library's abort() function. Defaults to `EYA_LIBRARY_OPTION_OFF` (disabled).
 *
 * When enabled (EYA_LIBRARY_OPTION_ON):
 * - Includes <stdlib.h>
 * - Sets default termination handler to abort()
 * - Provides immediate termination on critical errors
 *
 * When disabled (EYA_LIBRARY_OPTION_OFF):
 * - Includes null pointer definition
 * - Sets default termination handler to nullptr
 * - Allows custom termination handler setup
 *
 * @warning Disabling this may lead to undefined behavior if termination occurs
 *          before custom handler is installed
 */
#ifndef EYA_LIBRARY_OPTION_RUNTIME_TERMINATE_USE_STDLIB
#    define EYA_LIBRARY_OPTION_RUNTIME_TERMINATE_USE_STDLIB EYA_LIBRARY_OPTION_OFF
#endif // EYA_LIBRARY_OPTION_RUNTIME_TERMINATE_USE_STDLIB

#endif // EYA_LIBRARY_OPTION_FALLBACK_H