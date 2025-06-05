#include <eya/memory_view.h>
#include <gtest/gtest.h>

TEST(eya_memory_view_unpack, unpack_with_only_begin) {
  eya_memory_view_t view = {.begin = (void *)0x1000, .end = (void *)0x2000};
  const void *begin = nullptr;

  eya_memory_view_unpack(&view, &begin, nullptr);
  EXPECT_EQ(begin, (void *)0x1000);
}

TEST(eya_memory_view_unpack, unpack_with_only_end) {
  eya_memory_view_t view = {.begin = (void *)0x1000, .end = (void *)0x2000};
  const void *end = nullptr;

  eya_memory_view_unpack(&view, nullptr, &end);
  EXPECT_EQ(end, (void *)0x2000);
}

TEST(eya_memory_view_unpack, unpack_with_null_pointers) {
  eya_memory_view_t view = {.begin = (void *)0x1000, .end = (void *)0x2000};
  eya_memory_view_unpack(&view, nullptr, nullptr);
  EXPECT_EQ(view.begin, (void *)0x1000);
  EXPECT_EQ(view.end, (void *)0x2000);
}

TEST(eya_memory_view_unpack, unpack_with_null_self) {
  EXPECT_DEATH(eya_memory_view_unpack(nullptr, nullptr, nullptr), ".*");
}

TEST(eya_memory_view_get_begin, valid_self) {
  eya_memory_view_t view = {.begin = (void *)0x1000, .end = (void *)0x2000};

  const void *result = eya_memory_view_get_begin(&view);
  EXPECT_EQ(result, (void *)0x1000);
}

TEST(eya_memory_view_get_begin, null_self) {
  EXPECT_DEATH(eya_memory_view_get_begin(nullptr), ".*");
}

TEST(eya_memory_view_get_end, valid_self) {
  eya_memory_view_t view = {.begin = (void *)0x1000, .end = (void *)0x2000};

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

TEST(eya_memory_view_is_uninitialized, null_self) {
  EXPECT_DEATH(eya_memory_view_is_uninitialized(nullptr), ".*");
}

TEST(eya_memory_view_is_uninitialized, uninitialized) {
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_TRUE(eya_memory_view_is_uninitialized(&view));
}

TEST(eya_memory_view_is_uninitialized, empty) {
  int dummy;
  eya_memory_view_t view = {&dummy, &dummy};
  EXPECT_FALSE(eya_memory_view_is_uninitialized(&view));
}

TEST(eya_memory_view_is_uninitialized, invalid_null_begin) {
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  EXPECT_FALSE(eya_memory_view_is_uninitialized(&view));
}

TEST(eya_memory_view_is_uninitialized, invalid_null_end) {
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_FALSE(eya_memory_view_is_uninitialized(&view));
}

TEST(eya_memory_view_is_uninitialized, has_data) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[0], &data[1]};
  EXPECT_FALSE(eya_memory_view_is_uninitialized(&view));
}

TEST(eya_memory_view_is_uninitialized, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_FALSE(eya_memory_view_is_uninitialized(&view));
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

TEST(eya_memory_view_udiff, uninitialized) {
  eya_memory_view_t view = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_udiff(&view), ".*");
}

TEST(eya_memory_view_udiff, invalid_null_begin) {
  int dummy;
  eya_memory_view_t view = {nullptr, &dummy};
  EXPECT_DEATH(eya_memory_view_udiff(&view), ".*");
}

TEST(eya_memory_view_udiff, invalid_null_end) {
  int dummy;
  eya_memory_view_t view = {&dummy, nullptr};
  EXPECT_DEATH(eya_memory_view_udiff(&view), ".*");
}

TEST(eya_memory_view_udiff, invalid_dangling) {
  int data[2] = {1, 2};
  eya_memory_view_t view = {&data[1], &data[0]};
  EXPECT_DEATH(eya_memory_view_udiff(&view), ".*");
}

TEST(eya_memory_view_udiff, valid_single_byte) {
  char byte = 'A';
  eya_memory_view_t view = {&byte, &byte + 1};
  EXPECT_EQ(eya_memory_view_udiff(&view), 1);
}

TEST(eya_memory_view_udiff, valid_multiple_bytes) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t view = {&data[0], &data[4]};
  EXPECT_EQ(eya_memory_view_udiff(&view), 4 * sizeof(int));
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

TEST(eya_memory_view_contains_other, uninitialized_self) {
  eya_memory_view_t self = {nullptr, nullptr};
  char byte = 'A';
  eya_memory_view_t other = {&byte, &byte + 1};
  EXPECT_DEATH(eya_memory_view_contains_other(&self, &other), ".*");
}

TEST(eya_memory_view_contains_other, uninitialized_other) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t self = {&data[0], &data[4]};
  eya_memory_view_t other = {nullptr, nullptr};
  EXPECT_DEATH(eya_memory_view_contains_other(&self, &other), ".*");
}

TEST(eya_memory_view_contains_other, invalid_null_begin_self) {
  int dummy;
  eya_memory_view_t self = {nullptr, &dummy};
  eya_memory_view_t other = {&dummy, &dummy + 1};
  EXPECT_DEATH(eya_memory_view_contains_other(&self, &other), ".*");
}

