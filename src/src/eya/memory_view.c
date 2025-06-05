#include <eya/memory_view.h>

#include <eya/runtime_check_ref.h>
#include <eya/interval_util.h>
#include <eya/ptr_util.h>
#include <eya/nullptr.h>

void
eya_memory_view_unpack(const eya_memory_view_t *self, const void **begin, const void **end)
{
    eya_runtime_check_ref(self);

    if (begin)
    {
        *begin = self->begin;
    }

    if (end)
    {
        *end = self->end;
    }
}

const void *
eya_memory_view_get_begin(const eya_memory_view_t *self)
{
    const void *begin;
    eya_memory_view_unpack(self, &begin, nullptr);
    return begin;
}

const void *
eya_memory_view_get_end(const eya_memory_view_t *self)
{
    const void *end;
    eya_memory_view_unpack(self, nullptr, &end);
    return end;
}

eya_memory_view_state_t
eya_memory_view_get_state(const eya_memory_view_t *self)
{
    const void *begin, *end;
    eya_memory_view_unpack(self, &begin, &end);

    if (begin == end)
    {
        return (begin == nullptr) ? EYA_MEMORY_VIEW_UNINITIALIZED : EYA_MEMORY_VIEW_EMPTY;
    }

    if (begin == nullptr)
    {
        return EYA_MEMORY_VIEW_INVALID_NULL_BEGIN;
    }

    if (end == nullptr)
    {
        return EYA_MEMORY_VIEW_INVALID_NULL_END;
    }

    return (begin < end) ? EYA_MEMORY_VIEW_HAS_DATA : EYA_MEMORY_VIEW_INVALID_DANGLING;
}

bool
eya_memory_view_is_uninitialized(const eya_memory_view_t *self)
{
    const eya_memory_view_state_t state = eya_memory_view_get_state(self);
    return state == EYA_MEMORY_VIEW_UNINITIALIZED;
}

bool
eya_memory_view_is_empty(const eya_memory_view_t *self)
{
    const eya_memory_view_state_t state = eya_memory_view_get_state(self);
    return state == EYA_MEMORY_VIEW_EMPTY;
}

bool
eya_memory_view_has_data(const eya_memory_view_t *self)
{
    const eya_memory_view_state_t state = eya_memory_view_get_state(self);
    return state == EYA_MEMORY_VIEW_HAS_DATA;
}

bool
eya_memory_view_is_invalid(const eya_memory_view_t *self)
{
    const eya_memory_view_state_t state = eya_memory_view_get_state(self);
    return (state == EYA_MEMORY_VIEW_UNINITIALIZED) ||
           (state == EYA_MEMORY_VIEW_INVALID_NULL_BEGIN) ||
           (state == EYA_MEMORY_VIEW_INVALID_NULL_END) ||
           (state == EYA_MEMORY_VIEW_INVALID_DANGLING);
}

bool
eya_memory_view_is_valid(const eya_memory_view_t *self)
{
    return !eya_memory_view_is_invalid(self);
}

void
eya_memory_view_unpack_v(const eya_memory_view_t *self, const void **begin, const void **end)
{
    eya_runtime_check(eya_memory_view_is_valid(self), EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE);
    eya_memory_view_unpack(self, begin, end);
}

eya_uaddr_t
eya_memory_view_udiff(const eya_memory_view_t *self)
{
    const void *begin, *end;
    eya_memory_view_unpack_v(self, &begin, &end);
    return eya_ptr_udiff(end, begin);
}

eya_usize_t
eya_memory_view_get_size(const eya_memory_view_t *self)
{
    return eya_type_cast(eya_usize_t, eya_memory_view_udiff(self));
}

bool
eya_memory_view_is_aligned(const eya_memory_view_t *self, eya_usize_t align)
{
    eya_runtime_check(eya_math_is_power_of_two(align), EYA_RUNTIME_ERROR_NOT_POWER_OF_TWO);

    const void *begin;
    eya_memory_view_unpack_v(self, &begin, nullptr);
    return eya_ptr_is_aligned(begin, align);
}

bool
eya_memory_view_contains_ptr(const eya_memory_view_t *self, const void *ptr)
{
    const void *begin, *end;
    eya_memory_view_unpack_v(self, &begin, &end);
    return eya_interval_ropen_contains_value(begin, end, ptr);
}

bool
eya_memory_view_contains_other(const eya_memory_view_t *self, const eya_memory_view_t *other)
{
    const void *self_begin, *self_end;
    eya_memory_view_unpack_v(self, &self_begin, &self_end);

    const void *other_begin, *other_end;
    eya_memory_view_unpack_v(other, &other_begin, &other_end);

    return eya_interval_ropen_contains_range(self_begin, self_end, other_begin, other_end);
}

bool
eya_memory_view_is_valid_offset(const eya_memory_view_t *self, eya_uoffset_t offset)
{
    return offset < eya_memory_view_get_size(self);
}

const void *
eya_memory_view_at_begin(const eya_memory_view_t *self, eya_uoffset_t offset)
{
    eya_runtime_check(eya_memory_view_is_valid_offset(self, offset),
                      EYA_RUNTIME_ERROR_OUT_OF_RANGE);

    const void *begin = eya_memory_view_get_begin(self);
    return eya_ptr_add_offset_unsafe(const void, begin, offset);
}

const void *
eya_memory_view_at_end(const eya_memory_view_t *self, eya_uoffset_t offset)
{
    const eya_usize_t size = eya_memory_view_get_size(self);
    return eya_memory_view_at_begin(self, size - (offset + 1));
}

const void *
eya_memory_view_at(const eya_memory_view_t *self, eya_uoffset_t offset, bool reversed)
{
    return reversed ? eya_memory_view_at_end(self, offset) : eya_memory_view_at_begin(self, offset);
}

const void *
eya_memory_view_at_first(const void *self)
{
    return eya_memory_view_at(self, 0, false);
}

const void *
eya_memory_view_at_last(const void *self)
{
    return eya_memory_view_at(self, 0, true);
}

bool
eya_memory_view_is_begin_equal(const eya_memory_view_t *self, const void *ptr)
{
    return eya_memory_view_get_begin(self) == ptr;
}

bool
eya_memory_view_is_end_equal(const eya_memory_view_t *self, const void *ptr)
{
    return eya_memory_view_get_end(self) == ptr;
}

bool
eya_memory_view_is_begin_equal_to(const eya_memory_view_t *self, const eya_memory_view_t *other)
{
    return eya_memory_view_is_begin_equal(self, eya_memory_view_get_begin(other));
}

bool
eya_memory_view_is_end_equal_to(const eya_memory_view_t *self, const eya_memory_view_t *other)
{
    return eya_memory_view_is_end_equal(self, eya_memory_view_get_end(other));
}

bool
eya_memory_view_is_equal(const eya_memory_view_t *self, const eya_memory_view_t *other)
{
    return eya_memory_view_is_begin_equal_to(self, other) &&
           eya_memory_view_is_end_equal_to(self, other);
}