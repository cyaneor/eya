#include <eya/runtime_allocator.h>

/**
 * @brief Defines a thread-local runtime memory allocator,
 *        initialized with standard library functions if needed.
 *
 * This code defines a global variable `m_runtime_allocator`
 * as a thread-local instance of the `eya_memory_allocator` structure.
 *
 * The allocator initialization depends on whether
 * `EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_INIT_STDLIB` is defined:
 *
 * - If `EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_INIT_STDLIB` is defined,
 *   the allocator is initialized using the standard library's `malloc`
 *   for memory allocation and `free` for memory deallocation.
 *
 * - If `EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_INIT_STDLIB` is not defined,
 *   the memory allocation and deallocation functions are initialized as `nullptr`.
 *
 * This provides flexibility in runtime allocator configuration,
 * supporting both standard and custom memory management strategies.
 *
 * @note The allocator is marked as `THREAD_LOCAL`, meaning
 *       that each thread will have its own instance
 *       of `m_runtime_allocator`.
 */
#ifdef EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_INIT_STDLIB
#    include <stdlib.h>

EYA_ATTRIBUTE(THREAD_LOCAL)
eya_memory_allocator_t m_runtime_allocator = {malloc, free};
#else
EYA_ATTRIBUTE(THREAD_LOCAL)
eya_memory_allocator_t m_runtime_allocator = {};
#endif // EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_INIT_STDLIB

eya_memory_allocator_t *
eya_runtime_allocator()
{
    return &m_runtime_allocator;
}
