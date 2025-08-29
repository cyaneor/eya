#include <eya/memory_std.h>

#include <eya/runtime_check_ref.h>
#include <eya/algorithm_util.h>
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

    void *end = eya_ptr_add_unsafe(void, dst, n);
    eya_algorithm_copy(eya_uchar_t, dst, src, n);

    return end;
}

void *
eya_memory_std_copy_rev(void *dst, const void *src, eya_usize_t n)
{
    eya_runtime_check_ref(dst);
    eya_runtime_check_ref(src);

    void *end = eya_ptr_add_unsafe(void, dst, n);
    eya_algorithm_copy_rev(eya_uchar_t, dst, src, n);

    return end;
}

void *
eya_memory_std_rcopy(void *dst, const void *src, eya_usize_t n)
{
    eya_runtime_check_ref(dst);
    eya_runtime_check_ref(src);

    eya_algorithm_rcopy(eya_uchar_t, dst, src, n);
    return dst;
}

void *
eya_memory_std_move(void *dst, const void *src, eya_usize_t n)
{
    const void *src_end = eya_ptr_add_by_offset(void, src, n);
    if (eya_ptr_ranges_no_overlap(dst, src, src_end))
    {
        return eya_memory_std_copy(dst, src, n);
    }
    void *d = eya_memory_std_rcopy(dst, src, n);
    return eya_ptr_add_by_offset(void, d, n);
}

void *
eya_memory_std_set(void *dst, eya_uchar_t val, eya_usize_t n)
{
    eya_runtime_check_ref(dst);

    void *end = eya_ptr_add_unsafe(void, dst, n);
    eya_algorithm_set(eya_uchar_t, dst, val, n);
    return end;
}

const void *
eya_memory_std_compare(const void *lhs, const void *rhs, eya_usize_t n)
{
    eya_runtime_check_ref(lhs);
    eya_runtime_check_ref(rhs);

    eya_algorithm_compare(eya_uchar_t, lhs, rhs, n);
    return nullptr;
}

const void *
eya_memory_std_rcompare(const void *lhs, const void *rhs, eya_usize_t n)
{
    eya_runtime_check_ref(lhs);
    eya_runtime_check_ref(rhs);

    eya_algorithm_rcompare(eya_uchar_t, lhs, rhs, n);
    return nullptr;
}