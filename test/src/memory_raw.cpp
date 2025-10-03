#include <gtest/gtest.h>

#include <eya/memory_raw.h>
#include <eya/size.h>
#include <eya/static_array_size.h>

TEST(eya_memory_raw_compare, null_pointers)
{
    EXPECT_DEATH(eya_memory_raw_compare(nullptr, nullptr, nullptr, nullptr), ".*");
}

TEST(eya_memory_raw_compare, compare32)
{
    unsigned char lhs[32] = {};
    unsigned char rhs[32] = {};

    const void *result = eya_memory_raw_compare(lhs, lhs + 32, rhs, rhs + 32);
    EXPECT_EQ(result, nullptr);

    rhs[15] = 1;

    result = eya_memory_raw_compare(lhs, lhs + 32, rhs, rhs + 32);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result, lhs + 15);
}

TEST(eya_memory_raw_compare, compare16)
{
    unsigned char lhs[16] = {};
    unsigned char rhs[16] = {};

    const void *result = eya_memory_raw_compare(lhs, lhs + 16, rhs, rhs + 16);
    EXPECT_EQ(result, nullptr);

    rhs[7] = 1;

    result = eya_memory_raw_compare(lhs, lhs + 16, rhs, rhs + 16);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result, lhs + 7);
}

TEST(eya_memory_raw_compare, compare_same_length)
{
    constexpr eya_uchar_t lhs[] = {1, 2, 3, 4, 5};
    constexpr eya_uchar_t rhs[] = {1, 2, 3, 4, 5};
    constexpr eya_usize_t len   = eya_static_array_size(lhs);
    EXPECT_EQ(eya_memory_raw_compare(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(eya_memory_raw_compare, compare_different_length)
{
    constexpr eya_uchar_t lhs[]   = {1, 2, 3, 4, 5};
    constexpr eya_uchar_t rhs[]   = {1, 2, 3};
    constexpr eya_usize_t lhs_len = eya_static_array_size(lhs);
    constexpr eya_usize_t rhs_len = eya_static_array_size(rhs);

    EXPECT_EQ(eya_memory_raw_compare(lhs, &lhs[lhs_len], rhs, &rhs[rhs_len]), nullptr);
}

TEST(eya_memory_raw_compare, compare_different_values)
{
    constexpr eya_uchar_t lhs[] = {1, 2, 3, 4, 5};
    constexpr eya_uchar_t rhs[] = {1, 2, 0, 4, 5};
    constexpr eya_usize_t len   = eya_static_array_size(lhs);

    EXPECT_EQ(eya_memory_raw_compare(lhs, &lhs[len], rhs, &rhs[len]), &lhs[2]);
}

TEST(eya_memory_raw_compare, empty_array)
{
    constexpr eya_uchar_t rhs[]   = {1, 2, 3};
    constexpr eya_usize_t rhs_len = eya_static_array_size(rhs);
    EXPECT_DEATH(eya_memory_raw_compare(nullptr, nullptr, rhs, &rhs[rhs_len]), ".*");
}

TEST(eya_memory_raw_compare, compare_equal_after_different_elements)
{
    constexpr eya_uchar_t lhs[] = {1, 2, 3, 4, 5};
    constexpr eya_uchar_t rhs[] = {6, 7, 8, 4, 5};
    constexpr eya_usize_t len   = eya_static_array_size(lhs);

    EXPECT_EQ(eya_memory_raw_compare(lhs, &lhs[len], rhs, &rhs[len]), &lhs[0]);
}

TEST(eya_memory_raw_rcompare, null_pointers)
{
    EXPECT_DEATH(eya_memory_raw_rcompare(nullptr, nullptr, nullptr, nullptr), ".*");
}

TEST(eya_memory_raw_rcompare, compare_same_length)
{
    constexpr eya_uchar_t lhs[] = {1, 2, 3, 4, 5};
    constexpr eya_uchar_t rhs[] = {1, 2, 3, 4, 5};
    constexpr eya_usize_t len   = eya_static_array_size(lhs);

    EXPECT_EQ(eya_memory_raw_rcompare(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(eya_memory_raw_rcompare, compare_different_length)
{
    constexpr eya_uchar_t lhs[]   = {1, 2, 3, 4, 5};
    constexpr eya_uchar_t rhs[]   = {1, 2, 3};
    constexpr eya_usize_t lhs_len = eya_static_array_size(lhs);
    constexpr eya_usize_t rhs_len = eya_static_array_size(rhs);

    EXPECT_EQ(eya_memory_raw_rcompare(lhs, &lhs[lhs_len], rhs, &rhs[rhs_len]), &lhs[4]);
}

TEST(eya_memory_raw_rcompare, compare_different_values)
{
    constexpr eya_uchar_t lhs[] = {1, 2, 3, 4, 5};
    constexpr eya_uchar_t rhs[] = {1, 2, 3, 0, 5};
    constexpr eya_usize_t len   = eya_static_array_size(lhs);

    EXPECT_EQ(eya_memory_raw_rcompare(lhs, &lhs[len], rhs, &rhs[len]), &lhs[3]);
}

TEST(eya_memory_raw_rcompare, empty_array)
{
    constexpr eya_uchar_t rhs[]   = {1, 2, 3};
    constexpr eya_usize_t rhs_len = eya_static_array_size(rhs);

    EXPECT_DEATH(eya_memory_raw_rcompare(nullptr, nullptr, rhs, &rhs[rhs_len]), ".*");
}

TEST(eya_memory_raw_rcompare, compare_equal_after_different_elements)
{
    constexpr eya_uchar_t lhs[] = {1, 2, 3, 4, 5};
    constexpr eya_uchar_t rhs[] = {6, 7, 8, 4, 5};
    constexpr eya_usize_t len   = eya_static_array_size(lhs);

    EXPECT_EQ(eya_memory_raw_rcompare(lhs, &lhs[len], rhs, &rhs[len]), &lhs[2]);
}

TEST(eya_memory_raw_rcompare, compare_same_last_elements)
{
    constexpr eya_uchar_t lhs[] = {0, 0, 0, 0, 5};
    constexpr eya_uchar_t rhs[] = {0, 0, 0, 0, 5};
    constexpr eya_usize_t len   = eya_static_array_size(lhs);

    EXPECT_EQ(eya_memory_raw_rcompare(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(eya_memory_raw_copy, copy_with64_divisible_length)
{
    constexpr eya_usize_t len = 64;
    eya_uchar_t           src[len];
    eya_uchar_t           dst[len];
    constexpr eya_uchar_t value = 0xAB;

    memset(src, value, len);
    void *result = eya_memory_raw_copy(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (unsigned char i : dst)
    {
        ASSERT_EQ(i, value);
    }
}

TEST(eya_memory_raw_copy, copy_with32_divisible_length)
{
    constexpr eya_usize_t len = 32;
    eya_uchar_t           src[len];
    eya_uchar_t           dst[len];
    constexpr eya_uchar_t value = 0xCD;

    memset(src, value, len);
    void *result = eya_memory_raw_copy(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (unsigned char i : dst)
    {
        ASSERT_EQ(i, value);
    }
}

TEST(eya_memory_raw_copy, copy_with16_divisible_length)
{
    constexpr eya_usize_t len = 16;
    eya_uchar_t           src[len];
    eya_uchar_t           dst[len];
    constexpr eya_uchar_t value = 0xEF;

    memset(src, value, len);
    void *result = eya_memory_raw_copy(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (unsigned char i : dst)
    {
        ASSERT_EQ(i, value);
    }
}

TEST(eya_memory_raw_copy, copy_with8_divisible_length)
{
    constexpr eya_usize_t len = 8;
    eya_uchar_t           src[len];
    eya_uchar_t           dst[len];
    constexpr eya_uchar_t value = 0xFF;

    memset(src, value, len);
    void *result = eya_memory_raw_copy(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (unsigned char i : dst)
    {
        ASSERT_EQ(i, value);
    }
}

TEST(eya_memory_raw_copy, copy_with_non_divisible_length)
{
    constexpr eya_usize_t len = 12;
    eya_uchar_t           src[len];
    eya_uchar_t           dst[len];
    constexpr eya_uchar_t value = 0x01;

    memset(src, value, len);
    void *result = eya_memory_raw_copy(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst + len);

    for (unsigned char i : dst)
    {
        ASSERT_EQ(i, value);
    }
}

TEST(eya_memory_raw_rcopy, copy_rev_with64_divisible_length)
{
    constexpr eya_usize_t len = 64;
    eya_uchar_t           src[len];
    eya_uchar_t           dst[len];
    constexpr eya_uchar_t value = 0xAB;

    memset(src, value, len);
    void *result = eya_memory_raw_rcopy(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    for (eya_usize_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(dst[len - 1 - i], value);
    }
}

TEST(eya_memory_raw_rcopy, copy_rev_with32_divisible_length)
{
    constexpr eya_usize_t len = 32;
    eya_uchar_t           src[len];
    eya_uchar_t           dst[len];
    constexpr eya_uchar_t value = 0xCD;

    memset(src, value, len);
    void *result = eya_memory_raw_rcopy(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    for (eya_usize_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(dst[len - 1 - i], value);
    }
}

TEST(eya_memory_raw_rcopy, copy_rev_with16_divisible_length)
{
    constexpr eya_usize_t len = 16;
    eya_uchar_t           src[len];
    eya_uchar_t           dst[len];
    constexpr eya_uchar_t value = 0xEF;

    memset(src, value, len);
    void *result = eya_memory_raw_rcopy(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    for (eya_usize_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(dst[len - 1 - i], value);
    }
}

TEST(eya_memory_raw_rcopy, copy_rev_with8_divisible_length)
{
    constexpr eya_usize_t len = 8;
    eya_uchar_t           src[len];
    eya_uchar_t           dst[len];
    constexpr eya_uchar_t value = 0xFF;

    memset(src, value, len);
    void *result = eya_memory_raw_rcopy(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    for (eya_usize_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(dst[len - 1 - i], value);
    }
}

TEST(eya_memory_raw_rcopy, copy_rev_with_non_divisible_length)
{
    constexpr eya_usize_t len = 12;
    eya_uchar_t           src[len];
    eya_uchar_t           dst[len];
    constexpr eya_uchar_t value = 0x01;

    memset(src, value, len);
    void *result = eya_memory_raw_rcopy(dst, &dst[len], src, &src[len]);
    EXPECT_EQ(result, dst);

    for (eya_usize_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(dst[len - 1 - i], value);
    }
}

TEST(eya_memory_raw_move, move64_bytes)
{
    constexpr eya_ullong_t src[] = {1, 2, 3, 4};
    eya_ullong_t           dst[4];

    void *result = eya_memory_raw_move(dst, dst + 4, src, src + 4);
    ASSERT_EQ(result, &dst[4]);

    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(dst[i], src[i]);
    }
}

TEST(eya_memory_raw_move, move32_bytes)
{
    constexpr eya_uint_t src[] = {1, 2, 3, 4};
    eya_uint_t           dst[4];

    void *result = eya_memory_raw_move(dst, dst + 4, src, src + 4);
    ASSERT_EQ(result, &dst[4]);

    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(dst[i], src[i]);
    }
}

TEST(eya_memory_raw_move, move16_bytes)
{
    constexpr eya_ushort_t src[] = {1, 2, 3, 4};
    eya_ushort_t           dst[4];

    void *result = eya_memory_raw_move(dst, dst + 4, src, src + 4);
    ASSERT_EQ(result, &dst[4]);

    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(dst[i], src[i]);
    }
}

TEST(eya_memory_raw_move, move8_bytes)
{
    constexpr eya_uchar_t src[] = {1, 2, 3, 4};
    eya_uchar_t           dst[4];

    void *result = eya_memory_raw_move(dst, dst + 4, src, src + 4);
    ASSERT_EQ(result, &dst[4]);

    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(dst[i], src[i]);
    }
}

TEST(eya_memory_raw_move, move64_bytes_overlap)
{
    eya_ullong_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8};

    void *result = eya_memory_raw_move(buf + 2, buf + 2 + 4, buf, buf + 4);
    ASSERT_EQ(result, &buf[6]);

    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(buf[i + 2], i + 1);
    }
}

TEST(eya_memory_raw_move, move32_bytes_overlap)
{
    eya_uint_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8};

    void *result = eya_memory_raw_move(buf + 2, buf + 2 + 4, buf, buf + 4);
    ASSERT_EQ(result, &buf[6]);

    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(buf[i + 2], i + 1);
    }
}

TEST(eya_memory_raw_move, move16_bytes_overlap)
{
    eya_ushort_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8};

    void *result = eya_memory_raw_move(buf + 2, buf + 2 + 4, buf, buf + 4);
    ASSERT_EQ(result, &buf[6]);

    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(buf[i + 2], i + 1);
    }
}

TEST(eya_memory_raw_move, move8_bytes_overlap)
{
    eya_uchar_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8};

    void *result = eya_memory_raw_move(buf + 2, buf + 2 + 4, buf, buf + 4);
    ASSERT_EQ(result, &buf[6]);

    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(buf[i + 2], i + 1);
    }
}

TEST(eya_memory_raw_find, NormalTest)
{
    constexpr eya_uchar_t lhs[] = {1, 2, 3, 4, 5};
    constexpr eya_uchar_t rhs[] = {3, 4};

    const void *result = eya_memory_raw_find(lhs, lhs + 5, rhs, rhs + 2);
    EXPECT_EQ(result, lhs + 2);
}

TEST(eya_memory_raw_find, null_pointer)
{
    const constexpr eya_uchar_t *lhs   = nullptr;
    constexpr eya_uchar_t        rhs[] = {3, 4};

    EXPECT_DEATH(eya_memory_raw_find(lhs, lhs + 5, rhs, rhs + 2), ".*");
}

TEST(eya_memory_raw_find, empty_lhs)
{
    const constexpr eya_uchar_t *lhs   = nullptr;
    constexpr eya_uchar_t        rhs[] = {3, 4};

    EXPECT_DEATH(eya_memory_raw_find(lhs, lhs, rhs, rhs + 2), ".*");
}

TEST(eya_memory_raw_find, empty_rhs)
{
    constexpr eya_uchar_t        lhs[] = {1, 2, 3, 4, 5};
    const constexpr eya_uchar_t *rhs   = nullptr;

    EXPECT_DEATH(eya_memory_raw_find(lhs, lhs + 5, rhs, rhs), ".*");
}

TEST(eya_memory_raw_find, no_match)
{
    constexpr eya_uchar_t lhs[] = {1, 2, 3, 4, 5};
    constexpr eya_uchar_t rhs[] = {6, 7};

    const void *result = eya_memory_raw_find(lhs, lhs + 5, rhs, rhs + 2);
    EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_raw_find, match_at_start)
{
    constexpr eya_uchar_t lhs[] = {3, 4, 5};
    constexpr eya_uchar_t rhs[] = {3, 4};

    const void *result = eya_memory_raw_find(lhs, lhs + 3, rhs, rhs + 2);
    EXPECT_EQ(result, lhs);
}

TEST(eya_memory_raw_rfind, find_substring_in_string)
{
    constexpr eya_uchar_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    constexpr eya_uchar_t rhs[] = {0x03, 0x04};

    const void *result = eya_memory_raw_rfind(lhs, &lhs[6], rhs, &rhs[2]);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, lhs + 2);
}

TEST(eya_memory_raw_rfind, substring_not_found)
{
    constexpr eya_uchar_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    constexpr eya_uchar_t rhs[] = {0x07, 0x08};

    const void *result = eya_memory_raw_rfind(lhs, &lhs[6], rhs, &rhs[2]);
    ASSERT_EQ(result, nullptr);
}

TEST(eya_memory_raw_rfind, find_substring_at_end)
{
    constexpr eya_uchar_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    constexpr eya_uchar_t rhs[] = {0x05, 0x06};

    const void *result = eya_memory_raw_rfind(lhs, &lhs[6], rhs, &rhs[2]);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, lhs + 4);
}

TEST(eya_memory_raw_rfind, empty_arrays)
{
    EXPECT_DEATH(eya_memory_raw_rfind(nullptr, nullptr, nullptr, nullptr), ".*");
}

TEST(eya_memory_raw_rfind, rhs_longer_than_lhs)
{
    constexpr eya_uchar_t lhs[] = {0x01, 0x02, 0x03};
    constexpr eya_uchar_t rhs[] = {0x01, 0x02, 0x03, 0x04};

    ASSERT_EQ(eya_memory_raw_rfind(lhs, &lhs[3], rhs, &rhs[4]), nullptr);
}

TEST(eya_memory_raw_rfind, null_pointer_check)
{
    constexpr eya_uchar_t lhs[] = {0x01, 0x02, 0x03, 0x04};
    constexpr eya_uchar_t rhs[] = {0x03, 0x04};
    EXPECT_DEATH(eya_memory_raw_rfind(nullptr, &lhs[4], rhs, &rhs[2]), ".*");
}

TEST(eya_memory_raw_set, set_with64_divisible_length)
{
    constexpr eya_usize_t len = 64;
    eya_uchar_t           dst[len];
    constexpr eya_uchar_t value = 0xAB;

    void *result = eya_memory_raw_set(dst, &dst[len], value);
    EXPECT_EQ(result, dst + len);

    for (unsigned char i : dst)
    {
        ASSERT_EQ(i, value);
    }
}

TEST(eya_memory_raw_set, set_with32_divisible_length)
{
    constexpr eya_usize_t len = 32;
    eya_uchar_t           dst[len];
    constexpr eya_uchar_t value = 0xCD;

    void *result = eya_memory_raw_set(dst, &dst[len], value);
    EXPECT_EQ(result, dst + len);

    for (unsigned char i : dst)
    {
        ASSERT_EQ(i, value);
    }
}

TEST(eya_memory_raw_set, set_with16_divisible_length)
{
    constexpr eya_usize_t len = 16;
    eya_uchar_t           dst[len];
    constexpr eya_uchar_t value = 0xEF;

    void *result = eya_memory_raw_set(dst, &dst[len], value);
    EXPECT_EQ(result, dst + len);

    for (unsigned char i : dst)
    {
        ASSERT_EQ(i, value);
    }
}

TEST(eya_memory_raw_set, set_with8_divisible_length)
{
    constexpr eya_usize_t len = 8;
    eya_uchar_t           dst[len];
    constexpr eya_uchar_t value = 0xFF;

    void *result = eya_memory_raw_set(dst, &dst[len], value);
    EXPECT_EQ(result, dst + len);

    for (unsigned char i : dst)
    {
        ASSERT_EQ(i, value);
    }
}

TEST(eya_memory_raw_set, set_with_non_divisible_length)
{
    constexpr eya_usize_t len = 12;
    eya_uchar_t           dst[len];
    constexpr eya_uchar_t value = 0x01;

    void *result = eya_memory_raw_set(dst, &dst[len], value);
    EXPECT_EQ(result, dst + len);

    for (unsigned char i : dst)
    {
        ASSERT_EQ(i, value);
    }
}

TEST(eya_memory_raw_set, set_zero_length)
{
    constexpr eya_usize_t len    = 0;
    eya_uchar_t           dst[1] = {0xAA};
    constexpr eya_uchar_t value  = 0x55;

    void *result = eya_memory_raw_set(dst, dst, value);
    EXPECT_EQ(result, dst);
    ASSERT_EQ(dst[0], 0xAA);
}

TEST(eya_memory_raw_set, set_static_array_16_bytes_int16)
{
    eya_ushort_t          dst[8];
    constexpr eya_uchar_t value = 0x3C;

    void *result = eya_memory_raw_set(dst, dst + 8, value);
    EXPECT_EQ(result, dst + 8);

    const auto *ptr = reinterpret_cast<const eya_uchar_t *>(dst);
    for (size_t i = 0; i < 16; i++)
    {
        ASSERT_EQ(ptr[i], value) << "Failed at byte " << i;
    }
}

TEST(eya_memory_raw_set, set_static_array_32_bytes_int32)
{
    eya_uint_t            dst[8];
    constexpr eya_uchar_t value = 0x7E;

    void *result = eya_memory_raw_set(dst, dst + 8, value);
    EXPECT_EQ(result, dst + 8);

    const auto *ptr = reinterpret_cast<const eya_uchar_t *>(dst);
    for (size_t i = 0; i < 32; i++)
    {
        ASSERT_EQ(ptr[i], value) << "Failed at byte " << i;
    }
}

TEST(eya_memory_raw_set, set_static_array_64_bytes_mixed_types)
{
    struct
    {
        eya_ushort_t a[16];
        eya_uint_t   b[8];
    } dst                       = {};
    constexpr eya_uchar_t value = 0xA5;

    void *result = eya_memory_raw_set(&dst, &dst + 1, value);
    EXPECT_EQ(result, &dst + 1);

    const auto *ptr = reinterpret_cast<const eya_uchar_t *>(&dst);
    for (size_t i = 0; i < 64; i++)
    {
        ASSERT_EQ(ptr[i], value) << "Failed at byte " << i;
    }
}

TEST(eya_memory_raw_set, set_large_static_array_1024_bytes_int64)
{
    eya_ullong_t          dst[128];
    constexpr eya_uchar_t value = 0x11;

    void *result = eya_memory_raw_set(dst, dst + 128, value);
    EXPECT_EQ(result, dst + 128);

    const auto *ptr = reinterpret_cast<const eya_uchar_t *>(dst);
    for (size_t i = 0; i < 1024; i++)
    {
        ASSERT_EQ(ptr[i], value) << "Failed at byte " << i;
    }
}

TEST(eya_memory_raw_set, set_small_non_power_of_two_array)
{
    eya_uint_t            dst[5];
    constexpr eya_uchar_t value = 0xBD;

    void *result = eya_memory_raw_set(dst, dst + 5, value);
    EXPECT_EQ(result, dst + 5);

    const auto *ptr = reinterpret_cast<const eya_uchar_t *>(dst);
    for (size_t i = 0; i < 20; i++)
    {
        ASSERT_EQ(ptr[i], value) << "Failed at byte " << i;
    }
}