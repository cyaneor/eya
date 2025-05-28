#include <eya/memory.h>

#include <eya/runtime_return_if.h>
#include <eya/memory_std.h>
#include <eya/math_util.h>
#include <eya/ptr_util.h>

void *
eya_memory_copy(void *dst, eya_usize_t dst_size, const void *src, eya_usize_t src_size)
{
    const eya_usize_t n = eya_math_min(dst_size, src_size);
    return eya_memory_std_copy(dst, src, n);
}

void *
eya_memory_rcopy(void *dst, eya_usize_t dst_size, const void *src, eya_usize_t src_size)
{
    const eya_usize_t n = eya_math_min(dst_size, src_size);
    return eya_memory_std_rcopy(dst, src, n);
}

void *
eya_memory_move(void *dst, eya_usize_t dst_size, const void *src, eya_usize_t src_size)
{
    const eya_usize_t n = eya_math_min(dst_size, src_size);
    return eya_memory_std_move(dst, src, n);
}

void *
eya_memory_set(void *dst, eya_usize_t size, eya_uchar_t val)
{
    return eya_memory_std_set(dst, val, size);
}

const void *
eya_memory_compare(const void *lhs, eya_usize_t lhs_size, const void *rhs, eya_usize_t rhs_size)
{
    const eya_usize_t n = eya_math_min(lhs_size, rhs_size);
    return eya_memory_std_compare(lhs, rhs, n);
}

const void *
eya_memory_rcompare(const void *lhs, eya_usize_t lhs_size, const void *rhs, eya_usize_t rhs_size)
{
    eya_runtime_return_if(lhs_size, nullptr);
    eya_runtime_return_if(rhs_size, nullptr);

    const eya_usize_t n = eya_math_min(lhs_size, rhs_size);
    const eya_u8_t   *l = eya_ptr_add(const void, lhs, lhs_size - n);
    const eya_u8_t   *r = eya_ptr_add(const void, rhs, rhs_size - n);

    return eya_memory_std_rcompare(l, r, n);
}