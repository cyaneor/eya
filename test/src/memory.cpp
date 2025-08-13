#include <eya/memory.h>
#include <gtest/gtest.h>

TEST(eya_memory_find, find_substring_present)
{
    const char  lhs[]    = "Hello, World!";
    const char  rhs[]    = "World";
    eya_usize_t lhs_size = strlen(lhs);
    eya_usize_t rhs_size = strlen(rhs);

    const void *result = eya_memory_find(lhs, lhs_size, rhs, rhs_size);
    EXPECT_EQ(result, lhs + 7);
}

TEST(eya_memory_find, find_substring_not_present)
{
    const char  lhs[]    = "Hello, World!";
    const char  rhs[]    = "Planet";
    eya_usize_t lhs_size = strlen(lhs);
    eya_usize_t rhs_size = strlen(rhs);

    const void *result = eya_memory_find(lhs, lhs_size, rhs, rhs_size);
    EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_find, empty_rhs)
{
    const char  lhs[]    = "Hello, World!";
    const char  rhs[]    = "";
    eya_usize_t lhs_size = strlen(lhs);
    eya_usize_t rhs_size = 0;

    const void *result = eya_memory_find(lhs, lhs_size, rhs, rhs_size);
    EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_find, empty_lhs)
{
    const char  lhs[]    = "";
    const char  rhs[]    = "Test";
    eya_usize_t lhs_size = 0;
    eya_usize_t rhs_size = strlen(rhs);

    const void *result = eya_memory_find(lhs, lhs_size, rhs, rhs_size);
    EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_find, both_empty)
{
    const char  lhs[]    = "";
    const char  rhs[]    = "";
    eya_usize_t lhs_size = 0;
    eya_usize_t rhs_size = 0;

    const void *result = eya_memory_find(lhs, lhs_size, rhs, rhs_size);
    EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_find, substring_at_start)
{
    const char  lhs[]    = "Hello, World!";
    const char  rhs[]    = "Hello";
    eya_usize_t lhs_size = strlen(lhs);
    eya_usize_t rhs_size = strlen(rhs);

    const void *result = eya_memory_find(lhs, lhs_size, rhs, rhs_size);
    EXPECT_EQ(result, lhs);
}

TEST(eya_memory_find, substring_at_end)
{
    const char  lhs[]    = "Hello, World!";
    const char  rhs[]    = "!";
    eya_usize_t lhs_size = strlen(lhs);
    eya_usize_t rhs_size = strlen(rhs);

    const void *result = eya_memory_find(lhs, lhs_size, rhs, rhs_size);
    EXPECT_EQ(result, lhs + lhs_size - 1);
}

TEST(eya_memory_find, single_byte_search)
{
    const char  lhs[]    = {0x01, 0x02, 0x03, 0x04};
    const char  rhs[]    = {0x03};
    eya_usize_t lhs_size = 4;
    eya_usize_t rhs_size = 1;

    const void *result = eya_memory_find(lhs, lhs_size, rhs, rhs_size);
    EXPECT_EQ(result, lhs + 2);
}

TEST(eya_memory_rfind, find_last_substring_present)
{
    const char  lhs[]    = "Hello, World! Hello!";
    const char  rhs[]    = "Hello";
    eya_usize_t lhs_size = strlen(lhs);
    eya_usize_t rhs_size = strlen(rhs);

    const void *result = eya_memory_rfind(lhs, lhs_size, rhs, rhs_size);
    EXPECT_EQ(result, lhs + 14); // Последнее "Hello" начинается с позиции 14
}

TEST(eya_memory_rfind, find_substring_not_present)
{
    const char  lhs[]    = "Hello, World!";
    const char  rhs[]    = "Planet";
    eya_usize_t lhs_size = strlen(lhs);
    eya_usize_t rhs_size = strlen(rhs);

    const void *result = eya_memory_rfind(lhs, lhs_size, rhs, rhs_size);
    EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_rfind, empty_rhs)
{
    const char  lhs[]    = "Hello, World!";
    const char  rhs[]    = "";
    eya_usize_t lhs_size = strlen(lhs);
    eya_usize_t rhs_size = 0;

    const void *result = eya_memory_rfind(lhs, lhs_size, rhs, rhs_size);
    EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_rfind, empty_lhs)
{
    const char  lhs[]    = "";
    const char  rhs[]    = "Test";
    eya_usize_t lhs_size = 0;
    eya_usize_t rhs_size = strlen(rhs);

    const void *result = eya_memory_rfind(lhs, lhs_size, rhs, rhs_size);
    EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_rfind, both_empty)
{
    const char  lhs[]    = "";
    const char  rhs[]    = "";
    eya_usize_t lhs_size = 0;
    eya_usize_t rhs_size = 0;

    const void *result = eya_memory_rfind(lhs, lhs_size, rhs, rhs_size);
    EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_rfind, substring_at_start)
{
    const char  lhs[]    = "Hello, World!";
    const char  rhs[]    = "Hello";
    eya_usize_t lhs_size = strlen(lhs);
    eya_usize_t rhs_size = strlen(rhs);

    const void *result = eya_memory_rfind(lhs, lhs_size, rhs, rhs_size);
    EXPECT_EQ(result, lhs);
}

