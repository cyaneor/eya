#include <eya/memory_std.h>
#include <gtest/gtest.h>

TEST(eya_memory_std_set, fill_zero_length)
{
    static unsigned char buffer[10] = {0};
    void                *ret        = eya_memory_std_set(buffer, 0xAA, 0);
    for (size_t i = 0; i < sizeof(buffer); ++i)
    {
        EXPECT_EQ(buffer[i], 0);
    }
    EXPECT_EQ(ret, buffer);
}

TEST(eya_memory_std_set, fill_full_buffer)
{
    static unsigned char buffer[64];
    void                *ret = eya_memory_std_set(buffer, 0x55, sizeof(buffer));
    for (size_t i = 0; i < sizeof(buffer); ++i)
    {
        EXPECT_EQ(buffer[i], 0x55);
    }
    EXPECT_EQ(ret, buffer + sizeof(buffer));
}

TEST(eya_memory_std_set, fill_partial_buffer)
{
    static unsigned char buffer[32];
    eya_memory_std_set(buffer, 0, sizeof(buffer));
    size_t fill_size = 20;
    void  *ret       = eya_memory_std_set(buffer, 0xFF, fill_size);
    for (size_t i = 0; i < fill_size; ++i)
    {
        EXPECT_EQ(buffer[i], 0xFF);
    }
    for (size_t i = fill_size; i < sizeof(buffer); ++i)
    {
        EXPECT_EQ(buffer[i], 0);
    }
    EXPECT_EQ(ret, buffer + fill_size);
}

TEST(eya_memory_std_set, fill_single_byte)
{
    static unsigned char buffer[1] = {0};
    void                *ret       = eya_memory_std_set(buffer, 0x7E, 1);
    EXPECT_EQ(buffer[0], 0x7E);
    EXPECT_EQ(ret, buffer + 1);
}

TEST(eya_memory_std_set, fill_large_buffer)
{
    static unsigned char buffer[128];
    eya_memory_std_set(buffer, 0, sizeof(buffer));
    void *ret = eya_memory_std_set(buffer, 0x0F, sizeof(buffer));
    for (size_t i = 0; i < sizeof(buffer); ++i)
    {
        EXPECT_EQ(buffer[i], 0x0F);
    }
    EXPECT_EQ(ret, buffer + sizeof(buffer));
}

TEST(eya_memory_std_copy, small_array_copy)
{
    static const char src[]            = "Hello, world!";
    char              dst[sizeof(src)] = {0};

    void *ret = eya_memory_std_copy(dst, src, sizeof(src));
    EXPECT_EQ(ret, dst + sizeof(src));
    EXPECT_EQ(0, memcmp(dst, src, sizeof(src)));
}

TEST(eya_memory_std_copy, large_array_copy)
{
    static const size_t size = 1024 * 1024;
    static char         src[size];
    static char         dst[size];

    for (size_t i = 0; i < size; ++i)
    {
        src[i] = static_cast<char>(i & 0xFF);
    }
    eya_memory_std_set(dst, 0, size);

    void *ret = eya_memory_std_copy(dst, src, size);
    EXPECT_EQ(ret, dst + size);
    EXPECT_EQ(0, memcmp(dst, src, size));
}

TEST(eya_memory_std_copy, one_byte_copy)
{
    static const char src[]  = {42};
    char              dst[1] = {0};

    void *ret = eya_memory_std_copy(dst, src, 1);
    EXPECT_EQ(ret, dst + 1);
    EXPECT_EQ(dst[0], src[0]);
}

TEST(eya_memory_std_copy, nullptr_dst)
{
    static const char src[] = "data";
    EXPECT_DEATH(eya_memory_std_copy(nullptr, src, sizeof(src)), ".*");
}

TEST(eya_memory_std_copy, nullptr_src)
{
    char dst[10];
    EXPECT_DEATH(eya_memory_std_copy(dst, nullptr, 10), ".*");
}

TEST(eya_memory_std_copy, return_pointer_is_end_of_copied_block)
{
    static const char src[]            = "Test data";
    char              dst[sizeof(src)] = {0};

    void *ret = eya_memory_std_copy(dst, src, sizeof(src));
    EXPECT_EQ(ret, dst + sizeof(src));
}

