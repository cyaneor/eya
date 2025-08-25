#include <eya/runtime_allocator.h>

#if (EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_USE_STDLIB == EYA_LIBRARY_OPTION_ON)
#    include <stdlib.h>
#    include <eya/ptr_util.h>

EYA_ATTRIBUTE(THREAD_LOCAL)
eya_memory_allocator_t m_runtime_allocator = {(eya_memory_allocator_alloc_fn *)malloc,
                                              (eya_memory_allocator_dealloc_fn *)free};
#elif (EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_USE_STDLIB == EYA_LIBRARY_OPTION_OFF)
EYA_ATTRIBUTE(THREAD_LOCAL)
eya_memory_allocator_t m_runtime_allocator = {};
#endif // EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_INIT_STDLIB

eya_memory_allocator_t *
eya_runtime_allocator()
{
    return &m_runtime_allocator;
}
