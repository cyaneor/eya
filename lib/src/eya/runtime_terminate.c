#include <eya/runtime_terminate.h>

#if (EYA_LIBRARY_OPTION_RUNTIME_TERMINATE_INIT_STDLIB == EYA_CONFIG_ON)
#    include <stdlib.h>
EYA_ATTRIBUTE(THREAD_LOCAL)
eya_runtime_terminate_fn *m_runtime_terminate = abort;
#elif (EYA_LIBRARY_OPTION_RUNTIME_TERMINATE_INIT_STDLIB == EYA_CONFIG_OFF)
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