TEST(eya_memory_std_copy, return_pointer_with_zero_length)
{
    static const char src[]            = "Test data";
    char              dst[sizeof(src)] = {0};

    void *ret = eya_memory_std_copy(dst, src, 0);
    EXPECT_EQ(ret, dst);
}

TEST(eya_memory_std_copy, copy_128_bytes)
{
    static const size_t size = 128;
    static char         src[size];
    static char         dst[size];

    for (size_t i = 0; i < size; ++i)
    {
        src[i] = static_cast<char>(i & 0xFF);
    }
    eya_memory_std_set(dst, 0, size);

    void *ret = eya_memory_std_copy(dst, src, size);
    EXPECT_EQ(ret, dst + size);
    EXPECT_EQ(0, memcmp(dst, src, size));
}

TEST(eya_memory_std_copy, copy_256_bytes)
{
    static const size_t size = 256;
    static char         src[size];
    static char         dst[size];

    for (size_t i = 0; i < size; ++i)
    {
        src[i] = static_cast<char>(i & 0xFF);
    }
    eya_memory_std_set(dst, 0, size);

    void *ret = eya_memory_std_copy(dst, src, size);
    EXPECT_EQ(ret, dst + size);
    EXPECT_EQ(0, memcmp(dst, src, size));
}

TEST(eya_memory_std_copy, copy_512_bytes)
{
    static const size_t size = 512;
    static char         src[size];
    static char         dst[size];

    for (size_t i = 0; i < size; ++i)
    {
        src[i] = static_cast<char>(i & 0xFF);
    }
    eya_memory_std_set(dst, 0, size);

    void *ret = eya_memory_std_copy(dst, src, size);
    EXPECT_EQ(ret, dst + size);
    EXPECT_EQ(0, memcmp(dst, src, size));
}

TEST(eya_memory_std_copy_rev, small_array_copy)
{
    static const char src[]            = "Hello, world!";
    char              dst[sizeof(src)] = {0};

    void *ret = eya_memory_std_copy_rev(dst, src, sizeof(src));
    EXPECT_EQ(ret, dst + sizeof(src));
    for (size_t i = 0; i < sizeof(src); ++i)
    {
        EXPECT_EQ(dst[i], src[sizeof(src) - 1 - i]);
    }
}

TEST(eya_memory_std_copy_rev, large_array_copy)
{
    static const size_t size = 1024 * 1024;
    static char         src[size];
    static char         dst[size];

    for (size_t i = 0; i < size; ++i)
    {
        src[i] = static_cast<char>(i & 0xFF);
    }
    eya_memory_std_set(dst, 0, size);

    void *ret = eya_memory_std_copy_rev(dst, src, size);
    EXPECT_EQ(ret, dst + size);
    for (size_t i = 0; i < size; ++i)
    {
        EXPECT_EQ(dst[i], src[size - 1 - i]);
    }
}

TEST(eya_memory_std_copy_rev, one_byte_copy)
{
    static const char src[]  = {42};
    char              dst[1] = {0};

    void *ret = eya_memory_std_copy_rev(dst, src, 1);
    EXPECT_EQ(ret, dst + 1);
    EXPECT_EQ(dst[0], src[0]);
}

TEST(eya_memory_std_copy_rev, nullptr_dst)
{
    static const char src[] = "data";
    EXPECT_DEATH(eya_memory_std_copy_rev(nullptr, src, sizeof(src)), ".*");
}

TEST(eya_memory_std_copy_rev, nullptr_src)
{
    char dst[10];
    EXPECT_DEATH(eya_memory_std_copy_rev(dst, nullptr, 10), ".*");
}

TEST(eya_memory_std_copy_rev, return_pointer_is_end_of_copied_block)
{
    static const char src[]            = "Test data";
    char              dst[sizeof(src)] = {0};

    void *ret = eya_memory_std_copy_rev(dst, src, sizeof(src));
    EXPECT_EQ(ret, dst + sizeof(src));
}

TEST(eya_memory_std_copy_rev, return_pointer_with_zero_length)
{
    static const char src[]            = "Test data";
    char              dst[sizeof(src)] = {0};

    void *ret = eya_memory_std_copy_rev(dst, src, 0);
    EXPECT_EQ(ret, dst);
}

