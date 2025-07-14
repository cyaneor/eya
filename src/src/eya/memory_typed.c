#include <eya/memory_typed.h>

#include <eya/runtime_check_ref.h>
#include <eya/ptr_util.h>

eya_memory_range_t *
eya_memory_typed_get_range(const eya_memory_typed_t *self)
{
    return eya_ptr_cast(eya_memory_range_t, self);
}

void
eya_memory_typed_unpack(const eya_memory_typed_t *self,
                        void                    **begin,
                        void                    **end,
                        eya_usize_t              *element_size)
{
    const eya_memory_range_t *range = eya_memory_typed_get_range(self);
    eya_memory_range_unpack(range, begin, end);

    if (element_size)
    {
        *element_size = self->element_size;
    }
}

eya_usize_t
eya_memory_typed_get_element_size(const eya_memory_typed_t *self)
{
    eya_usize_t element_size;
    eya_memory_typed_unpack(self, nullptr, nullptr, &element_size);
    return element_size;
}

bool
eya_memory_typed_is_valid(const eya_memory_typed_t *self)
{
    const eya_usize_t         element_size = eya_memory_typed_get_element_size(self);
    const eya_memory_range_t *range        = eya_memory_typed_get_range(self);
    return eya_memory_range_is_multiple_of_size(range, element_size);
}

eya_usize_t
eya_memory_typed_get_size(const eya_memory_typed_t *self)
{
    eya_runtime_check(eya_memory_typed_is_valid(self),
                      EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE);

    const eya_memory_range_t *range        = eya_memory_typed_get_range(self);
    const eya_usize_t         size         = eya_memory_range_get_size(range);
    const eya_usize_t         element_size = eya_memory_typed_get_element_size(self);

    return size / element_size;
}

bool
eya_memory_typed_is_empty(const eya_memory_typed_t *self)
{
    return eya_memory_typed_get_size(self) == 0;
}

void
eya_memory_typed_swap(eya_memory_typed_t *self, const eya_memory_typed_t *other)
{
    eya_runtime_check(eya_memory_typed_is_equal_element_size(self, other),
                      EYA_RUNTIME_ERROR_DIFFERENT_ELEMENT_SIZE);

    eya_memory_range_t *self_range  = eya_memory_typed_get_range(self);
    eya_memory_range_t *other_range = eya_memory_typed_get_range(other);

    return eya_memory_range_swap(self_range, other_range);
}

void
eya_memory_typed_exchange(eya_memory_typed_t *self, const eya_memory_typed_t *other)
{
    eya_runtime_check(eya_memory_typed_is_equal_element_size(self, other),
                      EYA_RUNTIME_ERROR_DIFFERENT_ELEMENT_SIZE);

    eya_memory_range_t *self_range  = eya_memory_typed_get_range(self);
    eya_memory_range_t *other_range = eya_memory_typed_get_range(other);

    return eya_memory_range_exchange(self_range, other_range);
}

bool
eya_memory_range_is_valid_index(const eya_memory_typed_t *self, eya_usize_t index)
{
    const eya_usize_t size = eya_memory_typed_get_size(self);
    return index < size;
}

eya_uoffset_t
eya_memory_typed_get_offset_by_index(const eya_memory_typed_t *self, eya_usize_t index)
{
    eya_runtime_check(eya_memory_range_is_valid_index(self, index), EYA_RUNTIME_ERROR_OUT_OF_RANGE);
    const eya_usize_t element_size = eya_memory_typed_get_element_size(self);
    return index * element_size;
}

void *
eya_memory_typed_at_f(const eya_memory_typed_t *self, eya_usize_t index)
{
    const eya_uoffset_t offset = eya_memory_typed_get_offset_by_index(self, index);
    eya_memory_range_t *range  = eya_memory_typed_get_range(self);
    return eya_memory_range_at_f(range, offset);
}

void *
eya_memory_typed_at_b(const eya_memory_typed_t *self, eya_usize_t index)
{
    const eya_usize_t size = eya_memory_typed_get_size(self);
    return eya_memory_typed_at_f(self, size - (index + 1));
}

void *
eya_memory_typed_at(const eya_memory_typed_t *self, eya_usize_t index, bool reversed)
{
    return reversed ? eya_memory_typed_at_b(self, index) : eya_memory_typed_at_f(self, index);
}

void *
eya_memory_typed_front(const eya_memory_typed_t *self)
{
    return eya_memory_typed_at(self, 0, false);
}

void *
eya_memory_typed_back(const eya_memory_typed_t *self)
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
    const eya_memory_range_t *range = eya_memory_typed_get_range(self);
    return eya_memory_typed_is_equal_element_size(self, other) &&
           eya_memory_range_is_equal(range, other);
}