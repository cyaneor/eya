#include <eya/memory_view.h>
#include <gtest/gtest.h>

TEST(eya_memory_view_unpack, unpack_with_only_begin) {
  eya_memory_view_t view = {(void *)0x1000, (void *)0x2000};
  const void *begin = nullptr;

  eya_memory_view_unpack(&view, &begin, nullptr);
  EXPECT_EQ(begin, (void *)0x1000);
}

TEST(eya_memory_view_unpack, unpack_with_only_end) {
  eya_memory_view_t view = {(void *)0x1000, (void *)0x2000};
  const void *end = nullptr;

  eya_memory_view_unpack(&view, nullptr, &end);
  EXPECT_EQ(end, (void *)0x2000);
}

TEST(eya_memory_view_unpack, unpack_with_null_pointers) {
  eya_memory_view_t view = {(void *)0x1000, (void *)0x2000};
  eya_memory_view_unpack(&view, nullptr, nullptr);
  EXPECT_EQ(view.begin, (void *)0x1000);
  EXPECT_EQ(view.end, (void *)0x2000);
}

TEST(eya_memory_view_unpack, unpack_with_null_self) {
  EXPECT_DEATH(eya_memory_view_unpack(nullptr, nullptr, nullptr), ".*");
}

TEST(eya_memory_view_get_begin, valid_self) {
  eya_memory_view_t view = {(void *)0x1000, (void *)0x2000};

  const void *result = eya_memory_view_get_begin(&view);
  EXPECT_EQ(result, (void *)0x1000);
}

TEST(eya_memory_view_get_begin, null_self) {
  EXPECT_DEATH(eya_memory_view_get_begin(nullptr), ".*");
}

TEST(eya_memory_view_get_end, valid_self) {
  eya_memory_view_t view = {(void *)0x1000, (void *)0x2000};

  const void *result = eya_memory_view_get_end(&view);
  EXPECT_EQ(result, (void *)0x2000);
}

TEST(eya_memory_view_get_end, null_self) {
  EXPECT_DEATH(eya_memory_view_get_end(nullptr), ".*");
}

TEST(eya_memory_view_get_state, uninitialized) {
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_EQ(EYA_MEMORY_VIEW_UNINITIALIZED, eya_memory_view_get_state(&view));
}

TEST(eya_memory_view_get_state, empty) {
  int dummy;
  eya_memory_view_t view = {&dummy, &dummy};
  EXPECT_EQ(EYA_MEMORY_VIEW_EMPTY, eya_memory_view_get_state(&view));
}

TEST(eya_memory_view_get_state, invalid_null_begin) {
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  EXPECT_EQ(EYA_MEMORY_VIEW_INVALID_NULL_BEGIN,
            eya_memory_view_get_state(&view));
}

TEST(eya_memory_view_get_state, invalid_null_end) {
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_EQ(EYA_MEMORY_VIEW_INVALID_NULL_END, eya_memory_view_get_state(&view));
}

TEST(eya_memory_view_get_state, has_data) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[0], &data[1]};
  EXPECT_EQ(EYA_MEMORY_VIEW_HAS_DATA, eya_memory_view_get_state(&view));
}

TEST(eya_memory_view_get_state, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_EQ(EYA_MEMORY_VIEW_INVALID_DANGLING, eya_memory_view_get_state(&view));
}

TEST(eya_memory_view_is_uninit, null_self) {
  EXPECT_DEATH(eya_memory_view_is_uninit(nullptr), ".*");
}

TEST(eya_memory_view_is_uninit, uninitialized) {
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_TRUE(eya_memory_view_is_uninit(&view));
}

TEST(eya_memory_view_is_uninit, empty) {
  int dummy;
  eya_memory_view_t view = {&dummy, &dummy};
  EXPECT_FALSE(eya_memory_view_is_uninit(&view));
}

TEST(eya_memory_view_is_uninit, invalid_null_begin) {
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  EXPECT_FALSE(eya_memory_view_is_uninit(&view));
}

TEST(eya_memory_view_is_uninit, invalid_null_end) {
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_FALSE(eya_memory_view_is_uninit(&view));
}

TEST(eya_memory_view_is_uninit, has_data) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[0], &data[1]};
  EXPECT_FALSE(eya_memory_view_is_uninit(&view));
}

TEST(eya_memory_view_is_uninit, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_FALSE(eya_memory_view_is_uninit(&view));
}

TEST(eya_memory_view_is_empty, null_self) {
  EXPECT_DEATH(eya_memory_view_is_empty(nullptr), ".*");
}

TEST(eya_memory_view_is_empty, uninitialized) {
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_FALSE(eya_memory_view_is_empty(&view));
}

TEST(eya_memory_view_is_empty, empty) {
  int dummy;
  eya_memory_view_t view = {&dummy, &dummy};
  EXPECT_TRUE(eya_memory_view_is_empty(&view));
}

TEST(eya_memory_view_is_empty, invalid_null_begin) {
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  EXPECT_FALSE(eya_memory_view_is_empty(&view));
}

TEST(eya_memory_view_is_empty, invalid_null_end) {
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_FALSE(eya_memory_view_is_empty(&view));
}