TEST(eya_memory_std_copy_rev, copy_128_bytes)
{
    static const size_t size = 128;
    static char         src[size];
    static char         dst[size];

    for (size_t i = 0; i < size; ++i)
    {
        src[i] = static_cast<char>(i & 0xFF);
    }
    eya_memory_std_set(dst, 0, size);

    void *ret = eya_memory_std_copy_rev(dst, src, size);
    EXPECT_EQ(ret, dst + size);
    for (size_t i = 0; i < size; ++i)
    {
        EXPECT_EQ(dst[i], src[size - 1 - i]);
    }
}

TEST(eya_memory_std_copy_rev, copy_256_bytes)
{
    static const size_t size = 256;
    static char         src[size];
    static char         dst[size];

    for (size_t i = 0; i < size; ++i)
    {
        src[i] = static_cast<char>(i & 0xFF);
    }
    eya_memory_std_set(dst, 0, size);

    void *ret = eya_memory_std_copy_rev(dst, src, size);
    EXPECT_EQ(ret, dst + size);
    for (size_t i = 0; i < size; ++i)
    {
        EXPECT_EQ(dst[i], src[size - 1 - i]);
    }
}

TEST(eya_memory_std_copy_rev, copy_512_bytes)
{
    static const size_t size = 512;
    static char         src[size];
    static char         dst[size];

    for (size_t i = 0; i < size; ++i)
    {
        src[i] = static_cast<char>(i & 0xFF);
    }
    eya_memory_std_set(dst, 0, size);

    void *ret = eya_memory_std_copy_rev(dst, src, size);
    EXPECT_EQ(ret, dst + size);
    for (size_t i = 0; i < size; ++i)
    {
        EXPECT_EQ(dst[i], src[size - 1 - i]);
    }
}

TEST(eya_memory_std_rcopy, small_array_copy)
{
    static const char src[]            = "Hello, world!";
    char              dst[sizeof(src)] = {0};

    void *ret = eya_memory_std_rcopy(dst, src, sizeof(src));
    EXPECT_EQ(ret, dst);
    EXPECT_EQ(0, memcmp(dst, src, sizeof(src)));
}

TEST(eya_memory_std_rcopy, large_array_copy)
{
    static const size_t size = 1024 * 1024;
    static char         src[size];
    static char         dst[size];

    for (size_t i = 0; i < size; ++i)
    {
        src[i] = static_cast<char>(i & 0xFF);
    }
    eya_memory_std_set(dst, 0, size);

    void *ret = eya_memory_std_rcopy(dst, src, size);
    EXPECT_EQ(ret, dst);
    EXPECT_EQ(0, memcmp(dst, src, size));
}

TEST(eya_memory_std_rcopy, one_byte_copy)
{
    static const char src[]  = {42};
    char              dst[1] = {0};

    void *ret = eya_memory_std_rcopy(dst, src, 1);
    EXPECT_EQ(ret, dst);
    EXPECT_EQ(dst[0], src[0]);
}

TEST(eya_memory_std_rcopy, zero_length_copy)
{
    static const char src[]            = "test";
    char              dst[sizeof(src)] = {0};

    void *ret = eya_memory_std_rcopy(dst, src, 0);
    EXPECT_EQ(ret, dst);
    // dst should remain unchanged (all zeros)
    for (size_t i = 0; i < sizeof(src); ++i)
    {
        EXPECT_EQ(dst[i], 0);
    }
}

TEST(eya_memory_std_rcopy, nullptr_dst)
{
    static const char src[] = "data";
    EXPECT_DEATH(eya_memory_std_rcopy(nullptr, src, sizeof(src)), ".*");
}

TEST(eya_memory_std_rcopy, nullptr_src)
{
    char dst[10];
    EXPECT_DEATH(eya_memory_std_rcopy(dst, nullptr, 10), ".*");
}

TEST(eya_memory_std_rcopy, return_pointer_is_start_of_dst)
{
    static const char src[]            = "Test data";
    char              dst[sizeof(src)] = {0};

    void *ret = eya_memory_std_rcopy(dst, src, sizeof(src));
    EXPECT_EQ(ret, dst);
}

