#include <eya/memory_range.h>

#include <eya/memory_range_initializer.h>
#include <eya/runtime_check_ref.h>
#include <eya/algorithm_util.h>
#include <eya/interval_util.h>
#include <eya/runtime_try.h>
#include <eya/memory_raw.h>
#include <eya/ptr_util.h>

void
eya_memory_range_unpack(const eya_memory_range_t *self, void **begin, void **end)
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

void *
eya_memory_range_get_begin(const eya_memory_range_t *self)
{
    void *begin;
    eya_memory_range_unpack(self, &begin, nullptr);
    return begin;
}

void *
eya_memory_range_get_end(const eya_memory_range_t *self)
{
    void *end;
    eya_memory_range_unpack(self, nullptr, &end);
    return end;
}

eya_memory_range_state_t
eya_memory_range_get_state(const eya_memory_range_t *self)
{
    void *begin, *end;
    eya_memory_range_unpack(self, &begin, &end);

    if (begin == end)
    {
        return (begin == nullptr) ? EYA_MEMORY_RANGE_UNINITIALIZED : EYA_MEMORY_RANGE_EMPTY;
    }

    if (begin == nullptr)
    {
        return EYA_MEMORY_RANGE_INVALID_NULL_BEGIN;
    }

    if (end == nullptr)
    {
        return EYA_MEMORY_RANGE_INVALID_NULL_END;
    }

    return (begin < end) ? EYA_MEMORY_RANGE_HAS_DATA : EYA_MEMORY_RANGE_INVALID_DANGLING;
}

bool
eya_memory_range_is_uninit(const eya_memory_range_t *self)
{
    const eya_memory_range_state_t state = eya_memory_range_get_state(self);
    return state == EYA_MEMORY_RANGE_UNINITIALIZED;
}

bool
eya_memory_range_is_empty(const eya_memory_range_t *self)
{
    const eya_memory_range_state_t state = eya_memory_range_get_state(self);
    return state == EYA_MEMORY_RANGE_EMPTY;
}

bool
eya_memory_range_has_data(const eya_memory_range_t *self)
{
    const eya_memory_range_state_t state = eya_memory_range_get_state(self);
    return state == EYA_MEMORY_RANGE_HAS_DATA;
}

bool
eya_memory_range_is_invalid(const eya_memory_range_t *self)
{
    const eya_memory_range_state_t state = eya_memory_range_get_state(self);
    return (state == EYA_MEMORY_RANGE_UNINITIALIZED) ||
           (state == EYA_MEMORY_RANGE_INVALID_NULL_BEGIN) ||
           (state == EYA_MEMORY_RANGE_INVALID_NULL_END) ||
           (state == EYA_MEMORY_RANGE_INVALID_DANGLING);
}

bool
eya_memory_range_is_valid(const eya_memory_range_t *self)
{
    return !eya_memory_range_is_invalid(self);
}

void
eya_memory_range_unpack_v(const eya_memory_range_t *self, void **begin, void **end)
{
    eya_runtime_check(eya_memory_range_is_valid(self), EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE);
    eya_memory_range_unpack(self, begin, end);
}

eya_uaddr_t
eya_memory_range_diff(const eya_memory_range_t *self)
{
    void *begin, *end;
    eya_memory_range_unpack_v(self, &begin, &end);
    return eya_ptr_udiff(end, begin);
}

eya_usize_t
eya_memory_range_get_size(const eya_memory_range_t *self)
{
    return eya_type_cast(eya_usize_t, eya_memory_range_diff(self));
}

bool
eya_memory_range_is_aligned(const eya_memory_range_t *self, eya_usize_t align)
{
    eya_runtime_check(eya_math_is_power_of_two(align), EYA_RUNTIME_ERROR_NOT_POWER_OF_TWO);

    void *begin;
    eya_memory_range_unpack_v(self, &begin, nullptr);
    return eya_ptr_is_aligned(begin, align);
}

bool
eya_memory_range_is_multiple_of_size(const eya_memory_range_t *self, eya_usize_t element_size)
{
    eya_runtime_check(element_size, EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE);
    const eya_usize_t size = eya_memory_range_get_size(self);
    return eya_math_has_no_remainder(size, element_size);
}