TEST(eya_memory_view_is_empty, has_data) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[0], &data[1]};
  EXPECT_FALSE(eya_memory_view_is_empty(&view));
}

TEST(eya_memory_view_is_empty, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_FALSE(eya_memory_view_is_empty(&view));
}

TEST(eya_memory_view_has_data, null_self) {
  EXPECT_DEATH(eya_memory_view_has_data(nullptr), ".*");
}

TEST(eya_memory_view_has_data, uninitialized) {
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_FALSE(eya_memory_view_has_data(&view));
}

TEST(eya_memory_view_has_data, empty) {
  int dummy;
  eya_memory_view_t view = {&dummy, &dummy};
  EXPECT_FALSE(eya_memory_view_has_data(&view));
}

TEST(eya_memory_view_has_data, invalid_null_begin) {
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  EXPECT_FALSE(eya_memory_view_has_data(&view));
}

TEST(eya_memory_view_has_data, invalid_null_end) {
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_FALSE(eya_memory_view_has_data(&view));
}

TEST(eya_memory_view_has_data, has_data_single_byte) {
  char byte = 'A';
  eya_memory_view_t view = {&byte, &byte + 1};
  EXPECT_TRUE(eya_memory_view_has_data(&view));
}

TEST(eya_memory_view_has_data, has_data_multiple_bytes) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_TRUE(eya_memory_view_has_data(&view));
}

TEST(eya_memory_view_has_data, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_FALSE(eya_memory_view_has_data(&view));
}

TEST(eya_memory_view_is_invalid, uninitialized) {
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_TRUE(eya_memory_view_is_invalid(&view));
}

TEST(eya_memory_view_is_invalid, invalid_null_begin) {
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  EXPECT_TRUE(eya_memory_view_is_invalid(&view));
}

TEST(eya_memory_view_is_invalid, invalid_null_end) {
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_TRUE(eya_memory_view_is_invalid(&view));
}

TEST(eya_memory_view_is_invalid, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_TRUE(eya_memory_view_is_invalid(&view));
}

TEST(eya_memory_view_is_invalid, valid_single_byte) {
  char byte = 'A';
  eya_memory_view_t view = {&byte, &byte + 1};
  EXPECT_FALSE(eya_memory_view_is_invalid(&view));
}

TEST(eya_memory_view_is_invalid, valid_multiple_bytes) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_FALSE(eya_memory_view_is_invalid(&view));
}

TEST(eya_memory_view_is_valid, uninitialized) {
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_FALSE(eya_memory_view_is_valid(&view));
}

TEST(eya_memory_view_is_valid, invalid_null_begin) {
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  EXPECT_FALSE(eya_memory_view_is_valid(&view));
}

TEST(eya_memory_view_is_valid, invalid_null_end) {
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_FALSE(eya_memory_view_is_valid(&view));
}

TEST(eya_memory_view_is_valid, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_FALSE(eya_memory_view_is_valid(&view));
}

TEST(eya_memory_view_is_valid, valid_single_byte) {
  char byte = 'A';
  eya_memory_view_t view = {&byte, &byte + 1};
  EXPECT_TRUE(eya_memory_view_is_valid(&view));
}

TEST(eya_memory_view_is_valid, valid_multiple_bytes) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_TRUE(eya_memory_view_is_valid(&view));
}

TEST(eya_memory_view_diff, uninitialized) {
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_diff(&view), ".*");
}

TEST(eya_memory_view_diff, invalid_null_begin) {
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  EXPECT_DEATH(eya_memory_view_diff(&view), ".*");
}

TEST(eya_memory_view_diff, invalid_null_end) {
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_DEATH(eya_memory_view_diff(&view), ".*");
}

TEST(eya_memory_view_diff, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_DEATH(eya_memory_view_diff(&view), ".*");
}

TEST(eya_memory_view_diff, valid_single_byte) {
  char byte = 'A';
  eya_memory_view_t view = {&byte, &byte + 1};
  EXPECT_EQ(eya_memory_view_diff(&view), 1);
}

TEST(eya_memory_view_diff, valid_multiple_bytes) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_diff(&view), 4 * sizeof(int));
}

TEST(eya_memory_view_get_size, uninitialized) {
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_get_size(&view), ".*");
}

TEST(eya_memory_view_get_size, invalid_null_begin) {
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  EXPECT_DEATH(eya_memory_view_get_size(&view), ".*");
}

TEST(eya_memory_view_get_size, invalid_null_end) {
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_DEATH(eya_memory_view_get_size(&view), ".*");
}

TEST(eya_memory_view_get_size, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_DEATH(eya_memory_view_get_size(&view), ".*");
}

TEST(eya_memory_view_get_size, valid_single_byte) {
  char byte = 'A';
  eya_memory_view_t view = {&byte, &byte + 1};
  EXPECT_EQ(eya_memory_view_get_size(&view), 1);
}

TEST(eya_memory_view_get_size, valid_multiple_bytes) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_get_size(&view), 4 * sizeof(int));
}

TEST(eya_memory_view_unpack_v, uninitialized) {
  eya_memory_view_t view = {nullptr, nullptr};
  const void *begin, *end;
  EXPECT_DEATH(eya_memory_view_unpack_v(&view, &begin, &end), ".*");
}

