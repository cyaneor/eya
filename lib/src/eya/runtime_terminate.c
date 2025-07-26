#include <eya/runtime_terminate.h>

/**
 * @var m_runtime_terminate
 * @brief Pointer to the current emergency termination function
 *
 * Initialized depending on the `EYA_LIBRARY_OPTION_TERMINATE_INIT_STDLIB` option:
 * - If `ON`: set to `abort()` (standard termination from stdlib)
 * - If `OFF`: set to `nullptr` (requires explicit configuration)
 *
 * @note Thread-safe (THREAD_LOCAL), each thread can have its own handler
 * @see eya_runtime_terminate_set()
 */
#ifdef EYA_LIBRARY_OPTION_TERMINATE_INIT_STDLIB
#    include <stdlib.h>
EYA_ATTRIBUTE(THREAD_LOCAL)
eya_runtime_terminate_fn *m_runtime_terminate = abort;
#else
#    include <eya/nullptr.h>
EYA_ATTRIBUTE(THREAD_LOCAL)
eya_runtime_terminate_fn *m_runtime_terminate = nullptr;
#endif

void
eya_runtime_terminate(void)
{
    m_runtime_terminate();
    eya_compiler_unreachable();
}

eya_runtime_terminate_fn *
eya_runtime_terminate_set(eya_runtime_terminate_fn *fn)
{
    eya_runtime_terminate_fn *prev = m_runtime_terminate;
    m_runtime_terminate            = fn;
    return prev;
}