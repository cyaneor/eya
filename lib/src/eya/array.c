#include <eya/array.h>

#include <eya/runtime_check_ref.h>
#include <eya/memory_typed.h>
#include <eya/memory_std.h>
#include <eya/ptr_util.h>

eya_usize_t
eya_array_capacity(const void *self)
{
    const eya_usize_t size_in_bytes = eya_allocated_range_get_size(self);
    const eya_usize_t element_size  = eya_memory_typed_get_element_size(self);
    eya_runtime_check(element_size, EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE);

    return size_in_bytes / element_size;
}

void
eya_array_resize(void *self, eya_usize_t size)
{
#if (EYA_LIBRARY_OPTION_ARRAY_OPTIMIZE_RESIZE == EYA_CONFIG_ON)
    const eya_usize_t capacity = eya_array_capacity(self);
    if (capacity < size)
    {
#endif
        eya_allocated_array_resize(self, size);
#if (EYA_LIBRARY_OPTION_ARRAY_OPTIMIZE_RESIZE == EYA_CONFIG_ON)
    }
#endif
    eya_ptr_cast(eya_array_t, self)->size = size;
}

eya_array_t
eya_array_make(eya_usize_t element_size, eya_usize_t size)
{
    eya_array_t _t = {nullptr, nullptr, element_size, 0};
    eya_array_resize(&_t, size);
    return _t;
}

void
eya_array_unpack(const void  *self,
                 void       **begin,
                 void       **end,
                 eya_usize_t *element_size,
                 eya_usize_t *size)
{
    eya_memory_typed_unpack(self, begin, end, element_size);
    if (size)
    {
        *size = eya_ptr_cast(eya_array_t, self)->size;
    }
}

eya_usize_t
eya_array_get_size(const void *self)
{
    eya_usize_t size;
    eya_array_unpack(self, nullptr, nullptr, nullptr, &size);
    return size;
}

bool
eya_array_is_full(const void *self)
{
    return eya_array_get_size(self) == eya_array_capacity(self);
}

bool
eya_array_is_valid_index(const void *self, eya_usize_t index)
{
    const eya_usize_t size = eya_array_get_size(self);
    return index < size;
}

void *
eya_array_at_from_front(const void *self, eya_usize_t index)
{
    eya_runtime_check(eya_array_is_valid_index(self, index), EYA_RUNTIME_ERROR_OUT_OF_RANGE);
    return eya_memory_typed_at_from_front(self, index);
}

void *
eya_array_at_from_back(const void *self, eya_usize_t index)
{
    const eya_usize_t size = eya_array_get_size(self);
    return eya_array_at_from_front(self, size - (index + 1));
}

void *
eya_array_at(const void *self, eya_usize_t index, bool reversed)
{
    return reversed ? eya_array_at_from_back(self, index) : eya_array_at_from_front(self, index);
}

void *
eya_array_front(const void *self)
{
    return eya_array_at(self, 0, false);
}

void *
eya_array_back(const void *self)
{
    return eya_array_at(self, 0, true);
}

bool
eya_array_is_empty(const void *self)
{
    return eya_array_get_size(self) == 0;
}

void
eya_array_clear(void *self)
{
    eya_array_resize(self, 0);
}

void *
eya_array_get_begin(const void *self)
{
    return eya_memory_range_get_begin(self);
}

eya_usize_t
eya_array_get_total_size(const void *self)
{
    const eya_usize_t element_size = eya_memory_typed_get_element_size(self);
    eya_runtime_check(element_size, EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE);

    const eya_usize_t size = eya_array_get_size(self);
    return size * element_size;
}

eya_usize_t
eya_array_get_available_size(const void *self)
{
    eya_usize_t       max_size   = eya_allocated_array_get_max_size(self);
    const eya_usize_t total_size = eya_array_get_total_size(self);

    return max_size - total_size;
}

void *
eya_array_get_end(const void *self)
{
    void             *begin      = eya_array_get_begin(self);
    const eya_usize_t total_size = eya_array_get_total_size(self);
    return eya_ptr_add_by_offset(begin, total_size);
}

void
eya_array_shrink(void *self)
{
    const eya_usize_t capacity = eya_array_capacity(self);
    const eya_usize_t size     = eya_array_get_size(self);

    if (size <= capacity / EYA_LIBRARY_OPTION_ARRAY_DEFAULT_SHRINK_RATIO)
    {
        eya_array_resize(self, size);
    }
}

void
eya_array_reserve(void *self, eya_usize_t size)
{
    const eya_usize_t cur_size = eya_array_get_size(self);
    const eya_usize_t capacity = eya_array_capacity(self);

    const eya_usize_t reserve_size = cur_size + size;
    if (capacity < reserve_size)
    {
        const eya_usize_t new_capacity =
            capacity == 0 ? reserve_size
                          : (capacity * EYA_LIBRARY_OPTION_ARRAY_DEFAULT_GROWTH_RATIO) / 1000;

        eya_allocated_array_resize(self, new_capacity > reserve_size ? new_capacity : reserve_size);
    }
}