TEST(eya_memory_view_unpack_v, invalid_null_begin) {
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  const void *begin, *end;
  EXPECT_DEATH(eya_memory_view_unpack_v(&view, &begin, &end), ".*");
}

TEST(eya_memory_view_unpack_v, invalid_null_end) {
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  const void *begin, *end;
  EXPECT_DEATH(eya_memory_view_unpack_v(&view, &begin, &end), ".*");
}

TEST(eya_memory_view_unpack_v, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  const void *begin, *end;
  EXPECT_DEATH(eya_memory_view_unpack_v(&view, &begin, &end), ".*");
}

TEST(eya_memory_view_unpack_v, valid_single_byte) {
  char byte = 'A';
  eya_memory_view_t view = {&byte, &byte + 1};
  const void *begin, *end;
  eya_memory_view_unpack_v(&view, &begin, &end);
  EXPECT_EQ(begin, &byte);
  EXPECT_EQ(end, &byte + 1);
}

TEST(eya_memory_view_unpack_v, valid_multiple_bytes) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  const void *begin, *end;
  eya_memory_view_unpack_v(&view, &begin, &end);
  EXPECT_EQ(begin, &data[0]);
  EXPECT_EQ(end, &data[4]);
}

TEST(eya_memory_view_contains_ptr, uninitialized) {
  eya_memory_view_t view = {nullptr, nullptr};
  const void *ptr = nullptr;
  EXPECT_DEATH(eya_memory_view_contains_ptr(&view, ptr), ".*");
}

TEST(eya_memory_view_contains_ptr, invalid_null_begin) {
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  const void *ptr = &dummy;
  EXPECT_DEATH(eya_memory_view_contains_ptr(&view, ptr), ".*");
}

TEST(eya_memory_view_contains_ptr, invalid_null_end) {
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  const void *ptr = &dummy;
  EXPECT_DEATH(eya_memory_view_contains_ptr(&view, ptr), ".*");
}

TEST(eya_memory_view_contains_ptr, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  const void *ptr = &data[0];
  EXPECT_DEATH(eya_memory_view_contains_ptr(&view, ptr), ".*");
}

TEST(eya_memory_view_contains_ptr, valid_single_byte_contains) {
  char byte = 'A';
  eya_memory_view_t view = {&byte, &byte + 1};
  const void *ptr = &byte;
  EXPECT_TRUE(eya_memory_view_contains_ptr(&view, ptr));
}

TEST(eya_memory_view_contains_ptr, valid_single_byte_not_contains_end) {
  char byte = 'A';
  eya_memory_view_t view = {&byte, &byte + 1};
  const void *ptr = &byte + 1;
  EXPECT_FALSE(eya_memory_view_contains_ptr(&view, ptr));
}

TEST(eya_memory_view_contains_ptr, valid_multiple_bytes_contains_middle) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  const void *ptr = &data[2];
  EXPECT_TRUE(eya_memory_view_contains_ptr(&view, ptr));
}

TEST(eya_memory_view_contains_ptr, valid_multiple_bytes_not_contains_before) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  const void *ptr = &data[0] - 1;
  EXPECT_FALSE(eya_memory_view_contains_ptr(&view, ptr));
}

TEST(eya_memory_view_contains_ptr, valid_multiple_bytes_not_contains_after) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  const void *ptr = &data[4];
  EXPECT_FALSE(eya_memory_view_contains_ptr(&view, ptr));
}

TEST(eya_memory_view_contains, uninitialized_self) {
  eya_memory_view_t self = {nullptr, nullptr};
  char byte = 'A';
  eya_memory_view_t other = {&byte, &byte + 1};
  EXPECT_DEATH(eya_memory_view_contains(&self, &other), ".*");
}

TEST(eya_memory_view_contains, uninitialized_other) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t self = {&data[0], &data[4]};
  eya_memory_view_t other = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_contains(&self, &other), ".*");
}

TEST(eya_memory_view_contains, invalid_null_begin_self) {
  int dummy;
  eya_memory_view_t self = {nullptr, &dummy};
  eya_memory_view_t other = {&dummy, &dummy + 1};
  EXPECT_DEATH(eya_memory_view_contains(&self, &other), ".*");
}

TEST(eya_memory_view_contains, invalid_null_end_other) {
  int dummy;
  eya_memory_view_t self = {&dummy, &dummy + 1};
  eya_memory_view_t other = {&dummy, nullptr};
  EXPECT_DEATH(eya_memory_view_contains(&self, &other), ".*");
}

TEST(eya_memory_view_contains, valid_contains_exact) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t self = {&data[0], &data[4]};
  eya_memory_view_t other = {&data[0], &data[4]};
  EXPECT_FALSE(eya_memory_view_contains(&self, &other));
}

TEST(eya_memory_view_contains, valid_contains_subset) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t self = {&data[0], &data[4]};
  eya_memory_view_t other = {&data[1], &data[3]};
  EXPECT_TRUE(eya_memory_view_contains(&self, &other));
}

TEST(eya_memory_view_contains, valid_not_contains_before) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t self = {&data[1], &data[4]};
  eya_memory_view_t other = {&data[0], &data[2]};
  EXPECT_FALSE(eya_memory_view_contains(&self, &other));
}

