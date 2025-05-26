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

TEST(MemoryStdMoveTest, NonOverlappingRegions)
{
  const char src[] = "test data";
  char dst[sizeof(src)] = {0};

  void *result = eya_memory_std_move(dst, src, sizeof(src));

  // Verify data was copied correctly
  EXPECT_EQ(0, memcmp(dst, src, sizeof(src)));

  // Verify return value points to end of destination
  EXPECT_EQ(static_cast<char *>(result), dst + sizeof(src));
}

TEST(MemoryStdMoveTest, OverlappingRegionsSrcBeforeDst)
{
  char buffer[] = "abcdefghij";
  const size_t move_size = 5;
  const char *src = buffer;
  void *dst = buffer + 2; // Overlapping

  void *result = eya_memory_std_move(dst, src, move_size);

  // Verify expected result after move
  EXPECT_STREQ(buffer, "ababcdehij");

  // Verify return value
  EXPECT_EQ(static_cast<char *>(result), static_cast<char *>(dst) + move_size);
}

TEST(MemoryStdMoveTest, OverlappingRegionsDstBeforeSrc)
{
  char buffer[] = "abcdefghij";
  const size_t move_size = 5;
  void *dst = buffer;
  const char *src = buffer + 2; // Overlapping

  void *result = eya_memory_std_move(dst, src, move_size);

  // Verify expected result after move (should use reverse copy)
  EXPECT_STREQ(buffer, "cdefgfghij");

  // Verify return value
  EXPECT_EQ(static_cast<char *>(result), static_cast<char *>(dst) + move_size);
}

TEST(MemoryStdMoveTest, ZeroByteMove)
{
  char src[] = "source";
  char dst[] = "destination";

  void *result = eya_memory_std_move(dst, src, 0);

  // Verify nothing was changed
  EXPECT_STREQ(dst, "destination");
  EXPECT_EQ(result, dst);
}

TEST(MemoryStdMoveTest, NullPointers)
{
  // This test assumes the function handles null pointers gracefully
  // Note: In real code, we might want to add assertions for this case
  EXPECT_DEATH(eya_memory_std_move(nullptr, nullptr, 10), ".*");
}

TEST(MemoryStdMoveTest, FullOverlapSamePointer)
{
  char buffer[] = "test data";
  const char *original = "test data";

  void *result = eya_memory_std_move(buffer, buffer, sizeof(buffer));

  // Should remain unchanged
  EXPECT_STREQ(buffer, original);
  EXPECT_EQ(static_cast<char *>(result), buffer + sizeof(buffer));
}

TEST(MemoryStdMoveTest, PartialOverlapSmallBuffer)
{
  char buffer[5] = {1, 2, 3, 4, 5};
  void *result = eya_memory_std_move(buffer + 1, buffer, 3);

  // Expected result: [1, 1, 2, 3, 5]
  EXPECT_EQ(buffer[0], 1);
  EXPECT_EQ(buffer[1], 1);
  EXPECT_EQ(buffer[2], 2);
  EXPECT_EQ(buffer[3], 3);
  EXPECT_EQ(buffer[4], 5);
  EXPECT_EQ(static_cast<char *>(result), buffer + 1 + 3);
}