TEST(eya_memory_std_rcopy, return_pointer_with_zero_length)
{
    static const char src[]            = "Test data";
    char              dst[sizeof(src)] = {0};

    void *ret = eya_memory_std_rcopy(dst, src, 0);
    EXPECT_EQ(ret, dst);
}

TEST(eya_memory_std_rcopy, rcopy_128_bytes)
{
    static const size_t size = 128;
    static char         src[size];
    static char         dst[size];

    for (size_t i = 0; i < size; ++i)
    {
        src[i] = static_cast<char>(i & 0xFF);
    }
    eya_memory_std_set(dst, 0, size);

    void *ret = eya_memory_std_rcopy(dst, src, size);
    EXPECT_EQ(ret, dst);
    EXPECT_EQ(0, memcmp(dst, src, size));
}

TEST(eya_memory_std_rcopy, rcopy_256_bytes)
{
    static const size_t size = 256;
    static char         src[size];
    static char         dst[size];

    for (size_t i = 0; i < size; ++i)
    {
        src[i] = static_cast<char>(i & 0xFF);
    }
    eya_memory_std_set(dst, 0, size);

    void *ret = eya_memory_std_rcopy(dst, src, size);
    EXPECT_EQ(ret, dst);
    EXPECT_EQ(0, memcmp(dst, src, size));
}

TEST(eya_memory_std_rcopy, rcopy_512_bytes)
{
    static const size_t size = 512;
    static char         src[size];
    static char         dst[size];

    for (size_t i = 0; i < size; ++i)
    {
        src[i] = static_cast<char>(i & 0xFF);
    }
    eya_memory_std_set(dst, 0, size);

    void *ret = eya_memory_std_rcopy(dst, src, size);
    EXPECT_EQ(ret, dst);
    EXPECT_EQ(0, memcmp(dst, src, size));
}

TEST(eya_memory_std_move, non_overlapping_regions)
{
    const char src[]            = "test data";
    char       dst[sizeof(src)] = {0};

    void *result = eya_memory_std_move(dst, src, sizeof(src));

    // Verify data was copied correctly
    EXPECT_EQ(0, memcmp(dst, src, sizeof(src)));

    // Verify return value points to end of destination
    EXPECT_EQ(static_cast<char *>(result), dst + sizeof(src));
}

TEST(eya_memory_std_move, overlapping_regions_src_before_dst)
{
    char         buffer[]  = "abcdefghij";
    const size_t move_size = 5;
    const char  *src       = buffer;
    void        *dst       = buffer + 2; // Overlapping

    void *result = eya_memory_std_move(dst, src, move_size);

    // Verify expected result after move
    EXPECT_STREQ(buffer, "ababcdehij");

    // Verify return value
    EXPECT_EQ(static_cast<char *>(result), static_cast<char *>(dst) + move_size);
}

TEST(eya_memory_std_move, overlapping_regions_dst_before_src)
{
    char         buffer[]  = "abcdefghij";
    const size_t move_size = 5;
    void        *dst       = buffer;
    const char  *src       = buffer + 2; // Overlapping

    void *result = eya_memory_std_move(dst, src, move_size);

    // Verify expected result after move (should use reverse copy)
    EXPECT_STREQ(buffer, "cdefgfghij");

    // Verify return value
    EXPECT_EQ(static_cast<char *>(result), static_cast<char *>(dst) + move_size);
}

TEST(eya_memory_std_move, zero_byte_move)
{
    char src[] = "source";
    char dst[] = "destination";

    void *result = eya_memory_std_move(dst, src, 0);

    // Verify nothing was changed
    EXPECT_STREQ(dst, "destination");
    EXPECT_EQ(result, dst);
}

TEST(eya_memory_std_move, null_pointers)
{
    // This test assumes the function handles null pointers gracefully
    // Note: In real code, we might want to add assertions for this case
    EXPECT_DEATH(eya_memory_std_move(nullptr, nullptr, 10), ".*");
}

TEST(eya_memory_std_move, full_overlap_same_pointer)
{
    char        buffer[] = "test data";
    const char *original = "test data";

    void *result = eya_memory_std_move(buffer, buffer, sizeof(buffer));

    // Should remain unchanged
    EXPECT_STREQ(buffer, original);
    EXPECT_EQ(static_cast<char *>(result), buffer + sizeof(buffer));
}