TEST(eya_memory_view_contains, valid_not_contains_after) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t self = {&data[0], &data[3]};
  eya_memory_view_t other = {&data[2], &data[4]};
  EXPECT_FALSE(eya_memory_view_contains(&self, &other));
}

TEST(eya_memory_view_contains, valid_single_byte_contains) {
  char byte = 'A';
  eya_memory_view_t self = {&byte, &byte + 1};
  eya_memory_view_t other = {&byte, &byte + 1};
  EXPECT_FALSE(eya_memory_view_contains(&self, &other));
}

TEST(eya_memory_view_contains, valid_empty_other) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t self = {&data[0], &data[4]};
  eya_memory_view_t other = {&data[2], &data[2]};
  EXPECT_TRUE(eya_memory_view_contains(&self, &other));
}

TEST(eya_memory_view_is_valid_offset, invalid_uninitialized) {
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_is_valid_offset(&view, 0), ".*");
}

TEST(eya_memory_view_is_valid_offset, invalid_null_begin) {
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  EXPECT_DEATH(eya_memory_view_is_valid_offset(&view, 0), ".*");
}

TEST(eya_memory_view_is_valid_offset, invalid_null_end) {
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_DEATH(eya_memory_view_is_valid_offset(&view, 0), ".*");
}

TEST(eya_memory_view_is_valid_offset, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_DEATH(eya_memory_view_is_valid_offset(&view, 0), ".*");
}

TEST(eya_memory_view_is_valid_offset, valid_single_byte) {
  char byte = 'A';
  eya_memory_view_t view = {&byte, &byte + 1};

  EXPECT_TRUE(eya_memory_view_is_valid_offset(&view, 0));
  EXPECT_FALSE(eya_memory_view_is_valid_offset(&view, 1));
  EXPECT_FALSE(eya_memory_view_is_valid_offset(&view, 2));
}

TEST(eya_memory_view_is_valid_offset, valid_multiple_bytes) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  const size_t size = 4 * sizeof(int);

  EXPECT_TRUE(eya_memory_view_is_valid_offset(&view, 0));
  EXPECT_TRUE(eya_memory_view_is_valid_offset(&view, size - 1));

  EXPECT_FALSE(eya_memory_view_is_valid_offset(&view, size));
  EXPECT_FALSE(eya_memory_view_is_valid_offset(&view, size + 1));
  EXPECT_FALSE(eya_memory_view_is_valid_offset(&view, size + 10));
}

TEST(eya_memory_view_is_valid_offset, valid_empty_view) {
  int dummy;
  eya_memory_view_t view = {&dummy, &dummy};

  EXPECT_FALSE(eya_memory_view_is_valid_offset(&view, 0));
  EXPECT_FALSE(eya_memory_view_is_valid_offset(&view, 1));
}

TEST(eya_memory_view_at_begin, uninitialized) {
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_at_begin(&view, 0), ".*");
}

TEST(eya_memory_view_at_begin, invalid_null_begin) {
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  EXPECT_DEATH(eya_memory_view_at_begin(&view, 0), ".*");
}

TEST(eya_memory_view_at_begin, invalid_null_end) {
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_DEATH(eya_memory_view_at_begin(&view, 0), ".*");
}

TEST(eya_memory_view_at_begin, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_DEATH(eya_memory_view_at_begin(&view, 0), ".*");
}

TEST(eya_memory_view_at_begin, valid_zero_offset) {
  char byte = 'A';
  eya_memory_view_t view = {&byte, &byte + 1};
  EXPECT_EQ(eya_memory_view_at_begin(&view, 0), &byte);
}

TEST(eya_memory_view_at_begin, valid_non_zero_offset) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_at_begin(&view, sizeof(int)), &data[1]);
}

TEST(eya_memory_view_at_begin, offset_at_end) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_DEATH(eya_memory_view_at_begin(&view, 4 * sizeof(int)), ".*");
}

TEST(eya_memory_view_at_begin, offset_beyond_end) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_DEATH(eya_memory_view_at_begin(&view, 4 * sizeof(int) + 1), ".*");
}

TEST(eya_memory_view_at_end, uninitialized) {
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_at_end(&view, 0), ".*");
}

TEST(eya_memory_view_at_end, invalid_null_begin) {
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  EXPECT_DEATH(eya_memory_view_at_end(&view, 0), ".*");
}

TEST(eya_memory_view_at_end, invalid_null_end) {
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_DEATH(eya_memory_view_at_end(&view, 0), ".*");
}

TEST(eya_memory_view_at_end, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_DEATH(eya_memory_view_at_end(&view, 0), ".*");
}

TEST(eya_memory_view_at_end, valid_zero_offset_single_byte) {
  char byte = 'A';
  eya_memory_view_t view = {&byte, &byte + 1};
  EXPECT_EQ(eya_memory_view_at_end(&view, 0), &byte);
}

TEST(eya_memory_view_at_end, valid_non_zero_offset) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_at_end(&view, 4),
            (void *)((char *)&data[0] + (4 * sizeof(int) - 5)));
}

TEST(eya_memory_view_at_end, offset_at_begin) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_at_end(&view, 4 * sizeof(int) - 1), &data[0]);
}

