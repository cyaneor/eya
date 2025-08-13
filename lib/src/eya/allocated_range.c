#include <eya/allocated_range.h>

#include <eya/runtime_allocator.h>
#include <eya/memory_range.h>

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
    void                   *old_ptr   = eya_memory_range_get_begin(self);
    const eya_usize_t       cur_size  = eya_memory_range_get_size(self);
    eya_memory_allocator_t *allocator = eya_runtime_allocator();

    void *new_ptr = eya_memory_allocator_realloc(allocator, old_ptr, cur_size, size);
    eya_memory_range_set_by_size_f(self, new_ptr, size);
}