bool
eya_memory_range_contains_ptr(const eya_memory_range_t *self, const void *ptr)
{
    void *begin, *end;
    eya_memory_range_unpack_v(self, &begin, &end);
    return eya_interval_ropen_contains_value(begin, end, ptr);
}

bool
eya_memory_range_contains_range(const eya_memory_range_t *self, const void *begin, const void *end)
{
    void *self_begin, *self_end;
    eya_memory_range_unpack_v(self, &self_begin, &self_end);
    return eya_interval_ropen_contains_range(self_begin, self_end, begin, end);
}

bool
eya_memory_range_contains(const eya_memory_range_t *self, const eya_memory_range_t *other)
{
    void *other_begin, *other_end;
    eya_memory_range_unpack_v(other, &other_begin, &other_end);
    return eya_memory_range_contains_range(self, other_begin, other_end);
}

bool
eya_memory_range_is_valid_offset(const eya_memory_range_t *self, eya_uoffset_t offset)
{
    eya_usize_t size = eya_memory_range_get_size(self);
    return offset < size;
}

void *
eya_memory_range_at_from_front(const eya_memory_range_t *self, eya_uoffset_t offset)
{
    eya_runtime_check(eya_memory_range_is_valid_offset(self, offset),
                      EYA_RUNTIME_ERROR_OUT_OF_RANGE);

    const void *begin = eya_memory_range_get_begin(self);
    return eya_ptr_add_by_offset_unsafe(void, begin, offset);
}

void *
eya_memory_range_at_from_back(const eya_memory_range_t *self, eya_uoffset_t offset)
{
    const eya_usize_t size = eya_memory_range_get_size(self);
    return eya_memory_range_at_from_front(self, size - (offset + 1));
}

void *
eya_memory_range_at(const eya_memory_range_t *self, eya_uoffset_t offset, bool reversed)
{
    return reversed ? eya_memory_range_at_from_back(self, offset)
                    : eya_memory_range_at_from_front(self, offset);
}

void *
eya_memory_range_front(const eya_memory_range_t *self)
{
    return eya_memory_range_at(self, 0, false);
}

void *
eya_memory_range_back(const eya_memory_range_t *self)
{
    return eya_memory_range_at(self, 0, true);
}

bool
eya_memory_range_is_equal_begin_to(const eya_memory_range_t *self, const void *ptr)
{
    return eya_memory_range_get_begin(self) == ptr;
}

bool
eya_memory_range_is_equal_end_to(const eya_memory_range_t *self, const void *ptr)
{
    return eya_memory_range_get_end(self) == ptr;
}

bool
eya_memory_range_is_equal_begin(const eya_memory_range_t *self, const eya_memory_range_t *other)
{
    return eya_memory_range_is_equal_begin_to(self, eya_memory_range_get_begin(other));
}

bool
eya_memory_range_is_equal_end(const eya_memory_range_t *self, const eya_memory_range_t *other)
{
    return eya_memory_range_is_equal_end_to(self, eya_memory_range_get_end(other));
}

bool
eya_memory_range_is_equal(const eya_memory_range_t *self, const eya_memory_range_t *other)
{
    return self == other || (eya_memory_range_is_equal_begin(self, other) &&
                             eya_memory_range_is_equal_end(self, other));
}

void
eya_memory_range_assign(eya_memory_range_t *self, const eya_memory_range_t *other)
{
    eya_runtime_check_ref(self);
    eya_memory_range_t *s = eya_ptr_cast(eya_memory_range_t, self);
    eya_memory_range_unpack(other, &s->begin, &s->end);
}

void
eya_memory_range_clear(eya_memory_range_t *self)
{
    eya_memory_range_t other = eya_memory_range_empty_initializer();
    eya_memory_range_assign(self, &other);
}

void
eya_memory_range_assign_v(eya_memory_range_t *self, const eya_memory_range_t *other)
{
    eya_runtime_check(eya_memory_range_is_valid(other), EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE);
    eya_memory_range_assign(self, other);
}

void
eya_memory_range_pack(eya_memory_range_t *self, void *begin, void *end)
{
    const eya_memory_range_t range = eya_memory_range_initializer(begin, end);
    eya_memory_range_assign(self, &range);
}