TEST(eya_memory_view_at_end, offset_beyond_size) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_DEATH(eya_memory_view_at_end(&view, 4 * sizeof(int)), ".*");
}

TEST(eya_memory_view_at_first, uninitialized) {
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_at_first(&view), ".*");
}

TEST(eya_memory_view_at_first, invalid_null_begin) {
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  EXPECT_DEATH(eya_memory_view_at_first(&view), ".*");
}

TEST(eya_memory_view_at_first, invalid_null_end) {
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_DEATH(eya_memory_view_at_first(&view), ".*");
}

TEST(eya_memory_view_at_first, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_DEATH(eya_memory_view_at_first(&view), ".*");
}

TEST(eya_memory_view_at_first, empty_view) {
  int data[1];
  eya_memory_view_t view = {&data[0], &data[0]};
  EXPECT_DEATH(eya_memory_view_at_first(&view), ".*");
}

TEST(eya_memory_view_at_first, valid_single_byte) {
  char byte = 'A';
  eya_memory_view_t view = {&byte, &byte + 1};
  EXPECT_EQ(eya_memory_view_at_first(&view), &byte);
}

TEST(eya_memory_view_at_first, valid_array) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_at_first(&view), &data[0]);
}

TEST(eya_memory_view_at_last, uninitialized) {
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_at_last(&view), ".*");
}

TEST(eya_memory_view_at_last, invalid_null_begin) {
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  EXPECT_DEATH(eya_memory_view_at_last(&view), ".*");
}

TEST(eya_memory_view_at_last, invalid_null_end) {
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_DEATH(eya_memory_view_at_last(&view), ".*");
}

TEST(eya_memory_view_at_last, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_DEATH(eya_memory_view_at_last(&view), ".*");
}

TEST(eya_memory_view_at_last, empty_view) {
  int data[1];
  eya_memory_view_t view = {&data[0], &data[0]};
  EXPECT_DEATH(eya_memory_view_at_last(&view), ".*");
}

TEST(eya_memory_view_at_last, valid_single_byte) {
  char byte = 'A';
  eya_memory_view_t view = {&byte, &byte + 1};
  EXPECT_EQ(eya_memory_view_at_last(&view), &byte);
}

TEST(eya_memory_view_at_last, valid_byte_array) {
  char data[4] = {'A', 'B', 'C', 'D'};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_at_last(&view), &data[3]);
}

TEST(eya_memory_view_at_last, valid_int_array) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};

  const char *last_byte =
      reinterpret_cast<const char *>(&data[3]) + sizeof(int) - 1;

  EXPECT_EQ(eya_memory_view_at_last(&view), last_byte);
}

TEST(eya_memory_view_is_equal_begin_to, valid_equal) {
  int data[2];
  eya_memory_view_t view = {&data[0], &data[1]};
  EXPECT_TRUE(eya_memory_view_is_equal_begin_to(&view, &data[0]));
}

TEST(eya_memory_view_is_equal_begin_to, valid_not_equal) {
  int data[2];
  int other;
  eya_memory_view_t view = {&data[0], &data[1]};
  EXPECT_FALSE(eya_memory_view_is_equal_begin_to(&view, &other));
}

TEST(eya_memory_view_is_equal_end_to, valid_equal) {
  int data[2];
  eya_memory_view_t view = {&data[0], &data[1]};
  EXPECT_TRUE(eya_memory_view_is_equal_end_to(&view, &data[1]));
}

TEST(eya_memory_view_is_equal_end_to, valid_not_equal) {
  int data[2];
  int other;
  eya_memory_view_t view = {&data[0], &data[1]};
  EXPECT_FALSE(eya_memory_view_is_equal_end_to(&view, &other));
}

TEST(eya_memory_view_is_equal_begin, same_view) {
  int data[2];
  eya_memory_view_t view1 = {&data[0], &data[1]};
  eya_memory_view_t view2 = {&data[0], &data[1]};
  EXPECT_TRUE(eya_memory_view_is_equal_begin(&view1, &view2));
}

TEST(eya_memory_view_is_equal_begin, different_begin) {
  int data[3];
  eya_memory_view_t view1 = {&data[0], &data[2]};
  eya_memory_view_t view2 = {&data[1], &data[2]};
  EXPECT_FALSE(eya_memory_view_is_equal_begin(&view1, &view2));
}

TEST(eya_memory_view_is_equal_begin, same_begin_different_end) {
  int data[3];
  eya_memory_view_t view1 = {&data[0], &data[1]};
  eya_memory_view_t view2 = {&data[0], &data[2]};
  EXPECT_TRUE(eya_memory_view_is_equal_begin(&view1, &view2));
}

TEST(eya_memory_view_is_equal_end, same_view) {
  int data[2];
  eya_memory_view_t view1 = {&data[0], &data[1]};
  eya_memory_view_t view2 = {&data[0], &data[1]};
  EXPECT_TRUE(eya_memory_view_is_equal_end(&view1, &view2));
}

TEST(eya_memory_view_is_equal_end, different_end) {
  int data[3];
  eya_memory_view_t view1 = {&data[0], &data[1]};
  eya_memory_view_t view2 = {&data[0], &data[2]};
  EXPECT_FALSE(eya_memory_view_is_equal_end(&view1, &view2));
}

