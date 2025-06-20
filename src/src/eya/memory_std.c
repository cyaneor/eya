#include <eya/memory_std.h>

#include <eya/runtime_check_ref.h>
#include <eya/ptr_util.h>

/*
 * IMPORTANT COMPILATION NOTES FOR GCC:
 * This library must be compiled with:
 *
 * -flto (Link Time Optimization) enabled
 * -ftree-vectorize enabled for optimal performance
 *
 * These optimizations are crucial
 * for achieving maximum performance in memory operations.
 */

void *
eya_memory_std_copy(void *dst, const void *src, eya_usize_t n)
{
    eya_runtime_check_ref(dst);
    eya_runtime_check_ref(src);

    eya_uchar_t       *d = (eya_uchar_t *)dst;
    const eya_uchar_t *s = (const eya_uchar_t *)src;

    while (n--)
    {
        *d++ = *s++;
    }

    return d;
}

void *
eya_memory_std_rcopy(void *dst, const void *src, eya_usize_t n)
{
    eya_runtime_check_ref(dst);
    eya_runtime_check_ref(src);

    eya_uchar_t       *d = eya_ptr_add_by_offset_unsafe(dst, n);
    const eya_uchar_t *s = eya_ptr_add_by_offset_unsafe(src, n);

    while (n--)
    {
        *(--d) = *(--s);
    }

    return d;
}

void *
eya_memory_std_move(void *dst, const void *src, eya_usize_t n)
{
    const void *src_end = eya_ptr_add_by_offset(src, n);
    if (eya_ptr_ranges_no_overlap(dst, src, src_end))
    {
        return eya_memory_std_copy(dst, src, n);
    }
    void *d = eya_memory_std_rcopy(dst, src, n);
    return eya_ptr_add_by_offset(d, n);
}

void *
eya_memory_std_set(void *dst, eya_uchar_t val, eya_usize_t n)
{
    eya_runtime_check_ref(dst);
    eya_uchar_t *d = eya_ptr_cast(eya_uchar_t, dst);

    while (n--)
    {
        *d++ = val;
    }

    return d;
}

const void *
eya_memory_std_compare(const void *lhs, const void *rhs, eya_usize_t n)
{
    eya_runtime_check_ref(lhs);
    eya_runtime_check_ref(rhs);

    const eya_uchar_t *l = eya_ptr_cast(const eya_uchar_t, lhs);
    const eya_uchar_t *r = eya_ptr_cast(const eya_uchar_t, rhs);

    while (n--)
    {
        if (*l != *r)
        {
            return l;
        }
        l++;
        r++;
    }

    return nullptr;
}

const void *
eya_memory_std_rcompare(const void *lhs, const void *rhs, eya_usize_t n)
{
    eya_runtime_check_ref(lhs);
    eya_runtime_check_ref(rhs);

    const eya_uchar_t *l = eya_ptr_cast(const eya_uchar_t, lhs) + n - 1;
    const eya_uchar_t *r = eya_ptr_cast(const eya_uchar_t, rhs) + n - 1;

    while (n--)
    {
        if (*l != *r)
        {
            return l;
        }
        l--;
        r--;
    }

    return nullptr;
}