void
eya_memory_range_pack_v(eya_memory_range_t *self, void *begin, void *end)
{
    const eya_memory_range_t range = eya_memory_range_initializer(begin, end);
    eya_memory_range_assign_v(self, &range);
}

void
eya_memory_range_reset(eya_memory_range_t *self, void *begin, void *end)
{
    eya_memory_range_pack(self, begin, end);
}

void
eya_memory_range_reset_v(eya_memory_range_t *self, void *begin, void *end)
{
    eya_memory_range_pack_v(self, begin, end);
}

void
eya_memory_range_reset_s(eya_memory_range_t *self, void *begin, eya_usize_t size)
{
    eya_runtime_check(begin, EYA_RUNTIME_ERROR_INVALID_ARGUMENT);
    eya_memory_range_reset(self, begin, eya_ptr_add_by_offset_unsafe(void, begin, size));
}

void
eya_memory_range_reset_f(eya_memory_range_t *self, void *begin, eya_usize_t size)
{
    eya_runtime_try(e)
    {
        eya_memory_range_reset_s(self, begin, size);
        eya_runtime_try_return();
    }
    eya_runtime_catch
    {
        eya_memory_range_clear(self);
    }
}

void
eya_memory_range_swap(eya_memory_range_t *self, eya_memory_range_t *other)
{
    eya_runtime_check_ref(self);
    eya_runtime_check_ref(other);

    eya_memory_range_t *s = eya_ptr_cast(eya_memory_range_t, self);
    eya_memory_range_t *o = eya_ptr_cast(eya_memory_range_t, other);
    eya_algorithm_swap(eya_memory_range_t, *s, *o);
}

void
eya_memory_range_exchange(eya_memory_range_t *self, eya_memory_range_t *other)
{
    eya_memory_range_clear(self);
    eya_memory_range_swap(self, other);
}

eya_memory_range_t
eya_memory_range_make(void *begin, void *end)
{
    eya_memory_range_t self = eya_memory_range_empty_initializer();
    eya_memory_range_reset(&self, begin, end);
    return self;
}

eya_memory_range_t
eya_memory_range_slice(const eya_memory_range_t *self, eya_uoffset_t offset, eya_usize_t size)
{
    void *begin = eya_memory_range_at(self, offset, false);
    void *end   = eya_memory_range_at(self, offset + size, false);
    return eya_memory_range_make(begin, end);
}

void *
eya_memory_range_set(eya_memory_range_t *self, eya_uchar_t value)
{
    void *begin, *end;
    eya_memory_range_unpack_v(self, &begin, &end);
    return eya_memory_raw_set(begin, end, value);
}

void
eya_memory_range_set_value(eya_memory_range_t *self,
                           eya_uoffset_t       offset,
                           bool                reversed,
                           eya_uchar_t         value)
{
    eya_ptr_deref(eya_uchar_t, eya_memory_range_at(self, offset, reversed)) = value;
}

void *
eya_memory_range_copy_range(eya_memory_range_t *self, const void *begin, const void *end)
{
    void *self_begin, *self_end;
    eya_memory_range_unpack_v(self, &self_begin, &self_end);
    return eya_memory_raw_copy(self_begin, self_end, begin, end);
}

void *
eya_memory_range_copy(eya_memory_range_t *self, const eya_memory_range_t *other)
{
    void *other_begin, *other_end;
    eya_memory_range_unpack_v(other, &other_begin, &other_end);
    return eya_memory_range_copy_range(self, other_begin, other_end);
}

void *
eya_memory_range_set_pattern_range(eya_memory_range_t *self, const void *begin, const void *end)
{
    void *self_begin, *self_end;
    eya_memory_range_unpack_v(self, &self_begin, &self_end);
    return eya_memory_raw_set_pattern(self_begin, self_end, begin, end);
}

void *
eya_memory_range_set_pattern(eya_memory_range_t *self, const eya_memory_range_t *other)
{
    void *other_begin, *other_end;
    eya_memory_range_unpack_v(other, &other_begin, &other_end);
    return eya_memory_range_set_pattern_range(self, other_begin, other_end);
}