TEST(eya_memory_view_is_equal_end, same_end_different_begin) {
  int data[3];
  eya_memory_view_t view1 = {&data[0], &data[2]};
  eya_memory_view_t view2 = {&data[1], &data[2]};
  EXPECT_TRUE(eya_memory_view_is_equal_end(&view1, &view2));
}

TEST(eya_memory_view_is_equal, identical_views) {
  int data[2];
  eya_memory_view_t view1 = {&data[0], &data[1]};
  eya_memory_view_t view2 = {&data[0], &data[1]};
  EXPECT_TRUE(eya_memory_view_is_equal(&view1, &view2));
}

TEST(eya_memory_view_is_equal, different_begin) {
  int data[3];
  eya_memory_view_t view1 = {&data[0], &data[2]};
  eya_memory_view_t view2 = {&data[1], &data[2]};
  EXPECT_FALSE(eya_memory_view_is_equal(&view1, &view2));
}

TEST(eya_memory_view_is_equal, different_end) {
  int data[3];
  eya_memory_view_t view1 = {&data[0], &data[1]};
  eya_memory_view_t view2 = {&data[0], &data[2]};
  EXPECT_FALSE(eya_memory_view_is_equal(&view1, &view2));
}

TEST(eya_memory_view_is_equal, completely_different) {
  int data1[2];
  int data2[2];
  eya_memory_view_t view1 = {&data1[0], &data1[1]};
  eya_memory_view_t view2 = {&data2[0], &data2[1]};
  EXPECT_FALSE(eya_memory_view_is_equal(&view1, &view2));
}

TEST(eya_memory_view_is_equal, empty_views) {
  int data;
  eya_memory_view_t view1 = {&data, &data};
  eya_memory_view_t view2 = {&data, &data};
  EXPECT_TRUE(eya_memory_view_is_equal(&view1, &view2));
}

TEST(eya_memory_view_is_equal, different_empty_views) {
  int data1;
  int data2;
  eya_memory_view_t view1 = {&data1, &data1};
  eya_memory_view_t view2 = {&data2, &data2};
  EXPECT_FALSE(eya_memory_view_is_equal(&view1, &view2));
}

TEST(eya_memory_view_is_aligned, invalid_align_zero) {
  int data;
  eya_memory_view_t view = {&data, &data + 1};
  EXPECT_DEATH(eya_memory_view_is_aligned(&view, 0), ".*");
}

TEST(eya_memory_view_is_aligned, invalid_align_not_power_of_two) {
  int data;
  eya_memory_view_t view = {&data, &data + 1};
  EXPECT_DEATH(eya_memory_view_is_aligned(&view, 3), ".*");
  EXPECT_DEATH(eya_memory_view_is_aligned(&view, 5), ".*");
  EXPECT_DEATH(eya_memory_view_is_aligned(&view, 6), ".*");
  EXPECT_DEATH(eya_memory_view_is_aligned(&view, 7), ".*");
  EXPECT_DEATH(eya_memory_view_is_aligned(&view, 9), ".*");
}

TEST(eya_memory_view_is_aligned, null_view_pointer) {
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_is_aligned(&view, 1), ".*");
}

TEST(eya_memory_view_find_range, uninitialized_view) {
  int data[1] = {1};
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_find_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_view_find_range, invalid_null_begin) {
  int data[1] = {1};
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  EXPECT_DEATH(eya_memory_view_find_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_view_find_range, invalid_null_end) {
  int data[1] = {1};
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_DEATH(eya_memory_view_find_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_view_find_range, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_DEATH(eya_memory_view_find_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_view_find_range, empty_view) {
  int data[1] = {1};
  eya_memory_view_t view = {&data[0], &data[0]};
  EXPECT_EQ(eya_memory_view_find_range(&view, &data[0], &data[1]), nullptr);
}

TEST(eya_memory_view_find_range, empty_search_range) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_find_range(&view, &data[0], &data[0]), nullptr);
}

TEST(eya_memory_view_find_range, not_found) {
  int data[4] = {1, 2, 3, 4};
  int search[1] = {5};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_find_range(&view, &search[0], &search[1]), nullptr);
}

TEST(eya_memory_view_find_range, found_at_begin) {
  int data[4] = {1, 2, 3, 4};
  int search[1] = {1};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_find_range(&view, &search[0], &search[1]),
            &data[0]);
}

TEST(eya_memory_view_find_range, found_at_middle) {
  int data[4] = {1, 2, 3, 4};
  int search[1] = {3};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_find_range(&view, &search[0], &search[1]),
            &data[2]);
}

TEST(eya_memory_view_find_range, found_multibyte) {
  char data[] = "hello world";
  char search[] = "world";
  eya_memory_view_t view = {&data[0], &data[sizeof(data) - 1]};
  EXPECT_EQ(eya_memory_view_find_range(&view, &search[0],
                                       &search[sizeof(search) - 1]),
            &data[6]);
}

TEST(eya_memory_view_find, uninitialized_other) {
  int data[1] = {1};
  eya_memory_view_t view = {&data[0], &data[1]};
  eya_memory_view_t other = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_find(&view, &other), ".*");
}

