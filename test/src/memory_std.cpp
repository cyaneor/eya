#include <eya/memory_std.h>
#include <gtest/gtest.h>

TEST(eya_memory_std_set, fill_zero_length)
{
  static unsigned char buffer[10] = {0};
  void *ret = eya_memory_std_set(buffer, 0xAA, 0);
  for (size_t i = 0; i < sizeof(buffer); ++i)
  {
    EXPECT_EQ(buffer[i], 0);
  }
  EXPECT_EQ(ret, buffer);
}

TEST(eya_memory_std_set, fill_full_buffer)
{
  static unsigned char buffer[64];
  void *ret = eya_memory_std_set(buffer, 0x55, sizeof(buffer));
  for (size_t i = 0; i < sizeof(buffer); ++i)
  {
    EXPECT_EQ(buffer[i], 0x55);
  }
  EXPECT_EQ(ret, buffer + sizeof(buffer));
}

TEST(eya_memory_std_set, fill_partial_buffer)
{
  static unsigned char buffer[32];
  memset(buffer, 0, sizeof(buffer));
  size_t fill_size = 20;
  void *ret = eya_memory_std_set(buffer, 0xFF, fill_size);
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
  void *ret = eya_memory_std_set(buffer, 0x7E, 1);
  EXPECT_EQ(buffer[0], 0x7E);
  EXPECT_EQ(ret, buffer + 1);
}

TEST(eya_memory_std_set, fill_large_buffer)
{
  static unsigned char buffer[128];
  memset(buffer, 0, sizeof(buffer));
  void *ret = eya_memory_std_set(buffer, 0x0F, sizeof(buffer));
  for (size_t i = 0; i < sizeof(buffer); ++i)
  {
    EXPECT_EQ(buffer[i], 0x0F);
  }
  EXPECT_EQ(ret, buffer + sizeof(buffer));
}

TEST(eya_memory_std_copy, small_array_copy)
{
  static const char src[] = "Hello, world!";
  char dst[sizeof(src)] = {0};

  void *ret = eya_memory_std_copy(dst, src, sizeof(src));
  EXPECT_EQ(ret, dst + sizeof(src));
  EXPECT_EQ(0, memcmp(dst, src, sizeof(src)));
}

TEST(eya_memory_std_copy, large_array_copy)
{
  static const size_t size = 1024 * 1024;
  static char src[size];
  static char dst[size];

  for (size_t i = 0; i < size; ++i)
  {
    src[i] = static_cast<char>(i & 0xFF);
  }
  memset(dst, 0, size);

  void *ret = eya_memory_std_copy(dst, src, size);
  EXPECT_EQ(ret, dst + size);
  EXPECT_EQ(0, memcmp(dst, src, size));
}

TEST(eya_memory_std_copy, one_byte_copy)
{
  static const char src[] = {42};
  char dst[1] = {0};

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
  static const char src[] = "Test data";
  char dst[sizeof(src)] = {0};

  void *ret = eya_memory_std_copy(dst, src, sizeof(src));
  EXPECT_EQ(ret, dst + sizeof(src));
}

TEST(eya_memory_std_copy, return_pointer_with_zero_length)
{
  static const char src[] = "Test data";
  char dst[sizeof(src)] = {0};

  void *ret = eya_memory_std_copy(dst, src, 0);
  EXPECT_EQ(ret, dst);
}

TEST(eya_memory_std_copy, copy_128_bytes)
{
  static const size_t size = 128;
  static char src[size];
  static char dst[size];

  for (size_t i = 0; i < size; ++i)
  {
    src[i] = static_cast<char>(i & 0xFF);
  }
  memset(dst, 0, size);

  void *ret = eya_memory_std_copy(dst, src, size);
  EXPECT_EQ(ret, dst + size);
  EXPECT_EQ(0, memcmp(dst, src, size));
}