TEST(eya_memory_view_contains_other, invalid_null_end_other) {
  int dummy;
  eya_memory_view_t self = {&dummy, &dummy + 1};
  eya_memory_view_t other = {&dummy, nullptr};
  EXPECT_DEATH(eya_memory_view_contains_other(&self, &other), ".*");
}

TEST(eya_memory_view_contains_other, valid_contains_exact) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t self = {&data[0], &data[4]};
  eya_memory_view_t other = {&data[0], &data[4]};
  EXPECT_FALSE(eya_memory_view_contains_other(&self, &other));
}

TEST(eya_memory_view_contains_other, valid_contains_subset) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t self = {&data[0], &data[4]};
  eya_memory_view_t other = {&data[1], &data[3]};
  EXPECT_TRUE(eya_memory_view_contains_other(&self, &other));
}

TEST(eya_memory_view_contains_other, valid_not_contains_before) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t self = {&data[1], &data[4]};
  eya_memory_view_t other = {&data[0], &data[2]};
  EXPECT_FALSE(eya_memory_view_contains_other(&self, &other));
}

TEST(eya_memory_view_contains_other, valid_not_contains_after) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t self = {&data[0], &data[3]};
  eya_memory_view_t other = {&data[2], &data[4]};
  EXPECT_FALSE(eya_memory_view_contains_other(&self, &other));
}

TEST(eya_memory_view_contains_other, valid_single_byte_contains) {
  char byte = 'A';
  eya_memory_view_t self = {&byte, &byte + 1};
  eya_memory_view_t other = {&byte, &byte + 1};
  EXPECT_FALSE(eya_memory_view_contains_other(&self, &other));
}

TEST(eya_memory_view_contains_other, valid_empty_other) {
  int data[4] = {1, 2, 3, 4};
  eya_memory_view_t self = {&data[0], &data[4]};
  eya_memory_view_t other = {&data[2], &data[2]};
  EXPECT_TRUE(eya_memory_view_contains_other(&self, &other));
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

TEST(eya_memory_view_is_begin_equal, valid_equal) {
  int data[2];
  eya_memory_view_t view = {&data[0], &data[1]};
  EXPECT_TRUE(eya_memory_view_is_begin_equal(&view, &data[0]));
}

TEST(eya_memory_view_is_begin_equal, valid_not_equal) {
  int data[2];
  int other;
  eya_memory_view_t view = {&data[0], &data[1]};
  EXPECT_FALSE(eya_memory_view_is_begin_equal(&view, &other));
}

TEST(eya_memory_view_is_end_equal, valid_equal) {
  int data[2];
  eya_memory_view_t view = {&data[0], &data[1]};
  EXPECT_TRUE(eya_memory_view_is_end_equal(&view, &data[1]));
}

TEST(eya_memory_view_is_end_equal, valid_not_equal) {
  int data[2];
  int other;
  eya_memory_view_t view = {&data[0], &data[1]};
  EXPECT_FALSE(eya_memory_view_is_end_equal(&view, &other));
}

TEST(eya_memory_view_is_begin_equal_to, same_view) {
  int data[2];
  eya_memory_view_t view1 = {&data[0], &data[1]};
  eya_memory_view_t view2 = {&data[0], &data[1]};
  EXPECT_TRUE(eya_memory_view_is_begin_equal_to(&view1, &view2));
}

TEST(eya_memory_view_is_begin_equal_to, different_begin) {
  int data[3];
  eya_memory_view_t view1 = {&data[0], &data[2]};
  eya_memory_view_t view2 = {&data[1], &data[2]};
  EXPECT_FALSE(eya_memory_view_is_begin_equal_to(&view1, &view2));
}

TEST(eya_memory_view_is_begin_equal_to, same_begin_different_end) {
  int data[3];
  eya_memory_view_t view1 = {&data[0], &data[1]};
  eya_memory_view_t view2 = {&data[0], &data[2]};
  EXPECT_TRUE(eya_memory_view_is_begin_equal_to(&view1, &view2));
}

TEST(eya_memory_view_is_end_equal_to, same_view) {
  int data[2];
  eya_memory_view_t view1 = {&data[0], &data[1]};
  eya_memory_view_t view2 = {&data[0], &data[1]};
  EXPECT_TRUE(eya_memory_view_is_end_equal_to(&view1, &view2));
}

TEST(eya_memory_view_is_end_equal_to, different_end) {
  int data[3];
  eya_memory_view_t view1 = {&data[0], &data[1]};
  eya_memory_view_t view2 = {&data[0], &data[2]};
  EXPECT_FALSE(eya_memory_view_is_end_equal_to(&view1, &view2));
}

TEST(eya_memory_view_is_end_equal_to, same_end_different_begin) {
  int data[3];
  eya_memory_view_t view1 = {&data[0], &data[2]};
  eya_memory_view_t view2 = {&data[1], &data[2]};
  EXPECT_TRUE(eya_memory_view_is_end_equal_to(&view1, &view2));
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