TEST(eya_memory_view_find, empty_other) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  eya_memory_view_t other = {&data[0], &data[0]};
  EXPECT_EQ(eya_memory_view_find(&view, &other), nullptr);
}

TEST(eya_memory_view_find, found_subview) {
  int data[4] = {1, 2, 3, 4};
  int subdata[2] = {2, 3};
  eya_memory_view_t view = {&data[0], &data[4]};
  eya_memory_view_t other = {&subdata[0], &subdata[2]};
  EXPECT_EQ(eya_memory_view_find(&view, &other), &data[1]);
}

TEST(eya_memory_view_rfind_range, uninitialized_view) {
  int data[1] = {1};
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_rfind_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_view_rfind_range, invalid_null_begin) {
  int data[1] = {1};
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  EXPECT_DEATH(eya_memory_view_rfind_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_view_rfind_range, invalid_null_end) {
  int data[1] = {1};
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_DEATH(eya_memory_view_rfind_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_view_rfind_range, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_DEATH(eya_memory_view_rfind_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_view_rfind_range, empty_view) {
  int data[1] = {1};
  eya_memory_view_t view = {&data[0], &data[0]};
  EXPECT_EQ(eya_memory_view_rfind_range(&view, &data[0], &data[1]), nullptr);
}

TEST(eya_memory_view_rfind_range, empty_search_range) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_rfind_range(&view, &data[0], &data[0]), nullptr);
}

TEST(eya_memory_view_rfind_range, not_found) {
  int data[4] = {1, 2, 3, 4};
  int search[1] = {5};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_rfind_range(&view, &search[0], &search[1]),
            nullptr);
}

TEST(eya_memory_view_rfind_range, found_at_begin) {
  int data[4] = {1, 2, 1, 4};
  int search[1] = {1};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_rfind_range(&view, &search[0], &search[1]),
            &data[2]);
}

TEST(eya_memory_view_rfind_range, found_at_end) {
  int data[4] = {1, 2, 3, 4};
  int search[1] = {4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_rfind_range(&view, &search[0], &search[1]),
            &data[3]);
}

TEST(eya_memory_view_rfind_range, found_multibyte) {
  char data[] = "hello world world";
  char search[] = "world";
  eya_memory_view_t view = {&data[0], &data[sizeof(data) - 1]};
  EXPECT_EQ(eya_memory_view_rfind_range(&view, &search[0],
                                        &search[sizeof(search) - 1]),
            &data[12]);
}

TEST(eya_memory_view_rfind, uninitialized_other) {
  int data[1] = {1};
  eya_memory_view_t view = {&data[0], &data[1]};
  eya_memory_view_t other = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_rfind(&view, &other), ".*");
}

TEST(eya_memory_view_rfind, empty_other) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  eya_memory_view_t other = {&data[0], &data[0]};
  EXPECT_EQ(eya_memory_view_rfind(&view, &other), nullptr);
}

TEST(eya_memory_view_rfind, found_last_subview) {
  int data[6] = {1, 2, 3, 2, 3, 4};
  int subdata[2] = {2, 3};
  eya_memory_view_t view = {&data[0], &data[6]};
  eya_memory_view_t other = {&subdata[0], &subdata[2]};
  EXPECT_EQ(eya_memory_view_rfind(&view, &other), &data[3]);
}

TEST(eya_memory_view_rfind, identical_views) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_rfind(&view, &view), &data[0]);
}

TEST(eya_memory_view_compare_range, invalid_null_end) {
  int data[1] = {1};
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_DEATH(eya_memory_view_compare_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_view_compare_range, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_DEATH(eya_memory_view_compare_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_view_compare_range, empty_view) {
  int data[1] = {1};
  eya_memory_view_t view = {&data[0], &data[0]};
  EXPECT_EQ(eya_memory_view_compare_range(&view, &data[0], &data[1]), nullptr);
}

TEST(eya_memory_view_compare_range, empty_compare_range) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_compare_range(&view, &data[0], &data[0]), nullptr);
}

TEST(eya_memory_view_compare_range, identical_content) {
  int data[4] = {1, 2, 3, 4};
  int compare[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_compare_range(&view, &compare[0], &compare[4]),
            nullptr);
}

TEST(eya_memory_view_compare_range, different_content) {
  int data[4] = {1, 2, 3, 4};
  int compare[4] = {1, 2, 0, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_compare_range(&view, &compare[0], &compare[4]),
            &data[2]);
}

TEST(eya_memory_view_compare_range, multibyte_string) {
  char data[] = "hello world";
  char compare[] = "hello there";
  eya_memory_view_t view = {&data[0], &data[sizeof(data) - 1]};
  EXPECT_EQ(eya_memory_view_compare_range(&view, &compare[0],
                                          &compare[sizeof(compare) - 1]),
            &data[6]);
}

TEST(eya_memory_view_compare, uninitialized_other) {
  int data[1] = {1};
  eya_memory_view_t view = {&data[0], &data[1]};
  eya_memory_view_t other = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_compare(&view, &other), ".*");
}

TEST(eya_memory_view_compare, empty_other) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  eya_memory_view_t other = {&data[0], &data[0]};
  EXPECT_EQ(eya_memory_view_compare(&view, &other), nullptr);
}