void *
eya_memory_range_copy_rev_range(eya_memory_range_t *self, const void *begin, const void *end)
{
    void *self_begin, *self_end;
    eya_memory_range_unpack_v(self, &self_begin, &self_end);
    return eya_memory_raw_copy_rev(self_begin, self_end, begin, end);
}

void *
eya_memory_range_copy_rev(eya_memory_range_t *self, const eya_memory_range_t *other)
{
    void *other_begin, *other_end;
    eya_memory_range_unpack_v(other, &other_begin, &other_end);
    return eya_memory_range_copy_rev_range(self, other_begin, other_end);
}

void *
eya_memory_range_rcopy_range(eya_memory_range_t *self, const void *begin, const void *end)
{
    void *self_begin, *self_end;
    eya_memory_range_unpack_v(self, &self_begin, &self_end);
    return eya_memory_raw_rcopy(self_begin, self_end, begin, end);
}

void *
eya_memory_range_rcopy(eya_memory_range_t *self, const eya_memory_range_t *other)
{
    void *other_begin, *other_end;
    eya_memory_range_unpack_v(other, &other_begin, &other_end);
    return eya_memory_range_rcopy_range(self, other_begin, other_end);
}

void *
eya_memory_range_move_range(eya_memory_range_t *self, const void *begin, const void *end)
{
    void *self_begin, *self_end;
    eya_memory_range_unpack_v(self, &self_begin, &self_end);
    return eya_memory_raw_move(self_begin, self_end, begin, end);
}

void *
eya_memory_range_move(eya_memory_range_t *self, const eya_memory_range_t *other)
{
    void *other_begin, *other_end;
    eya_memory_range_unpack_v(other, &other_begin, &other_end);
    return eya_memory_range_move_range(self, other_begin, other_end);
}

const void *
eya_memory_range_find_range(const eya_memory_range_t *self, const void *begin, const void *end)
{
    void *self_begin, *self_end;
    eya_memory_range_unpack_v(self, &self_begin, &self_end);
    return eya_memory_raw_find(self_begin, self_end, begin, end);
}

const void *
eya_memory_range_find(const eya_memory_range_t *self, const eya_memory_range_t *other)
{
    void *other_begin, *other_end;
    eya_memory_range_unpack_v(other, &other_begin, &other_end);
    return eya_memory_range_find_range(self, other_begin, other_end);
}

const void *
eya_memory_range_rfind_range(const eya_memory_range_t *self, const void *begin, const void *end)
{
    void *self_begin, *self_end;
    eya_memory_range_unpack_v(self, &self_begin, &self_end);
    return eya_memory_raw_rfind(self_begin, self_end, begin, end);
}

const void *
eya_memory_range_rfind(const eya_memory_range_t *self, const eya_memory_range_t *other)
{
    void *other_begin, *other_end;
    eya_memory_range_unpack_v(other, &other_begin, &other_end);
    return eya_memory_range_rfind_range(self, other_begin, other_end);
}

const void *
eya_memory_range_compare_range(const eya_memory_range_t *self, const void *begin, const void *end)
{
    void *self_begin, *self_end;
    eya_memory_range_unpack_v(self, &self_begin, &self_end);
    return eya_memory_raw_compare(self_begin, self_end, begin, end);
}

const void *
eya_memory_range_compare(const eya_memory_range_t *self, const eya_memory_range_t *other)
{
    void *other_begin, *other_end;
    eya_memory_range_unpack_v(other, &other_begin, &other_end);
    return eya_memory_range_compare_range(self, other_begin, other_end);
}

const void *
eya_memory_range_rcompare_range(const eya_memory_range_t *self, const void *begin, const void *end)
{
    void *self_begin, *self_end;
    eya_memory_range_unpack_v(self, &self_begin, &self_end);
    return eya_memory_raw_rcompare(self_begin, self_end, begin, end);
}

const void *
eya_memory_range_rcompare(const eya_memory_range_t *self, const eya_memory_range_t *other)
{
    void *other_begin, *other_end;
    eya_memory_range_unpack_v(other, &other_begin, &other_end);
    return eya_memory_range_rcompare_range(self, other_begin, other_end);
}