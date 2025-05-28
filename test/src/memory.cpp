#include <eya/memory.h>
#include <gtest/gtest.h>

TEST(eya_memory_find, find_substring_present) {
  const char lhs[] = "Hello, World!";
  const char rhs[] = "World";
  eya_usize_t lhs_size = strlen(lhs);
  eya_usize_t rhs_size = strlen(rhs);

  const void *result = eya_memory_find(lhs, lhs_size, rhs, rhs_size);
  EXPECT_EQ(result, lhs + 7);
}

TEST(eya_memory_find, find_substring_not_present) {
  const char lhs[] = "Hello, World!";
  const char rhs[] = "Planet";
  eya_usize_t lhs_size = strlen(lhs);
  eya_usize_t rhs_size = strlen(rhs);

  const void *result = eya_memory_find(lhs, lhs_size, rhs, rhs_size);
  EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_find, empty_rhs) {
  const char lhs[] = "Hello, World!";
  const char rhs[] = "";
  eya_usize_t lhs_size = strlen(lhs);
  eya_usize_t rhs_size = 0;

  const void *result = eya_memory_find(lhs, lhs_size, rhs, rhs_size);
  EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_find, empty_lhs) {
  const char lhs[] = "";
  const char rhs[] = "Test";
  eya_usize_t lhs_size = 0;
  eya_usize_t rhs_size = strlen(rhs);

  const void *result = eya_memory_find(lhs, lhs_size, rhs, rhs_size);
  EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_find, both_empty) {
  const char lhs[] = "";
  const char rhs[] = "";
  eya_usize_t lhs_size = 0;
  eya_usize_t rhs_size = 0;

  const void *result = eya_memory_find(lhs, lhs_size, rhs, rhs_size);
  EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_find, substring_at_start) {
  const char lhs[] = "Hello, World!";
  const char rhs[] = "Hello";
  eya_usize_t lhs_size = strlen(lhs);
  eya_usize_t rhs_size = strlen(rhs);

  const void *result = eya_memory_find(lhs, lhs_size, rhs, rhs_size);
  EXPECT_EQ(result, lhs);
}

TEST(eya_memory_find, substring_at_end) {
  const char lhs[] = "Hello, World!";
  const char rhs[] = "!";
  eya_usize_t lhs_size = strlen(lhs);
  eya_usize_t rhs_size = strlen(rhs);

  const void *result = eya_memory_find(lhs, lhs_size, rhs, rhs_size);
  EXPECT_EQ(result, lhs + lhs_size - 1);
}

TEST(eya_memory_find, single_byte_search) {
  const char lhs[] = {0x01, 0x02, 0x03, 0x04};
  const char rhs[] = {0x03};
  eya_usize_t lhs_size = 4;
  eya_usize_t rhs_size = 1;

  const void *result = eya_memory_find(lhs, lhs_size, rhs, rhs_size);
  EXPECT_EQ(result, lhs + 2);
}

TEST(eya_memory_rfind, find_last_substring_present) {
  const char lhs[] = "Hello, World! Hello!";
  const char rhs[] = "Hello";
  eya_usize_t lhs_size = strlen(lhs);
  eya_usize_t rhs_size = strlen(rhs);

  const void *result = eya_memory_rfind(lhs, lhs_size, rhs, rhs_size);
  EXPECT_EQ(result, lhs + 14); // Последнее "Hello" начинается с позиции 14
}

TEST(eya_memory_rfind, find_substring_not_present) {
  const char lhs[] = "Hello, World!";
  const char rhs[] = "Planet";
  eya_usize_t lhs_size = strlen(lhs);
  eya_usize_t rhs_size = strlen(rhs);

  const void *result = eya_memory_rfind(lhs, lhs_size, rhs, rhs_size);
  EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_rfind, empty_rhs) {
  const char lhs[] = "Hello, World!";
  const char rhs[] = "";
  eya_usize_t lhs_size = strlen(lhs);
  eya_usize_t rhs_size = 0;

  const void *result = eya_memory_rfind(lhs, lhs_size, rhs, rhs_size);
  EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_rfind, empty_lhs) {
  const char lhs[] = "";
  const char rhs[] = "Test";
  eya_usize_t lhs_size = 0;
  eya_usize_t rhs_size = strlen(rhs);

  const void *result = eya_memory_rfind(lhs, lhs_size, rhs, rhs_size);
  EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_rfind, both_empty) {
  const char lhs[] = "";
  const char rhs[] = "";
  eya_usize_t lhs_size = 0;
  eya_usize_t rhs_size = 0;

  const void *result = eya_memory_rfind(lhs, lhs_size, rhs, rhs_size);
  EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_rfind, substring_at_start) {
  const char lhs[] = "Hello, World!";
  const char rhs[] = "Hello";
  eya_usize_t lhs_size = strlen(lhs);
  eya_usize_t rhs_size = strlen(rhs);

  const void *result = eya_memory_rfind(lhs, lhs_size, rhs, rhs_size);
  EXPECT_EQ(result, lhs);
}

TEST(eya_memory_rfind, substring_at_end) {
  const char lhs[] = "Hello, World!";
  const char rhs[] = "!";
  eya_usize_t lhs_size = strlen(lhs);
  eya_usize_t rhs_size = strlen(rhs);

  const void *result = eya_memory_rfind(lhs, lhs_size, rhs, rhs_size);
  EXPECT_EQ(result, lhs + lhs_size - 1);
}

TEST(eya_memory_rfind, single_byte_search) {
  const char lhs[] = {0x01, 0x02, 0x03, 0x02};
  const char rhs[] = {0x02};
  eya_usize_t lhs_size = 4;
  eya_usize_t rhs_size = 1;

  const void *result = eya_memory_rfind(lhs, lhs_size, rhs, rhs_size);
  EXPECT_EQ(result, lhs + 3);
}