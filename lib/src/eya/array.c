#include <eya/array.h>

#include <eya/runtime_check_ref.h>
#include <eya/memory_typed.h>
#include <eya/memory_std.h>
#include <eya/ptr_util.h>

/**
 * @def EYA_ARRAY_DEFAULT_GROWTH_RATIO
 * @brief Default growth multiplier for array expansion (fixed-point, per mille)
 *
 * Defines the growth factor as a fixed-point value where 1000 = 1.0x (no growth).
 * A value of 1500 means the array will grow by 1.5x (1500/1000) of its current capacity.
 * Used in integer arithmetic to avoid floating-point operations in embedded systems.
 * Can be redefined before including the header file.
 */
#ifndef EYA_ARRAY_DEFAULT_GROWTH_RATIO
#    define EYA_ARRAY_DEFAULT_GROWTH_RATIO 1500
#endif // EYA_ARRAY_DEFAULT_GROWTH_RATIO

eya_usize_t
eya_array_capacity(const void *self)
{
    return eya_memory_typed_get_size(self);
}

void
eya_array_resize(void *self, eya_usize_t size)
{
    const eya_usize_t capacity = eya_array_capacity(self);
    if (capacity < size)
    {
        eya_allocated_array_resize(self, size);
    }
    eya_ptr_cast(eya_array_t, self)->size = size;
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
eya_array_is_empty(const void *self)
{
    return eya_array_get_size(self) == 0;
}

void
eya_array_clear(void *self)
{
    eya_runtime_check_ref(self);
    eya_ptr_cast(eya_array_t, self)->size = 0;
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

    if (size < capacity)
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
            capacity == 0 ? reserve_size : (capacity * EYA_ARRAY_DEFAULT_GROWTH_RATIO) / 1000;

        eya_allocated_array_resize(self, new_capacity > reserve_size ? new_capacity : reserve_size);
    }
}