TEST(eya_memory_std_copy, copy_256_bytes)
{
  static const size_t size = 256;
  static char src[size];
  static char dst[size];

  for (size_t i = 0; i < size; ++i)
  {
    src[i] = static_cast<char>(i & 0xFF);
  }
  memset(dst, 0, size);

  void *ret = eya_memory_std_copy(dst, src, size);
  EXPECT_EQ(ret, dst + size);
  EXPECT_EQ(0, memcmp(dst, src, size));
}

TEST(eya_memory_std_copy, copy_512_bytes)
{
  static const size_t size = 512;
  static char src[size];
  static char dst[size];

  for (size_t i = 0; i < size; ++i)
  {
    src[i] = static_cast<char>(i & 0xFF);
  }
  memset(dst, 0, size);

  void *ret = eya_memory_std_copy(dst, src, size);
  EXPECT_EQ(ret, dst + size);
  EXPECT_EQ(0, memcmp(dst, src, size));
}

TEST(eya_memory_std_rcopy, small_array_copy)
{
  static const char src[] = "Hello, world!";
  char dst[sizeof(src)] = {0};

  void *ret = eya_memory_std_rcopy(dst, src, sizeof(src));
  EXPECT_EQ(ret, dst);
  EXPECT_EQ(0, memcmp(dst, src, sizeof(src)));
}

TEST(eya_memory_std_rcopy, large_array_copy)
{
  static const size_t size = 1024 * 1024;
  static char src[size];
  static char dst[size];

  for (size_t i = 0; i < size; ++i)
  {
    src[i] = static_cast<char>(i & 0xFF);
  }
  memset(dst, 0, size);

  void *ret = eya_memory_std_rcopy(dst, src, size);
  EXPECT_EQ(ret, dst);
  EXPECT_EQ(0, memcmp(dst, src, size));
}

TEST(eya_memory_std_rcopy, one_byte_copy)
{
  static const char src[] = {42};
  char dst[1] = {0};

  void *ret = eya_memory_std_rcopy(dst, src, 1);
  EXPECT_EQ(ret, dst);
  EXPECT_EQ(dst[0], src[0]);
}

TEST(eya_memory_std_rcopy, zero_length_copy)
{
  static const char src[] = "test";
  char dst[sizeof(src)] = {0};

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
  static const char src[] = "Test data";
  char dst[sizeof(src)] = {0};

  void *ret = eya_memory_std_rcopy(dst, src, sizeof(src));
  EXPECT_EQ(ret, dst);
}

TEST(eya_memory_std_rcopy, return_pointer_with_zero_length)
{
  static const char src[] = "Test data";
  char dst[sizeof(src)] = {0};

  void *ret = eya_memory_std_rcopy(dst, src, 0);
  EXPECT_EQ(ret, dst);
}

TEST(eya_memory_std_rcopy, rcopy_128_bytes)
{
  static const size_t size = 128;
  static char src[size];
  static char dst[size];

  for (size_t i = 0; i < size; ++i)
  {
    src[i] = static_cast<char>(i & 0xFF);
  }
  memset(dst, 0, size);

  void *ret = eya_memory_std_rcopy(dst, src, size);
  EXPECT_EQ(ret, dst);
  EXPECT_EQ(0, memcmp(dst, src, size));
}

TEST(eya_memory_std_rcopy, rcopy_256_bytes)
{
  static const size_t size = 256;
  static char src[size];
  static char dst[size];

  for (size_t i = 0; i < size; ++i)
  {
    src[i] = static_cast<char>(i & 0xFF);
  }
  memset(dst, 0, size);

  void *ret = eya_memory_std_rcopy(dst, src, size);
  EXPECT_EQ(ret, dst);
  EXPECT_EQ(0, memcmp(dst, src, size));
}

TEST(eya_memory_std_rcopy, rcopy_512_bytes)
{
  static const size_t size = 512;
  static char src[size];
  static char dst[size];

  for (size_t i = 0; i < size; ++i)
  {
    src[i] = static_cast<char>(i & 0xFF);
  }
  memset(dst, 0, size);

  void *ret = eya_memory_std_rcopy(dst, src, size);
  EXPECT_EQ(ret, dst);
  EXPECT_EQ(0, memcmp(dst, src, size));
}