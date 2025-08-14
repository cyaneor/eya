/**
 * @file library_option.h
 * @brief Configuration options for the EYA Library
 *
 * This header file defines all compile-time configurable options for the `EYA Library`.
 * It provides a centralized location for build configuration, memory management settings,
 * array behavior customization, and runtime parameters.
 *
 * The options are organized into logical sections:
 * - Build configuration (static vs shared library)
 * - Memory allocator behavior
 * - Array implementation parameters
 * - Runtime system settings
 */

#ifndef EYA_LIBRARY_OPTION_H
#define EYA_LIBRARY_OPTION_H

// ============================================================================================= //
//                                        LIBRARY OPTIONS                                        //
// ============================================================================================= //

/**
 * @def EYA_LIBRARY_OPTION_OFF
 * @brief Flag indicating disabled/off state
 *
 * This macro defines the value used to represent a disabled or off configuration state.
 * Default value is 0 if not previously defined.
 */
#ifndef EYA_LIBRARY_OPTION_OFF
#    define EYA_LIBRARY_OPTION_OFF 0
#endif // EYA_LIBRARY_OPTION_OFF

/**
 * @def EYA_LIBRARY_OPTION_ON
 * @brief Flag indicating enabled/on state
 *
 * This macro defines the value used to represent an enabled or on configuration state.
 * Default value is 1 if not previously defined.
 */
#ifndef EYA_LIBRARY_OPTION_ON
#    define EYA_LIBRARY_OPTION_ON 1
#endif // EYA_LIBRARY_OPTION_ON

// --------------------------------------------------------------------------------------------- //
//                                             BUILD                                             //
// --------------------------------------------------------------------------------------------- //

/**
 * @def EYA_LIBRARY_OPTION_SHARED_BUILD
 * @brief Configuration macro for shared library build mode
 *
 * @details Determines whether the library is being built as a shared library (DLL/SO).
 *          Defaults to `EYA_LIBRARY_OPTION_OFF` if not explicitly defined.
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
 * @brief Default static library build configuration
 *
 * This macro defines the default value for static library building
 * when not explicitly configured through build system options.
 *
 * - Defaults to `EYA_LIBRARY_OPTION_OFF` if not defined
 * - Can be overridden by build system configuration
 * - Should be checked with #ifdef before use in code
 *
 * Usage example:
 * @code
 * #if EYA_LIBRARY_OPTION_STATIC_BUILD == EYA_LIBRARY_OPTION_ON
 *     // Static library specific code
 * #else
 *     // Shared library or other configuration
 * #endif
 * @endcode
 *
 * @see EYA_LIBRARY_OPTION_SHARED_BUILD for the complementary option
 * @see EYA_LIBRARY_OPTION_OFF for the default value
 * @see EYA_LIBRARY_OPTION_ON for enabled state
 */
#ifndef EYA_LIBRARY_OPTION_STATIC_BUILD
#    define EYA_LIBRARY_OPTION_STATIC_BUILD EYA_LIBRARY_OPTION_ON
#endif // EYA_LIBRARY_OPTION_STATIC_BUILD

// --------------------------------------------------------------------------------------------- //
//                                           ALLOCATOR                                           //
// --------------------------------------------------------------------------------------------- //

/**
 * @def EYA_LIBRARY_OPTION_MEMORY_ALLOCATOR_INIT_ALLOCATED
 * @brief Configuration option for memory initialization behavior
 *
 * Controls whether to fill newly allocated memory
 * with zeros or leave it uninitialized.
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
 *
 * @note Default value is EYA_LIBRARY_OPTION_ON (safe mode with zero-initialization)
 */
#ifndef EYA_LIBRARY_OPTION_MEMORY_ALLOCATOR_INIT_ALLOCATED
#    define EYA_LIBRARY_OPTION_MEMORY_ALLOCATOR_INIT_ALLOCATED EYA_LIBRARY_OPTION_ON
#endif // EYA_LIBRARY_OPTION_MEMORY_ALLOCATOR_INIT_ALLOCATED

/**
 * @def EYA_LIBRARY_OPTION_ARRAY_OPTIMIZE_RESIZE
 * @brief Configuration option for array resize optimization behavior
 *
 * This macro controls whether array resizing operations should be optimized
 * to only occur when necessary. The optimization prevents unnecessary memory
 * reallocations when the new size would fit within the current capacity.
 *
 * @note Default value is EYA_LIBRARY_OPTION_ON if not previously defined.
 * @see eya_array_resize() where this option is implemented
 *
 * @value EYA_LIBRARY_OPTION_ON  Enable resize optimization (only resize when capacity exceeded)
 * @value EYA_LIBRARY_OPTION_OFF Disable optimization (resize on every call)
 *
 * @warning Disabling optimization (EYA_LIBRARY_OPTION_OFF) may impact performance
 *          due to frequent reallocations, but ensures minimal memory usage.
 */
#ifndef EYA_LIBRARY_OPTION_ARRAY_OPTIMIZE_RESIZE
#    define EYA_LIBRARY_OPTION_ARRAY_OPTIMIZE_RESIZE EYA_LIBRARY_OPTION_ON
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
 * Used in integer arithmetic to avoid floating-point operations in embedded systems.
 * Can be redefined before including the header file.
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
 * standard library's malloc/free functions or leave it uninitialized.
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
 * @note Default value is EYA_LIBRARY_OPTION_ON for immediate usability
 * @warning When disabled, using uninitialized allocator will cause undefined behavior
 * @see eya_memory_allocator_t for allocator structure definition
 */
#ifndef EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_USE_STDLIB
#    define EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_USE_STDLIB EYA_LIBRARY_OPTION_ON
#endif // EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_USE_STDLIB

/**
 * @def EYA_LIBRARY_OPTION_RUNTIME_TERMINATE_USE_STDLIB
 * @brief Configuration option for standard library termination behavior
 *
 * Controls whether to initialize the runtime termination handler
 * with standard library's abort() function or set it to null.
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
 * @note Default value is EYA_LIBRARY_OPTION_ON (safe mode with abort())
 * @warning Disabling this may lead to undefined behavior if termination occurs
 *          before custom handler is installed
 */
#ifndef EYA_LIBRARY_OPTION_RUNTIME_TERMINATE_USE_STDLIB
#    define EYA_LIBRARY_OPTION_RUNTIME_TERMINATE_USE_STDLIB EYA_LIBRARY_OPTION_ON
#endif // EYA_LIBRARY_OPTION_RUNTIME_TERMINATE_USE_STDLIB

#endif // EYA_LIBRARY_OPTION_H
