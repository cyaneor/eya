#include <eya/memory_range.h>

#include <eya/runtime_check_ref.h>
#include <eya/memory_view.h>
#include <eya/ptr_util.h>
#include <eya/nullptr.h>

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

bool
eya_memory_range_is_uninit(const eya_memory_range_t *self)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    return eya_memory_view_is_uninit(view);
}

bool
eya_memory_range_is_empty(const eya_memory_range_t *self)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    return eya_memory_view_is_empty(view);
}

bool
eya_memory_range_has_data(const eya_memory_range_t *self)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    return eya_memory_view_has_data(view);
}

bool
eya_memory_range_is_invalid(const eya_memory_range_t *self)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    return eya_memory_view_is_invalid(view);
}

bool
eya_memory_range_is_valid(const eya_memory_range_t *self)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    return eya_memory_view_is_valid(view);
}

void
eya_memory_range_unpack_v(const eya_memory_range_t *self, void **begin, void **end)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    eya_runtime_check(eya_memory_view_is_valid(view), EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE);
    eya_memory_range_unpack(self, begin, end);
}

void *
eya_memory_range_at_begin(const eya_memory_range_t *self, eya_uoffset_t offset)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    const void              *ptr  = eya_memory_view_at_begin(view, offset);
    return eya_ptr_cast(void, ptr);
}

void *
eya_memory_range_at_end(const eya_memory_range_t *self, eya_uoffset_t offset)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    const void              *ptr  = eya_memory_view_at_end(view, offset);
    return eya_ptr_cast(void, ptr);
}

void *
eya_memory_range_at(const eya_memory_range_t *self, eya_uoffset_t offset, bool reversed)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    const void              *ptr  = eya_memory_view_at(view, offset, reversed);
    return eya_ptr_cast(void, ptr);
}

void *
eya_memory_range_at_first(const void *self)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    const void              *ptr  = eya_memory_view_at_first(view);
    return eya_ptr_cast(void, ptr);
}

void *
eya_memory_range_at_last(const void *self)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    const void              *ptr  = eya_memory_view_at_last(view);
    return eya_ptr_cast(void, ptr);
}

bool
eya_memory_range_is_equal_begin_to(const eya_memory_range_t *self, const void *ptr)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    return eya_memory_view_is_equal_begin_to(view, ptr);
}

bool
eya_memory_range_is_equal_end_to(const eya_memory_range_t *self, const void *ptr)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    return eya_memory_view_is_equal_end_to(view, ptr);
}

bool
eya_memory_range_is_equal_begin(const eya_memory_range_t *self, const eya_memory_range_t *other)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    return eya_memory_view_is_equal_begin(view, eya_memory_range_get_begin(other));
}

bool
eya_memory_range_is_equal_end(const eya_memory_range_t *self, const eya_memory_range_t *other)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    return eya_memory_view_is_equal_end(view, eya_memory_range_get_end(other));
}

bool
eya_memory_range_is_equal(const eya_memory_range_t *self, const eya_memory_range_t *other)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    return eya_memory_view_is_equal(view, eya_memory_range_get_end(other));
}

const void *
eya_memory_range_find_range(const eya_memory_range_t *self, const void *begin, const void *end)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    return eya_memory_view_find_range(view, begin, end);
}

const void *
eya_memory_range_find(const eya_memory_range_t *self, const eya_memory_range_t *other)
{
    const eya_memory_view_t *self_view  = eya_ptr_cast(eya_memory_view_t, self);
    const eya_memory_view_t *other_view = eya_ptr_cast(eya_memory_view_t, other);
    return eya_memory_view_find(self_view, other_view);
}

const void *
eya_memory_range_rfind_range(const eya_memory_range_t *self, const void *begin, const void *end)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    return eya_memory_view_rfind_range(view, begin, end);
}

const void *
eya_memory_range_rfind(const eya_memory_range_t *self, const eya_memory_range_t *other)
{
    const eya_memory_view_t *self_view  = eya_ptr_cast(eya_memory_view_t, self);
    const eya_memory_view_t *other_view = eya_ptr_cast(eya_memory_view_t, other);
    return eya_memory_view_rfind(self_view, other_view);
}

const void *
eya_memory_range_compare_range(const eya_memory_range_t *self, const void *begin, const void *end)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    return eya_memory_view_compare_range(view, begin, end);
}

const void *
eya_memory_range_compare(const eya_memory_range_t *self, const eya_memory_range_t *other)
{
    const eya_memory_view_t *self_view  = eya_ptr_cast(eya_memory_view_t, self);
    const eya_memory_view_t *other_view = eya_ptr_cast(eya_memory_view_t, other);
    return eya_memory_view_compare(self_view, other_view);
}

const void *
eya_memory_range_rcompare_range(const eya_memory_range_t *self, const void *begin, const void *end)
{
    const eya_memory_view_t *view = eya_ptr_cast(eya_memory_view_t, self);
    return eya_memory_view_rcompare_range(view, begin, end);
}

const void *
eya_memory_range_rcompare(const eya_memory_range_t *self, const eya_memory_range_t *other)
{
    const eya_memory_view_t *self_view  = eya_ptr_cast(eya_memory_view_t, self);
    const eya_memory_view_t *other_view = eya_ptr_cast(eya_memory_view_t, other);
    return eya_memory_view_rcompare(self_view, other_view);
}

eya_memory_range_t
eya_memory_range_make(void *begin, void *end)
{
    eya_memory_range_t self = (eya_memory_range_t){begin, end};
    eya_runtime_check(eya_memory_range_is_valid(&self), EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE);
    return self;
}