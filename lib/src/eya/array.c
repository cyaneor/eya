#include <eya/array.h>

#include <eya/allocated_array_initializer.h>
#include <eya/array_initializer.h>
#include <eya/runtime_check_ref.h>
#include <eya/memory_typed.h>
#include <eya/memory_std.h>
#include <eya/ptr_util.h>

void
eya_array_unpack(const eya_array_t *self,
                 void             **begin,
                 void             **end,
                 eya_usize_t       *element_size,
                 eya_usize_t       *size)
{
    eya_memory_typed_unpack_full(
        eya_ptr_rcast(const eya_memory_typed_t, self), begin, end, element_size);

    if (size)
    {
        *size = self->size;
    }
}

eya_usize_t
eya_array_capacity(const eya_array_t *self)
{
    return eya_allocated_array_get_size(eya_ptr_rcast(const eya_allocated_array_t, self));
}

eya_usize_t
eya_array_get_size(const eya_array_t *self)
{
    eya_usize_t size;
    eya_array_unpack(self, nullptr, nullptr, nullptr, &size);
    return size;
}

bool
eya_array_is_full(const eya_array_t *self)
{
    return eya_array_get_size(self) == eya_array_capacity(self);
}

bool
eya_array_is_valid_index(const eya_array_t *self, eya_usize_t index)
{
    const eya_usize_t size = eya_array_get_size(self);
    return index < size;
}

void *
eya_array_at_from_front(const eya_array_t *self, eya_usize_t index)
{
    eya_runtime_check(eya_array_is_valid_index(self, index), EYA_RUNTIME_ERROR_OUT_OF_RANGE);
    return eya_memory_typed_at_from_front(eya_ptr_rcast(const eya_memory_typed_t, self), index);
}

void *
eya_array_at_from_back(const eya_array_t *self, eya_usize_t index)
{
    const eya_usize_t size = eya_array_get_size(self);
    return eya_array_at_from_front(self, size - (index + 1));
}

void *
eya_array_at(const eya_array_t *self, eya_usize_t index, bool reversed)
{
    return reversed ? eya_array_at_from_back(self, index) : eya_array_at_from_front(self, index);
}

void *
eya_array_front(const eya_array_t *self)
{
    return eya_array_at(self, 0, false);
}

void *
eya_array_back(const eya_array_t *self)
{
    return eya_array_at(self, 0, true);
}

bool
eya_array_is_empty(const eya_array_t *self)
{
    return eya_array_get_size(self) == 0;
}

void
eya_array_clear(eya_array_t *self)
{
    eya_array_resize(self, 0);
}

void *
eya_array_get_begin(const eya_array_t *self)
{
    return eya_memory_range_get_begin(eya_ptr_rcast(const eya_memory_range_t, self));
}

eya_usize_t
eya_array_get_total_size(const eya_array_t *self)
{
    const eya_usize_t element_size =
        eya_memory_typed_get_element_size(eya_ptr_rcast(const eya_memory_typed_t, self));

    eya_runtime_check(element_size, EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE);

    const eya_usize_t size = eya_array_get_size(self);
    return size * element_size;
}

eya_usize_t
eya_array_get_available_size(const eya_array_t *self)
{
    eya_usize_t max_size =
        eya_allocated_array_get_max_size(eya_ptr_rcast(const eya_allocated_array_t, self));

    const eya_usize_t total_size = eya_array_get_total_size(self);
    return max_size - total_size;
}

void *
eya_array_get_end(const eya_array_t *self)
{
    void             *begin      = eya_array_get_begin(self);
    const eya_usize_t total_size = eya_array_get_total_size(self);
    return eya_ptr_add_by_offset(begin, total_size);
}

void
eya_array_shrink(eya_array_t *self)
{
    const eya_usize_t capacity = eya_array_capacity(self);
    const eya_usize_t size     = eya_array_get_size(self);

    if (size <= capacity / EYA_LIBRARY_OPTION_ARRAY_DEFAULT_SHRINK_RATIO)
    {
        eya_array_resize(self, size);
    }
}

void
eya_array_reserve(eya_array_t *self, eya_usize_t size)
{
    const eya_usize_t cur_size     = eya_array_get_size(self);
    const eya_usize_t capacity     = eya_array_capacity(self);
    eya_usize_t       reserve_size = cur_size + size;

    if (capacity < reserve_size)
    {
#if (EYA_LIBRARY_OPTION_ARRAY_RESERVE_OPTIMIZE == EYA_LIBRARY_OPTION_ON)
        /* Standard mode: smart growth with coefficient */
        reserve_size = capacity == 0
                           ? reserve_size
                           : (reserve_size * EYA_LIBRARY_OPTION_ARRAY_DEFAULT_GROWTH_RATIO) / 1000;

#endif
        eya_allocated_array_resize(eya_ptr_rcast(eya_allocated_array_t, self), reserve_size);
    }
}

void
eya_array_resize(eya_array_t *self, eya_usize_t size)
{
#if (EYA_LIBRARY_OPTION_ARRAY_OPTIMIZE_RESIZE == EYA_LIBRARY_OPTION_ON)
    const eya_usize_t capacity = eya_array_capacity(self);
    if (capacity < size)
    {
#endif
        eya_allocated_array_resize(eya_ptr_rcast(eya_allocated_array_t, self), size);
#if (EYA_LIBRARY_OPTION_ARRAY_OPTIMIZE_RESIZE == EYA_LIBRARY_OPTION_ON)
    }
#endif
    self->size = size;
}

eya_array_t
eya_array_make(eya_usize_t element_size, eya_usize_t size)
{
    eya_runtime_check(element_size, EYA_RUNTIME_ERROR_INVALID_ARGUMENT);
    eya_array_t _t = eya_array_initializer(eya_allocated_array_initializer(element_size));
    if (size)
    {
        eya_array_resize(&_t, size);
    }
    return _t;
}

void
eya_array_free(eya_array_t *self)
{
    eya_allocated_array_resize(eya_ptr_rcast(eya_allocated_array_t, self), 0);
    self->size = 0;
}