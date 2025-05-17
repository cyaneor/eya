#include <eya/memory_std.h>
#include <gtest/gtest.h>

TEST(eya_memory_std_set, fill_zero_length) {
  static unsigned char buffer[10] = {0};
  void *ret = eya_memory_std_set(buffer, 0xAA, 0);
  for (size_t i = 0; i < sizeof(buffer); ++i) {
    EXPECT_EQ(buffer[i], 0);
  }
  EXPECT_EQ(ret, buffer);
}

TEST(eya_memory_std_set, fill_full_buffer) {
  static unsigned char buffer[64];
  void *ret = eya_memory_std_set(buffer, 0x55, sizeof(buffer));
  for (size_t i = 0; i < sizeof(buffer); ++i) {
    EXPECT_EQ(buffer[i], 0x55);
  }
  EXPECT_EQ(ret, buffer + sizeof(buffer));
}

TEST(eya_memory_std_set, fill_partial_buffer) {
  static unsigned char buffer[32];
  memset(buffer, 0, sizeof(buffer));
  size_t fill_size = 20;
  void *ret = eya_memory_std_set(buffer, 0xFF, fill_size);
  for (size_t i = 0; i < fill_size; ++i) {
    EXPECT_EQ(buffer[i], 0xFF);
  }
  for (size_t i = fill_size; i < sizeof(buffer); ++i) {
    EXPECT_EQ(buffer[i], 0);
  }
  EXPECT_EQ(ret, buffer + fill_size);
}

TEST(eya_memory_std_set, fill_single_byte) {
  static unsigned char buffer[1] = {0};
  void *ret = eya_memory_std_set(buffer, 0x7E, 1);
  EXPECT_EQ(buffer[0], 0x7E);
  EXPECT_EQ(ret, buffer + 1);
}

TEST(eya_memory_std_set, fill_large_buffer) {
  static unsigned char buffer[128];
  memset(buffer, 0, sizeof(buffer));
  void *ret = eya_memory_std_set(buffer, 0x0F, sizeof(buffer));
  for (size_t i = 0; i < sizeof(buffer); ++i) {
    EXPECT_EQ(buffer[i], 0x0F);
  }
  EXPECT_EQ(ret, buffer + sizeof(buffer));
}