TEST(eya_memory_std_move, partial_overlap_small_buffer)
{
    char  buffer[5] = {1, 2, 3, 4, 5};
    void *result    = eya_memory_std_move(buffer + 1, buffer, 3);

    // Expected result: [1, 1, 2, 3, 5]
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 1);
    EXPECT_EQ(buffer[2], 2);
    EXPECT_EQ(buffer[3], 3);
    EXPECT_EQ(buffer[4], 5);
    EXPECT_EQ(static_cast<char *>(result), buffer + 1 + 3);
}

TEST(eya_memory_std_compare, equal_buffers)
{
    // Small buffer (within EYA_MEMORY_STD_SMALL_BLOCK_THRESHOLD)
    char buf1[] = "abcdefghijklmnop";
    char buf2[] = "abcdefghijklmnop";
    EXPECT_EQ(nullptr, eya_memory_std_compare(buf1, buf2, 16));

    // Medium buffer (SIMD block size)
    char buf3[32];
    char buf4[32];
    eya_memory_std_set(buf3, 'A', 32);
    eya_memory_std_set(buf4, 'A', 32);
    EXPECT_EQ(nullptr, eya_memory_std_compare(buf3, buf4, 32));

    // Large buffer (stream threshold)
    char buf5[128];
    char buf6[128];
    eya_memory_std_set(buf5, 'B', 128);
    eya_memory_std_set(buf6, 'B', 128);
    EXPECT_EQ(nullptr, eya_memory_std_compare(buf5, buf6, 128));

    // Zero size
    EXPECT_EQ(nullptr, eya_memory_std_compare(buf1, buf2, 0));
}

// Test unequal buffers with difference at various positions
TEST(eya_memory_std_compare, unequal_buffers)
{
    // Difference in first byte
    char buf1[] = "Xbcdefgh";
    char buf2[] = "Ybcdefgh";
    EXPECT_EQ(buf1, eya_memory_std_compare(buf1, buf2, 8));

    // Difference in middle (byte 4)
    char buf3[] = "abcdXghi";
    char buf4[] = "abcdYghi";
    EXPECT_EQ(buf3 + 4, eya_memory_std_compare(buf3, buf4, 8));

    // Difference in last byte
    char buf5[] = "abcdefgh";
    char buf6[] = "abcdefgX";
    EXPECT_EQ(buf5 + 7, eya_memory_std_compare(buf5, buf6, 8));

    // Difference in 64-bit block
    char buf7[] = "abcdefghijklmnop";
    char buf8[] = "abcdefghijkXmnop";
    EXPECT_EQ(buf7 + 11, eya_memory_std_compare(buf7, buf8, 16));

    // Difference in SIMD block
    char buf9[32];
    char buf10[32];
    eya_memory_std_set(buf9, 'A', 32);
    eya_memory_std_set(buf10, 'A', 32);
    buf9[20]  = 'X';
    buf10[20] = 'Y';
    EXPECT_EQ(buf9 + 20, eya_memory_std_compare(buf9, buf10, 32));
}

// Test unaligned buffers
TEST(eya_memory_std_compare, unaligned_buffers)
{
    char buf1[] = "abcdefghijklmnopqrst";
    char buf2[] = "abcdefghijklmnopqrst";
    // Offset lhs by 1 to make it unaligned
    EXPECT_EQ(nullptr, eya_memory_std_compare(buf1 + 1, buf2 + 1, 16));

    // Unequal unaligned buffers
    char buf3[] = "abcdefghXjklmnopqrst";
    char buf4[] = "abcdefghYjklmnopqrst";
    EXPECT_EQ(buf3 + 8, eya_memory_std_compare(buf3 + 1, buf4 + 1, 16));
}

// Test partial block sizes
TEST(eya_memory_std_compare, partial_blocks)
{
    char buf1[] = "abcdefg";
    char buf2[] = "abcdefg";
    EXPECT_EQ(nullptr, eya_memory_std_compare(buf1, buf2, 7));

    char buf3[] = "abcdefX";
    char buf4[] = "abcdefY";
    EXPECT_EQ(buf3 + 6, eya_memory_std_compare(buf3, buf4, 7));

    // Single byte
    char buf5[] = "A";
    char buf6[] = "A";
    EXPECT_EQ(nullptr, eya_memory_std_compare(buf5, buf6, 1));

    char buf7[] = "A";
    char buf8[] = "B";
    EXPECT_EQ(buf7, eya_memory_std_compare(buf7, buf8, 1));
}