TEST(eya_memory_rfind, substring_at_end)
{
    const char  lhs[]    = "Hello, World!";
    const char  rhs[]    = "!";
    eya_usize_t lhs_size = strlen(lhs);
    eya_usize_t rhs_size = strlen(rhs);

    const void *result = eya_memory_rfind(lhs, lhs_size, rhs, rhs_size);
    EXPECT_EQ(result, lhs + lhs_size - 1);
}

TEST(eya_memory_rfind, single_byte_search)
{
    const char  lhs[]    = {0x01, 0x02, 0x03, 0x02};
    const char  rhs[]    = {0x02};
    eya_usize_t lhs_size = 4;
    eya_usize_t rhs_size = 1;

    const void *result = eya_memory_rfind(lhs, lhs_size, rhs, rhs_size);
    EXPECT_EQ(result, lhs + 3);
}

TEST(eya_memory_set_pattern, set_pattern_in_middle)
{
    char        buffer[10]   = {0};
    const char  pattern[]    = "AB";
    eya_usize_t pattern_size = sizeof(pattern) - 1;

    eya_memory_set_pattern(buffer + 2, 6, pattern, pattern_size);

    EXPECT_EQ(buffer[2], 'A');
    EXPECT_EQ(buffer[3], 'B');
    EXPECT_EQ(buffer[4], 'A');
    EXPECT_EQ(buffer[5], 'B');
    EXPECT_EQ(buffer[6], 'A');
    EXPECT_EQ(buffer[7], 'B');
    EXPECT_EQ(buffer[8], 0); // Should be zero as it's beyond the pattern size
}

TEST(eya_memory_set_pattern, set_pattern_at_start)
{
    char        buffer[10]   = {0};
    const char  pattern[]    = "XYZ";
    eya_usize_t pattern_size = sizeof(pattern) - 1;

    eya_memory_set_pattern(buffer, 10, pattern, pattern_size);

    EXPECT_EQ(buffer[0], 'X');
    EXPECT_EQ(buffer[1], 'Y');
    EXPECT_EQ(buffer[2], 'Z');
    EXPECT_EQ(buffer[3], 'X');
    EXPECT_EQ(buffer[4], 'Y');
    EXPECT_EQ(buffer[5], 'Z');
}

TEST(eya_memory_set_pattern, set_pattern_with_leftover_space)
{
    char        buffer[7]    = {0};
    const char  pattern[]    = "12345";
    eya_usize_t pattern_size = sizeof(pattern) - 1;

    eya_memory_set_pattern(buffer, 7, pattern, pattern_size);

    EXPECT_EQ(buffer[0], '1');
    EXPECT_EQ(buffer[1], '2');
    EXPECT_EQ(buffer[2], '3');
    EXPECT_EQ(buffer[3], '4');
    EXPECT_EQ(buffer[4], '5');
    EXPECT_EQ(buffer[5], '1'); // Pattern wraps around
    EXPECT_EQ(buffer[6], '2'); // Pattern wraps around
}

TEST(eya_memory_set_pattern, pattern_larger_than_buffer)
{
    char        buffer[4]    = {0};
    const char  pattern[]    = "ABCDE";
    eya_usize_t pattern_size = sizeof(pattern) - 1;

    eya_memory_set_pattern(buffer, 4, pattern, pattern_size);

    EXPECT_EQ(buffer[0], 'A');
    EXPECT_EQ(buffer[1], 'B');
    EXPECT_EQ(buffer[2], 'C');
    EXPECT_EQ(buffer[3], 'D'); // Should not go beyond the buffer size
}

TEST(eya_memory_set_pattern, empty_pattern)
{
    char        buffer[10]   = {0};
    const char  pattern[]    = "";
    eya_usize_t pattern_size = 0;

    eya_memory_set_pattern(buffer, 10, pattern, pattern_size);

    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ(buffer[i], 0); // Buffer should remain unchanged
    }
}

TEST(eya_memory_set_pattern, empty_buffer)
{
    char       *buffer       = nullptr;
    const char  pattern[]    = "Hello";
    eya_usize_t pattern_size = sizeof(pattern) - 1;
    EXPECT_DEATH(eya_memory_set_pattern(buffer, 0, pattern, pattern_size), ".*");
}

TEST(eya_memory_set_pattern, single_byte_pattern)
{
    char        buffer[10]   = {0};
    const char  pattern[]    = "A";
    eya_usize_t pattern_size = sizeof(pattern) - 1;

    eya_memory_set_pattern(buffer, 10, pattern, pattern_size);

    EXPECT_EQ(buffer[0], 'A');
    EXPECT_EQ(buffer[1], 'A');
    EXPECT_EQ(buffer[2], 'A');
    EXPECT_EQ(buffer[3], 'A');
    EXPECT_EQ(buffer[4], 'A');
    EXPECT_EQ(buffer[5], 'A');
    EXPECT_EQ(buffer[6], 'A');
    EXPECT_EQ(buffer[7], 'A');
    EXPECT_EQ(buffer[8], 'A');
    EXPECT_EQ(buffer[9], 'A');
}