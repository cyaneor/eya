#include <eya/memory_typed.h>

#include <eya/runtime_check_ref.h>
#include <eya/ptr_util.h>

void
eya_memory_typed_unpack(const void *self, void **begin, void **end, eya_usize_t *element_size)
{
    eya_memory_range_unpack(self, begin, end);
    if (element_size)
    {
        *element_size = eya_ptr_cast(eya_memory_typed_t, self)->element_size;
    }
}

eya_usize_t
eya_memory_typed_get_element_size(const void *self)
{
    eya_usize_t element_size;
    eya_memory_typed_unpack(self, nullptr, nullptr, &element_size);
    return element_size;
}

bool
eya_memory_typed_is_valid(const void *self)
{
    const eya_usize_t element_size = eya_memory_typed_get_element_size(self);
    return eya_memory_range_is_multiple_of_size(self, element_size);
}

eya_usize_t
eya_memory_typed_get_size(const void *self)
{
    eya_runtime_check(eya_memory_typed_is_valid(self),
                      EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE);

    const eya_usize_t size         = eya_memory_range_get_size(self);
    const eya_usize_t element_size = eya_memory_typed_get_element_size(self);

    return size / element_size;
}

bool
eya_memory_typed_is_empty(const void *self)
{
    return eya_memory_typed_get_size(self) == 0;
}

void
eya_memory_typed_swap(void *self, void *other)
{
    eya_runtime_check(eya_memory_typed_is_equal_element_size(self, other),
                      EYA_RUNTIME_ERROR_DIFFERENT_ELEMENT_SIZE);

    eya_memory_range_swap(self, other);
}

void
eya_memory_typed_exchange(void *self, void *other)
{
    eya_runtime_check(eya_memory_typed_is_equal_element_size(self, other),
                      EYA_RUNTIME_ERROR_DIFFERENT_ELEMENT_SIZE);

    eya_memory_range_exchange(self, other);
}

bool
eya_memory_range_is_valid_index(const void *self, eya_usize_t index)
{
    const eya_usize_t size = eya_memory_typed_get_size(self);
    return index < size;
}

eya_uoffset_t
eya_memory_typed_get_offset_by_index(const void *self, eya_usize_t index)
{
    eya_runtime_check(eya_memory_range_is_valid_index(self, index), EYA_RUNTIME_ERROR_OUT_OF_RANGE);
    const eya_usize_t element_size = eya_memory_typed_get_element_size(self);
    return index * element_size;
}

void *
eya_memory_typed_at_from_front(const void *self, eya_usize_t index)
{
    const eya_uoffset_t offset = eya_memory_typed_get_offset_by_index(self, index);
    return eya_memory_range_at_from_front(self, offset);
}

void *
eya_memory_typed_at_from_back(const void *self, eya_usize_t index)
{
    const eya_usize_t size = eya_memory_typed_get_size(self);
    return eya_memory_typed_at_from_front(self, size - (index + 1));
}

void *
eya_memory_typed_at(const void *self, eya_usize_t index, bool reversed)
{
    return reversed ? eya_memory_typed_at_from_back(self, index)
                    : eya_memory_typed_at_from_front(self, index);
}

void *
eya_memory_typed_front(const void *self)
{
    return eya_memory_typed_at(self, 0, false);
}

void *
eya_memory_typed_back(const void *self)
{
    return eya_memory_typed_at(self, 0, true);
}

bool
eya_memory_typed_is_equal_element_size_to(const void *self, eya_usize_t element_size)
{
    return eya_memory_typed_get_element_size(self) == element_size;
}

bool
eya_memory_typed_is_equal_element_size(const void *self, const void *other)
{
    const eya_usize_t element_size = eya_memory_typed_get_element_size(other);
    return eya_memory_typed_is_equal_element_size_to(self, element_size);
}

bool
eya_memory_typed_is_equal(const void *self, const void *other)
{
    return eya_memory_typed_is_equal_element_size(self, other) &&
           eya_memory_range_is_equal(self, other);
}