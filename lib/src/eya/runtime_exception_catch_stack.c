#include <eya/runtime_exception_catch_stack.h>

#include <eya/nullptr.h>
#include <eya/static_assert.h>

eya_static_assert(EYA_LIBRARY_OPTION_RUNTIME_EXCEPTION_CATCH_STACK_MAX,
                  "Zero stack depth makes exception handling impossible.");

/**
 * @var eya_exception_catch_t *m_runtime_exceptions
 * @brief Array of exception frames for runtime exception handling
 *
 * This array stores pointers to exception frames used by the exception handling mechanism.
 * Each thread has its own copy of the array due to the THREAD_LOCAL attribute.
 *
 * This value defines the maximum number of
 * simultaneously handled exceptions per thread.
 *
 * @note Initialized with null pointers upon creation
 */
EYA_ATTRIBUTE(THREAD_LOCAL)
eya_exception_catch_t *m_runtime_exceptions[EYA_LIBRARY_OPTION_RUNTIME_EXCEPTION_CATCH_STACK_MAX];

/**
 * @var eya_exception_catch_t **m_runtime_exception
 * @brief Pointer to the current active exception frame
 *
 * Used to track the current exception context in a thread.
 * The THREAD_LOCAL attribute ensures thread safety.
 *
 * @note Initialized with a null pointer (nullptr)
 */
EYA_ATTRIBUTE(THREAD_LOCAL)
eya_exception_catch_t **m_runtime_exception = nullptr;

eya_exception_catch_t *
eya_runtime_exception_catch_stack_get_current(void)
{
    return *m_runtime_exception;
}

bool
eya_runtime_exception_catch_stack_is_begin(void)
{
    return m_runtime_exception == m_runtime_exceptions;
}

bool
eya_runtime_exception_catch_stack_is_end(void)
{
    return m_runtime_exception ==
           &m_runtime_exceptions[EYA_LIBRARY_OPTION_RUNTIME_EXCEPTION_CATCH_STACK_MAX];
}

eya_exception_catch_t *
eya_runtime_exception_catch_stack_next(void)
{
    if (!eya_runtime_exception_catch_stack_is_end())
    {
        m_runtime_exception++;
        return *m_runtime_exception;
    }
    return nullptr;
}

eya_exception_catch_t *
eya_runtime_exception_catch_stack_prev(void)
{
    if (!eya_runtime_exception_catch_stack_is_begin())
    {
        m_runtime_exception--;
        return *m_runtime_exception;
    }
    return nullptr;
}

eya_exception_catch_t *
eya_runtime_exception_catch_stack_push(eya_exception_catch_t *e)
{
    if (!eya_runtime_exception_catch_stack_is_end())
    {
        *m_runtime_exception = e;
        eya_runtime_exception_catch_stack_next();
        return e;
    }
    return nullptr;
}

eya_compiler_constructor(eya_runtime_exception_catch_stack_init)
{
    m_runtime_exception = m_runtime_exceptions;
}

eya_compiler_destructor(eya_runtime_exception_catch_stack_deinit)
{
    m_runtime_exception = nullptr;
}