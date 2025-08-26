#include <eya/allocated_range.h>

#include <eya/runtime_allocator.h>
#include <eya/memory_range.h>

eya_usize_t
eya_allocated_range_get_size(const eya_allocated_range_t *self)
{
    return eya_memory_range_is_uninit(self) ? 0 : eya_memory_range_get_size(self);
}

void
eya_allocated_range_clear(eya_allocated_range_t *self)
{
    eya_memory_allocator_t *allocator = eya_runtime_allocator();

    void *ptr = eya_memory_range_get_begin(self);
    eya_memory_allocator_free(allocator, ptr);
    eya_memory_range_clear(self);
}

void
eya_allocated_range_exchange(eya_allocated_range_t *self, eya_allocated_range_t *other)
{
    eya_allocated_range_clear(self);
    eya_memory_range_swap(self, other);
}

void
eya_allocated_range_resize(eya_allocated_range_t *self, eya_usize_t size)
{
    eya_memory_allocator_t *allocator = eya_runtime_allocator();
    void                   *old_ptr   = eya_memory_range_get_begin(self);
    eya_usize_t             cur_size  = eya_allocated_range_get_size(self);

    void *new_ptr = eya_memory_allocator_realloc(allocator, old_ptr, cur_size, size);
    eya_memory_range_reset_f(self, new_ptr, size);
}