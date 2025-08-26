#include <eya/memory.h>

#include <eya/runtime_check_ref.h>
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
eya_memory_copy_rev(void *dst, eya_usize_t dst_size, const void *src, eya_usize_t src_size)
{
    const eya_usize_t n = eya_math_min(dst_size, src_size);
    return eya_memory_std_copy_rev(dst, src, n);
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

void *
eya_memory_set_pattern(void *dst, eya_usize_t dst_size, const void *src, eya_usize_t src_size)
{
    eya_runtime_check_ref(dst);
    eya_runtime_check_ref(src);

    eya_runtime_return_ifn(dst_size, nullptr);
    eya_runtime_return_ifn(src_size, nullptr);

    eya_uchar_t       *d = eya_ptr_cast(eya_uchar_t, dst);
    const eya_uchar_t *s = eya_ptr_cast(const eya_uchar_t, src);

    eya_uchar_t *cur = d;
    for (eya_usize_t i = 0; i < dst_size; i += src_size)
    {
        eya_usize_t remaining = dst_size - i;
        eya_usize_t copy_size = (remaining < src_size) ? remaining : src_size;

        for (eya_usize_t j = 0; j < copy_size; j++)
        {
            d[i + j] = s[j];
        }

        cur = d + i + copy_size;
    }

    return cur;
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
    const eya_usize_t n = eya_math_min(lhs_size, rhs_size);
    const eya_u8_t   *l = eya_ptr_add(lhs, lhs_size - n);
    const eya_u8_t   *r = eya_ptr_add(rhs, rhs_size - n);

    return eya_memory_std_rcompare(l, r, n);
}

const void *
eya_memory_find(const void *lhs, eya_usize_t lhs_size, const void *rhs, eya_usize_t rhs_size)
{
    eya_runtime_check_ref(lhs);
    eya_runtime_check_ref(rhs);

    eya_runtime_return_ifn(lhs_size, nullptr);
    eya_runtime_return_ifn(rhs_size, nullptr);

    const eya_u8_t *l = eya_ptr_cast(const eya_u8_t, lhs);
    const eya_u8_t *e = eya_ptr_add_by_offset_unsafe(l, lhs_size);

    for (; l < e; ++l)
    {
        if (!eya_memory_compare(l, e - l, rhs, rhs_size))
        {
            return l;
        }
    }
    return nullptr;
}

const void *
eya_memory_rfind(const void *lhs, eya_usize_t lhs_size, const void *rhs, eya_usize_t rhs_size)
{
    eya_runtime_check_ref(lhs);
    eya_runtime_check_ref(rhs);

    eya_runtime_return_ifn(lhs_size, nullptr);
    eya_runtime_return_ifn(rhs_size, nullptr);

    const eya_u8_t *l = eya_ptr_cast(const eya_u8_t, lhs);
    const eya_u8_t *e = eya_ptr_add_by_offset_unsafe(l, lhs_size);

    for (; e > l; --e)
    {
        if (!eya_memory_rcompare(l, e - l, rhs, rhs_size))
        {
            return eya_ptr_sub_by_offset_unsafe(e, rhs_size);
        }
    }
    return nullptr;
}