TEST(eya_memory_view_compare, identical_views) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_compare(&view, &view), nullptr);
}

TEST(eya_memory_view_compare, different_views) {
  int data[4] = {1, 2, 3, 4};
  int other_data[4] = {1, 2, 0, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  eya_memory_view_t other = {&other_data[0], &other_data[4]};
  EXPECT_EQ(eya_memory_view_compare(&view, &other), &data[2]);
}

TEST(eya_memory_view_rcompare_range, invalid_null_end) {
  int data[1] = {1};
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_DEATH(eya_memory_view_rcompare_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_view_rcompare_range, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_DEATH(eya_memory_view_rcompare_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_view_rcompare_range, empty_view) {
  int data[1] = {1};
  eya_memory_view_t view = {&data[0], &data[0]};
  EXPECT_EQ(eya_memory_view_rcompare_range(&view, &data[0], &data[1]), nullptr);
}

TEST(eya_memory_view_rcompare_range, empty_compare_range) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_rcompare_range(&view, &data[0], &data[0]), nullptr);
}

TEST(eya_memory_view_rcompare_range, identical_content) {
  int data[4] = {1, 2, 3, 4};
  int compare[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_rcompare_range(&view, &compare[0], &compare[4]),
            nullptr);
}

TEST(eya_memory_view_rcompare_range, different_content) {
  int data[4] = {1, 2, 3, 4};
  int compare[4] = {1, 2, 3, 0};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_rcompare_range(&view, &compare[0], &compare[4]),
            &data[3]);
}

TEST(eya_memory_view_rcompare_range, multibyte_string) {
  char data[] = "hello world";
  char compare[] = "world hello";
  eya_memory_view_t view = {&data[0], &data[sizeof(data) - 1]};
  EXPECT_EQ(eya_memory_view_rcompare_range(&view, &compare[0],
                                           &compare[sizeof(compare) - 1]),
            &data[10]);
}

TEST(eya_memory_view_rcompare, uninitialized_other) {
  int data[1] = {1};
  eya_memory_view_t view = {&data[0], &data[1]};
  eya_memory_view_t other = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_rcompare(&view, &other), ".*");
}

TEST(eya_memory_view_rcompare, empty_other) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  eya_memory_view_t other = {&data[0], &data[0]};
  EXPECT_EQ(eya_memory_view_rcompare(&view, &other), nullptr);
}

TEST(eya_memory_view_rcompare, identical_views) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_rcompare(&view, &view), nullptr);
}

TEST(eya_memory_view_rcompare, different_views) {
  int data[4] = {1, 2, 3, 4};
  int other_data[4] = {1, 2, 3, 0};
  eya_memory_view_t view = {&data[0], &data[4]};
  eya_memory_view_t other = {&other_data[0], &other_data[4]};
  EXPECT_EQ(eya_memory_view_rcompare(&view, &other), &data[3]);
}

TEST(eya_memory_view_make, valid_range) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = eya_memory_view_make(&data[0], &data[4]);
  EXPECT_EQ(view.begin, &data[0]);
  EXPECT_EQ(view.end, &data[4]);
}

TEST(eya_memory_view_make, empty_range) {
  int data[1] = {1};
  eya_memory_view_t view = eya_memory_view_make(&data[0], &data[0]);
  EXPECT_EQ(view.begin, &data[0]);
  EXPECT_EQ(view.end, &data[0]);
}

TEST(eya_memory_view_make, uninitialized_null_begin_and_end) {
  EXPECT_DEATH(eya_memory_view_make(nullptr, nullptr), ".*");
}

TEST(eya_memory_view_make, invalid_null_begin) {
  int data[1] = {1};
  EXPECT_DEATH(eya_memory_view_make(nullptr, &data[1]), ".*");
}

TEST(eya_memory_view_make, invalid_dangling) {
  int data[2] = {1, 2};
  EXPECT_DEATH(eya_memory_view_make(&data[1], &data[0]), ".*");
}

TEST(eya_memory_view_clone, valid_range) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t original = eya_memory_view_make(&data[0], &data[4]);
  eya_memory_view_t clone = eya_memory_view_clone(&original);
  EXPECT_EQ(clone.begin, original.begin);
  EXPECT_EQ(clone.end, original.end);
}

TEST(eya_memory_view_clone, empty_range) {
  int data[1] = {1};
  eya_memory_view_t original = eya_memory_view_make(&data[0], &data[0]);
  eya_memory_view_t clone = eya_memory_view_clone(&original);
  EXPECT_EQ(clone.begin, original.begin);
  EXPECT_EQ(clone.end, original.end);
}

TEST(eya_memory_view_clone, uninitialized_null_begin_and_end) {
  eya_memory_view_t original = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_clone(&original), ".*");
}

TEST(eya_memory_view_clone, invalid_null_begin) {
  int data[1] = {1};
  eya_memory_view_t original = {nullptr, &data[1]};
  EXPECT_DEATH(eya_memory_view_clone(&original), ".*");
}

TEST(eya_memory_view_clone, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t original = {&data[1], &data[0]};
  EXPECT_DEATH(eya_memory_view_clone(&original), ".*");
}