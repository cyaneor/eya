#include <eya/memory_typed.h>

#include <eya/memory_typed_initializer.h>
#include <eya/runtime_check_ref.h>
#include <eya/ptr_util.h>

void
eya_memory_typed_unpack_full(const eya_memory_typed_t *self,
                             void                    **begin,
                             void                    **end,
                             eya_usize_t              *element_size)
{
    eya_memory_range_unpack(eya_ptr_ccast(eya_memory_range_t, self), begin, end);

    if (element_size)
    {
        *element_size = self->element_size;
    }
}

void
eya_memory_typed_unpack(const eya_memory_typed_t *self,
                        eya_memory_range_t       *range,
                        eya_usize_t              *element_size)
{
    if (range)
    {
        eya_memory_range_t *r = eya_ptr_cast(eya_memory_range_t, range);
        eya_memory_typed_unpack_full(self, &r->begin, &r->end, element_size);
    }
    else
    {
        eya_memory_typed_unpack_full(self, nullptr, nullptr, element_size);
    }
}

eya_usize_t
eya_memory_typed_get_element_size(const eya_memory_typed_t *self)
{
    eya_usize_t element_size;
    eya_memory_typed_unpack(self, nullptr, &element_size);
    return element_size;
}

bool
eya_memory_typed_is_valid(const eya_memory_typed_t *self)
{
    const eya_usize_t element_size = eya_memory_typed_get_element_size(self);
    return eya_memory_range_is_multiple_of_size(eya_ptr_ccast(eya_memory_range_t, self),
                                                element_size);
}

eya_usize_t
eya_memory_typed_get_size(const eya_memory_typed_t *self)
{
    eya_runtime_check(eya_memory_typed_is_valid(self),
                      EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE);

    const eya_usize_t size = eya_memory_range_get_size(eya_ptr_ccast(eya_memory_range_t, self));
    const eya_usize_t element_size = eya_memory_typed_get_element_size(self);

    return size / element_size;
}

bool
eya_memory_typed_is_empty(const eya_memory_typed_t *self)
{
    return eya_memory_typed_get_size(self) == 0;
}

void
eya_memory_typed_swap(eya_memory_typed_t *self, eya_memory_typed_t *other)
{
    eya_runtime_check(eya_memory_typed_is_equal_element_size(self, other),
                      EYA_RUNTIME_ERROR_DIFFERENT_ELEMENT_SIZE);

    eya_memory_range_swap(eya_ptr_cast(eya_memory_range_t, self),
                          eya_ptr_cast(eya_memory_range_t, other));
}

void
eya_memory_typed_exchange(eya_memory_typed_t *self, eya_memory_typed_t *other)
{
    eya_runtime_check(eya_memory_typed_is_equal_element_size(self, other),
                      EYA_RUNTIME_ERROR_DIFFERENT_ELEMENT_SIZE);

    eya_memory_range_exchange(eya_ptr_cast(eya_memory_range_t, self),
                              eya_ptr_cast(eya_memory_range_t, other));
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
eya_memory_typed_at_from_front(const eya_memory_typed_t *self, eya_usize_t index)
{
    const eya_uoffset_t offset = eya_memory_typed_get_offset_by_index(self, index);
    return eya_memory_range_at_from_front(eya_ptr_ccast(eya_memory_range_t, self), offset);
}

void *
eya_memory_typed_at_from_back(const eya_memory_typed_t *self, eya_usize_t index)
{
    const eya_usize_t size = eya_memory_typed_get_size(self);
    return eya_memory_typed_at_from_front(self, size - (index + 1));
}

void *
eya_memory_typed_at(const eya_memory_typed_t *self, eya_usize_t index, bool reversed)
{
    return reversed ? eya_memory_typed_at_from_back(self, index)
                    : eya_memory_typed_at_from_front(self, index);
}

void *
eya_memory_typed_front(eya_memory_typed_t *self)
{
    return eya_memory_typed_at(self, 0, false);
}

void *
eya_memory_typed_back(eya_memory_typed_t *self)
{
    return eya_memory_typed_at(self, 0, true);
}

bool
eya_memory_typed_is_equal_element_size_to(const eya_memory_typed_t *self, eya_usize_t element_size)
{
    return eya_memory_typed_get_element_size(self) == element_size;
}

bool
eya_memory_typed_is_equal_element_size(const eya_memory_typed_t *self,
                                       const eya_memory_typed_t *other)
{
    const eya_usize_t element_size = eya_memory_typed_get_element_size(other);
    return eya_memory_typed_is_equal_element_size_to(self, element_size);
}

bool
eya_memory_typed_is_equal(const eya_memory_typed_t *self, const eya_memory_typed_t *other)
{
    return eya_memory_typed_is_equal_element_size(self, other) &&
           eya_memory_range_is_equal(eya_ptr_ccast(eya_memory_range_t, self),
                                     eya_ptr_ccast(eya_memory_range_t, other));
}

eya_memory_typed_t
eya_memory_typed_make(void *begin, void *end, eya_usize_t element_size)
{
    eya_memory_typed_t self = eya_memory_typed_empty_initializer(element_size);
    eya_memory_range_reset(eya_ptr_cast(eya_memory_range_t, &self), begin, end);
    return self;
}