TEST(eya_memory_std_rcompare, empty_input)
{
    uint8_t lhs[1] = {0};
    uint8_t rhs[1] = {0};
    EXPECT_EQ(nullptr, eya_memory_std_rcompare(lhs, rhs, 0));
}

TEST(eya_memory_std_rcompare, small_block_identical)
{
    uint8_t lhs[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    uint8_t rhs[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    EXPECT_EQ(nullptr, eya_memory_std_rcompare(lhs, rhs, 16));
}

TEST(eya_memory_std_rcompare, small_block_mismatch_last)
{
    uint8_t lhs[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    uint8_t rhs[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 99};
    EXPECT_EQ(lhs + 15, eya_memory_std_rcompare(lhs, rhs, 16));
}

TEST(eya_memory_std_rcompare, small_block_mismatch_first)
{
    uint8_t lhs[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    uint8_t rhs[16] = {99, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    EXPECT_EQ(lhs + 0, eya_memory_std_rcompare(lhs, rhs, 16));
}

TEST(eya_memory_std_rcompare, medium_block_identical)
{
    uint8_t lhs[32];
    uint8_t rhs[32];
    eya_memory_std_set(lhs, 0xAA, 32);
    eya_memory_std_set(rhs, 0xAA, 32);
    EXPECT_EQ(nullptr, eya_memory_std_rcompare(lhs, rhs, 32));
}

TEST(eya_memory_std_rcompare, medium_block_mismatch_middle)
{
    uint8_t lhs[32];
    uint8_t rhs[32];
    eya_memory_std_set(lhs, 0xAA, 32);
    eya_memory_std_set(rhs, 0xAA, 32);
    lhs[16] = 0xBB;
    EXPECT_EQ(lhs + 16, eya_memory_std_rcompare(lhs, rhs, 32));
}

TEST(eya_memory_std_rcompare, large_block_identical)
{
    uint8_t lhs[128];
    uint8_t rhs[128];
    eya_memory_std_set(lhs, 0x55, 128);
    eya_memory_std_set(rhs, 0x55, 128);
    EXPECT_EQ(nullptr, eya_memory_std_rcompare(lhs, rhs, 128));
}

TEST(eya_memory_std_rcompare, large_block_mismatch_end)
{
    uint8_t lhs[128];
    uint8_t rhs[128];
    eya_memory_std_set(lhs, 0x55, 128);
    eya_memory_std_set(rhs, 0x55, 128);
    lhs[127] = 0x66;
    EXPECT_EQ(lhs + 127, eya_memory_std_rcompare(lhs, rhs, 128));
}

TEST(eya_memory_std_rcompare, large_block_mismatch_start)
{
    uint8_t lhs[128];
    uint8_t rhs[128];
    eya_memory_std_set(lhs, 0x55, 128);
    eya_memory_std_set(rhs, 0x55, 128);
    lhs[0] = 0x66;
    EXPECT_EQ(lhs + 0, eya_memory_std_rcompare(lhs, rhs, 128));
}

TEST(eya_memory_std_rcompare, unaligned_input)
{
    alignas(64) uint8_t lhs[135];
    alignas(64) uint8_t rhs[135];
    eya_memory_std_set(lhs, 0x33, 135);
    eya_memory_std_set(rhs, 0x33, 135);
    // Test with unaligned start (offset by 1 byte)
    EXPECT_EQ(nullptr, eya_memory_std_rcompare(lhs + 1, rhs + 1, 134));
}

TEST(eya_memory_std_rcompare, unaligned_mismatch)
{
    alignas(64) uint8_t lhs[135];
    alignas(64) uint8_t rhs[135];
    eya_memory_std_set(lhs, 0x33, 135);
    eya_memory_std_set(rhs, 0x33, 135);
    lhs[66] = 0x44;
    // Test with unaligned start (offset by 1 byte)
    EXPECT_EQ(lhs + 66, eya_memory_std_rcompare(lhs + 1, rhs + 1, 134));
}