#include <eya/memory_raw.h>

#include <eya/ptr_util.h>
#include <eya/memory.h>

void *
eya_memory_raw_copy(void *dst, const void *dst_end, const void *src, const void *src_end)
{
    eya_uaddr_t dst_size = eya_ptr_udiff(dst_end, dst);
    eya_uaddr_t src_size = eya_ptr_udiff(src_end, src);
    return eya_memory_copy(dst, dst_size, src, src_size);
}

void *
eya_memory_raw_rcopy(void *dst, const void *dst_end, const void *src, const void *src_end)
{
    eya_uaddr_t dst_size = eya_ptr_udiff(dst_end, dst);
    eya_uaddr_t src_size = eya_ptr_udiff(src_end, src);
    return eya_memory_rcopy(dst, dst_size, src, src_size);
}

void *
eya_memory_raw_move(void *dst, const void *dst_end, const void *src, const void *src_end)
{
    eya_uaddr_t dst_size = eya_ptr_udiff(dst_end, dst);
    eya_uaddr_t src_size = eya_ptr_udiff(src_end, src);
    return eya_memory_move(dst, dst_size, src, src_size);
}

void *
eya_memory_raw_set(void *dst, const void *dst_end, const eya_uchar_t value)
{
    const eya_uaddr_t n = eya_ptr_udiff(dst_end, dst);
    return eya_memory_set(dst, n, value);
}

const void *
eya_memory_raw_compare(const void *lhs, const void *lhs_end, const void *rhs, const void *rhs_end)
{
    eya_uaddr_t lhs_size = eya_ptr_udiff(lhs_end, lhs);
    eya_uaddr_t rhs_size = eya_ptr_udiff(rhs_end, rhs);
    return eya_memory_compare(lhs, lhs_size, rhs, rhs_size);
}

const void *
eya_memory_raw_rcompare(const void *lhs, const void *lhs_end, const void *rhs, const void *rhs_end)
{
    eya_uaddr_t lhs_size = eya_ptr_udiff(lhs_end, lhs);
    eya_uaddr_t rhs_size = eya_ptr_udiff(rhs_end, rhs);
    return eya_memory_rcompare(lhs, lhs_size, rhs, rhs_size);
}

const void *
eya_memory_raw_find(const void *lhs, const void *lhs_end, const void *rhs, const void *rhs_end)
{
    eya_uaddr_t lhs_size = eya_ptr_udiff(lhs_end, lhs);
    eya_uaddr_t rhs_size = eya_ptr_udiff(rhs_end, rhs);
    return eya_memory_find(lhs, lhs_size, rhs, rhs_size);
}

const void *
eya_memory_raw_rfind(const void *lhs, const void *lhs_end, const void *rhs, const void *rhs_end)
{
    eya_uaddr_t lhs_size = eya_ptr_udiff(lhs_end, lhs);
    eya_uaddr_t rhs_size = eya_ptr_udiff(rhs_end, rhs);
    return eya_memory_rfind(lhs, lhs_size, rhs, rhs_size);
}