#include <eya/memory_allocator.h>

#include <eya/runtime_check_ref.h>
#include <eya/runtime_return_if.h>
#include <eya/ptr_util.h>
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
    eya_runtime_check(self, EYA_RUNTIME_ERROR_ZERO_MEMORY_SIZE);

    eya_memory_allocator_alloc_fn *alloc_fn = eya_memory_allocator_get_alloc_fn(self);
    eya_runtime_check(alloc_fn, EYA_RUNTIME_ERROR_ALLOCATOR_FUNCTION_NOT_INITIALIZED);

    void *ptr = alloc_fn(size);

#if EYA_LIBRARY_OPTION_FILL_ZERO_AFTER_MEMORY_ALLOCATE
    // Если включена опция заполнения нулями после выделения памяти,
    // заполняем выделенную память нулями от указателя ptr до конца выделенной области
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
    eya_runtime_check(new_ptr, EYA_RUNTIME_ERROR_MEMORY_NOT_ALLOCATED);

    eya_memory_copy(new_ptr, new_size, old_ptr, old_size);
    eya_memory_allocator_free(self, old_ptr);

    return new_ptr;
}

void *
eya_memory_allocator_align_alloc(const eya_memory_allocator_t *self,
                                 eya_usize_t                   size,
                                 eya_usize_t                   alignment_size)
{
    eya_runtime_check(eya_math_is_power_of_two(alignment_size), EYA_RUNTIME_ERROR_NOT_POWER_OF_TWO);
    eya_usize_t alignment_offset = EYA_VOID_P_SIZE + eya_math_sub_one(alignment_size);

    void *unaligned_ptr = eya_memory_allocator_alloc(self, size + alignment_offset);
    eya_runtime_check(unaligned_ptr, EYA_RUNTIME_ERROR_MEMORY_NOT_ALLOCATED);

    void *offset_ptr  = eya_ptr_add_offset_unsafe(void, unaligned_ptr, alignment_offset);
    void *aligned_ptr = eya_addr_to_ptr(void, eya_ptr_align_down(offset_ptr, alignment_size));
    ((void **)aligned_ptr)[-1] = unaligned_ptr;

    return aligned_ptr;
}

void
eya_memory_allocator_align_free(const eya_memory_allocator_t *self, void *ptr)
{
    eya_runtime_check_ref(ptr);

    void *unaligned_ptr = ((void **)ptr)[-1];
    eya_memory_allocator_free(self, unaligned_ptr);
}

void *
eya_memory_allocator_align_realloc(const eya_memory_allocator_t *self,
                                   void                         *old_ptr,
                                   eya_usize_t                   old_size,
                                   eya_usize_t                   new_size,
                                   eya_usize_t                   alignment_size)
{
    eya_runtime_return_if(old_size == new_size, old_ptr);
    eya_runtime_return_ifn(old_ptr,
                           eya_memory_allocator_align_alloc(self, new_size, alignment_size));

    if (new_size == 0)
    {
        eya_memory_allocator_align_free(self, old_ptr);
        return nullptr;
    }

    void *new_ptr = eya_memory_allocator_align_alloc(self, new_size, alignment_size);
    eya_runtime_check(new_ptr, EYA_RUNTIME_ERROR_MEMORY_NOT_ALLOCATED);

    eya_memory_copy(new_ptr, new_size, old_ptr, old_size);
    eya_memory_allocator_align_free(self, old_ptr);

    return new_ptr;
}