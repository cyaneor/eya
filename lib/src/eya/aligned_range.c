#include <eya/aligned_range.h>

#include <eya/runtime_allocator.h>
#include <eya/memory_range.h>

void
eya_aligned_range_clear(eya_aligned_range_t *self)
{
    eya_memory_allocator_t *allocator = eya_runtime_allocator();

    void *ptr = eya_memory_range_get_begin(self);
    eya_memory_allocator_align_free(allocator, ptr);
    eya_memory_range_clear(self);
}

void
eya_aligned_range_exchange(eya_aligned_range_t *self, eya_aligned_range_t *other)
{
    eya_aligned_range_clear(self);
    eya_memory_range_swap(self, other);
}

void
eya_aligned_range_resize(eya_aligned_range_t *self, eya_usize_t size, eya_usize_t alignment_size)
{
    void                   *old_ptr   = eya_memory_range_get_begin(self);
    const eya_usize_t       cur_size  = eya_memory_range_get_size(self);
    eya_memory_allocator_t *allocator = eya_runtime_allocator();

    void *new_ptr =
        eya_memory_allocator_align_realloc(allocator, old_ptr, cur_size, size, alignment_size);
    
    eya_memory_range_set_by_size_v(self, new_ptr, size);
}