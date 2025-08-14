#include <eya/memory_allocator.h>

#include <eya/runtime_check_ref.h>
#include <eya/runtime_return_if.h>
#include <eya/nullptr.h>
#include <eya/memory.h>

eya_memory_allocator_alloc_fn *
eya_memory_allocator_get_alloc_fn(const eya_memory_allocator_t *self)
{
    eya_runtime_check_ref(self);
    return self->alloc_fn;
}

eya_memory_allocator_dealloc_fn *
eya_memory_allocator_get_dealloc_fn(const eya_memory_allocator_t *self)
{
    eya_runtime_check_ref(self);
    return self->dealloc_fn;
}

void *
eya_memory_allocator_alloc(const eya_memory_allocator_t *self, eya_usize_t size)
{
    eya_runtime_check(size, EYA_RUNTIME_ERROR_ZERO_MEMORY_ALLOCATE);

    eya_memory_allocator_alloc_fn *alloc_fn = eya_memory_allocator_get_alloc_fn(self);
    eya_runtime_check(alloc_fn, EYA_RUNTIME_ERROR_ALLOCATOR_FUNCTION_NOT_INITIALIZED);

    void *ptr = alloc_fn(size);
    eya_runtime_check(ptr, EYA_RUNTIME_ERROR_MEMORY_NOT_ALLOCATED);

#if (EYA_LIBRARY_OPTION_MEMORY_ALLOCATOR_INIT_ALLOCATED == EYA_LIBRARY_OPTION_ON)
    eya_memory_set(ptr, size, 0);
#endif

    return ptr;
}

void
eya_memory_allocator_free(const eya_memory_allocator_t *self, void *ptr)
{
    eya_runtime_return_ifn(ptr);

    eya_memory_allocator_dealloc_fn *dealloc_fn = eya_memory_allocator_get_dealloc_fn(self);
    eya_runtime_check(dealloc_fn, EYA_RUNTIME_ERROR_DEALLOCATOR_FUNCTION_NOT_INITIALIZED);

    dealloc_fn(ptr);
}

void *
eya_memory_allocator_realloc(const eya_memory_allocator_t *self,
                             void                         *old_ptr,
                             eya_usize_t                   old_size,
                             eya_usize_t                   new_size)
{
    eya_runtime_return_if(old_size == new_size, old_ptr);
    eya_runtime_return_ifn(old_ptr, eya_memory_allocator_alloc(self, new_size));

    if (new_size == 0)
    {
        eya_memory_allocator_free(self, old_ptr);
        return nullptr;
    }

    void *new_ptr = eya_memory_allocator_alloc(self, new_size);
    eya_memory_copy(new_ptr, new_size, old_ptr, old_size);
    eya_memory_allocator_free(self, old_ptr);

    return new_ptr;
}