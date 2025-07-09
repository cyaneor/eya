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