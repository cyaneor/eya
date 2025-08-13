#include <eya/allocated_range.h>

#include <eya/runtime_allocator.h>
#include <eya/memory_range.h>
#include <eya/runtime_try.h>

eya_usize_t
eya_allocated_range_get_size(const void *self)
{
    eya_runtime_try(e)
    {
        const eya_usize_t size = eya_memory_range_get_size(self);
        eya_runtime_try_return(size);
    }
    return 0;
}

void
eya_allocated_range_clear(void *self)
{
    eya_memory_allocator_t *allocator = eya_runtime_allocator();

    void *ptr = eya_memory_range_get_begin(self);
    eya_memory_allocator_free(allocator, ptr);
    eya_memory_range_clear(self);
}

void
eya_allocated_range_exchange(void *self, void *other)
{
    eya_allocated_range_clear(self);
    eya_memory_range_swap(self, other);
}

void
eya_allocated_range_resize(void *self, eya_usize_t size)
{
    eya_memory_allocator_t *allocator = eya_runtime_allocator();
    void                   *old_ptr   = eya_memory_range_get_begin(self);
    eya_usize_t             cur_size  = eya_allocated_range_get_size(self);

    void *new_ptr = eya_memory_allocator_realloc(allocator, old_ptr, cur_size, size);
    eya_memory_range_set_by_size_f(self, new_ptr, size);
}