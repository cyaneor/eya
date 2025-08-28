#include <eya/memory_typed.h>
#include <eya/memory_typed_initializer.h>
#include <gtest/gtest.h>

TEST(eya_memory_typed_unpack_full, valid_input)
{
    int array[5] = {1, 2, 3, 4, 5};

    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 5), sizeof(int));

    void       *begin        = nullptr;
    void       *end          = nullptr;
    eya_usize_t element_size = 0;

    eya_memory_typed_unpack_full(&self, &begin, &end, &element_size);

    EXPECT_EQ(begin, static_cast<void *>(array));
    EXPECT_EQ(end, static_cast<void *>(array + 5));
    EXPECT_EQ(element_size, sizeof(int));
}

TEST(eya_memory_typed_unpack_full, empty_range)
{
    eya_memory_typed_t typed_range = eya_memory_typed_empty_initializer(sizeof(double));

    void       *begin        = nullptr;
    void       *end          = nullptr;
    eya_usize_t element_size = 0;

    eya_memory_typed_unpack_full(&typed_range, &begin, &end, &element_size);

    EXPECT_EQ(begin, nullptr);
    EXPECT_EQ(end, nullptr);
    EXPECT_EQ(element_size, sizeof(double));
}

TEST(eya_memory_typed_unpack_full, null_element_size)
{
    char               array[3] = {'a', 'b', 'c'};
    eya_memory_typed_t typed_range =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(char));

    void *begin = nullptr;
    void *end   = nullptr;

    eya_memory_typed_unpack_full(&typed_range, &begin, &end, nullptr);

    EXPECT_EQ(begin, static_cast<void *>(array));
    EXPECT_EQ(end, static_cast<void *>(array + 3));
}

TEST(eya_memory_typed_unpack_full, uninitialized_range)
{
    eya_memory_typed_t typed_range = eya_memory_typed_empty_initializer(sizeof(float));

    void *begin = reinterpret_cast<void *>(0x1234);
    void *end   = reinterpret_cast<void *>(0x5678);

    eya_usize_t element_size = 0;
    eya_memory_typed_unpack_full(&typed_range, &begin, &end, &element_size);

    EXPECT_EQ(begin, nullptr);
    EXPECT_EQ(end, nullptr);
    EXPECT_EQ(element_size, sizeof(float));
}

TEST(eya_memory_typed_unpack, valid_input)
{
    int                array[5] = {1, 2, 3, 4, 5};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 5), sizeof(int));

    eya_memory_range_t range        = {nullptr, nullptr};
    eya_usize_t        element_size = 0;

    eya_memory_typed_unpack(&self, &range, &element_size);

    EXPECT_EQ(range.begin, static_cast<void *>(array));
    EXPECT_EQ(range.end, static_cast<void *>(array + 5));
    EXPECT_EQ(element_size, sizeof(int));
}

TEST(eya_memory_typed_unpack, null_element_size)
{
    char               array[3] = {'a', 'b', 'c'};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(char));

    eya_memory_range_t range = {nullptr, nullptr};
    eya_memory_typed_unpack(&self, &range, nullptr);

    EXPECT_EQ(range.begin, static_cast<void *>(array));
    EXPECT_EQ(range.end, static_cast<void *>(array + 3));
}

TEST(eya_memory_typed_unpack, null_range)
{
    int                array[5] = {1, 2, 3, 4, 5};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 5), sizeof(int));

    eya_usize_t element_size = 0;
    eya_memory_typed_unpack(&self, nullptr, &element_size);

    EXPECT_EQ(element_size, sizeof(int));
}

TEST(eya_memory_typed_unpack, empty_range)
{
    eya_memory_typed_t self = eya_memory_typed_empty_initializer(sizeof(double));

    eya_memory_range_t range = {reinterpret_cast<void *>(0x1234), reinterpret_cast<void *>(0x5678)};
    eya_usize_t        element_size = 0;

    eya_memory_typed_unpack(&self, &range, &element_size);

    EXPECT_EQ(range.begin, nullptr);
    EXPECT_EQ(range.end, nullptr);
    EXPECT_EQ(element_size, sizeof(double));
}

TEST(eya_memory_typed_get_element_size, valid_input)
{
    int                array[5] = {1, 2, 3, 4, 5};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 5), sizeof(int));

    eya_usize_t result = eya_memory_typed_get_element_size(&self);
    EXPECT_EQ(result, sizeof(int));
}

TEST(eya_memory_typed_get_element_size, empty_range)
{
    eya_memory_typed_t self   = eya_memory_typed_empty_initializer(sizeof(double));
    eya_usize_t        result = eya_memory_typed_get_element_size(&self);
    EXPECT_EQ(result, sizeof(double));
}

TEST(eya_memory_typed_get_element_size, zero_element_size)
{
    eya_memory_typed_t self   = eya_memory_typed_empty_initializer(0);
    eya_usize_t        result = eya_memory_typed_get_element_size(&self);
    EXPECT_EQ(result, 0);
}

TEST(eya_memory_typed_get_element_size, null_self)
{
    EXPECT_DEATH(eya_memory_typed_get_element_size(nullptr), ".*");
}

TEST(eya_memory_typed_is_valid, valid_range)
{
    int                array[4] = {1, 2, 3, 4};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 4), sizeof(int));

    bool result = eya_memory_typed_is_valid(&self);
    EXPECT_TRUE(result);
}

TEST(eya_memory_typed_is_valid, invalid_range)
{
    char               array[5] = {'a', 'b', 'c', 'd', 'e'};
    eya_memory_typed_t self     = eya_memory_typed_initializer(
        eya_memory_range_initializer(array, array + 3), // Non-multiple of element_size
        sizeof(int)                                     // 4 bytes, but range size is 3 bytes
    );

    bool result = eya_memory_typed_is_valid(&self);
    EXPECT_FALSE(result);
}

TEST(eya_memory_typed_is_valid, empty_range)
{
    eya_memory_typed_t self = eya_memory_typed_empty_initializer(sizeof(double));
    EXPECT_DEATH(eya_memory_typed_is_valid(&self), ".*");
}

TEST(eya_memory_typed_is_valid, zero_element_size)
{
    int                array[4] = {1, 2, 3, 4};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 4), 0);

    EXPECT_DEATH(eya_memory_typed_is_valid(&self), ".*");
}

TEST(eya_memory_typed_is_valid, null_self)
{
    EXPECT_DEATH(eya_memory_typed_is_valid(nullptr), ".*");
}

TEST(eya_memory_typed_get_size, valid_input)
{
    int                array[5] = {1, 2, 3, 4, 5};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 5), sizeof(int));

    eya_usize_t size = eya_memory_typed_get_size(&self);
    EXPECT_EQ(size, 5);
}

TEST(eya_memory_typed_get_size, empty_range)
{
    eya_memory_typed_t self = eya_memory_typed_empty_initializer(sizeof(double));
    EXPECT_DEATH(eya_memory_typed_get_size(&self), ".*");
}

TEST(eya_memory_typed_get_size, single_element)
{
    char               array[1] = {'a'};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 1), sizeof(char));

    eya_usize_t size = eya_memory_typed_get_size(&self);
    EXPECT_EQ(size, 1);
}

TEST(eya_memory_typed_get_size, null_self)
{
    EXPECT_DEATH(eya_memory_typed_get_size(nullptr), ".*");
}

TEST(eya_memory_typed_get_size, invalid_range_size)
{
    char               array[5] = {'a', 'b', 'c', 'd', 'e'};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), // 3 bytes
                                     sizeof(int) // 4 bytes, not a multiple
        );

    EXPECT_DEATH(eya_memory_typed_get_size(&self), ".*");
}

TEST(eya_memory_typed_is_empty, empty_range)
{
    eya_memory_typed_t self = eya_memory_typed_empty_initializer(sizeof(double));
    EXPECT_DEATH(eya_memory_typed_is_empty(&self), ".*");
}

TEST(eya_memory_typed_is_empty, non_empty_range)
{
    int                array[5] = {1, 2, 3, 4, 5};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 5), sizeof(int));

    bool is_empty = eya_memory_typed_is_empty(&self);
    EXPECT_FALSE(is_empty);
}

TEST(eya_memory_typed_is_empty, single_element)
{
    char               array[1] = {'a'};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 1), sizeof(char));

    bool is_empty = eya_memory_typed_is_empty(&self);
    EXPECT_FALSE(is_empty);
}

TEST(eya_memory_typed_is_empty, null_self)
{
    EXPECT_DEATH(eya_memory_typed_is_empty(nullptr), ".*");
}

TEST(eya_memory_typed_is_empty, invalid_range_size)
{
    char               array[5] = {'a', 'b', 'c', 'd', 'e'};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    EXPECT_DEATH(eya_memory_typed_is_empty(&self), ".*");
}

TEST(eya_memory_typed_swap, valid_swap_same_element_size)
{
    int                array1[3] = {1, 2, 3};
    int                array2[2] = {4, 5};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array1, array1 + 3), sizeof(int));

    eya_memory_typed_t other =
        eya_memory_typed_initializer(eya_memory_range_initializer(array2, array2 + 2), sizeof(int));

    eya_memory_typed_t self_before  = self;
    eya_memory_typed_t other_before = other;

    eya_memory_typed_swap(&self, &other);

    EXPECT_EQ(self.range.begin, other_before.range.begin);
    EXPECT_EQ(self.range.end, other_before.range.end);
    EXPECT_EQ(self.element_size, self_before.element_size);
    EXPECT_EQ(other.range.begin, self_before.range.begin);
    EXPECT_EQ(other.range.end, self_before.range.end);
    EXPECT_EQ(other.element_size, other_before.element_size);
}

TEST(eya_memory_typed_swap, empty_ranges_same_element_size)
{
    eya_memory_typed_t self  = eya_memory_typed_empty_initializer(sizeof(double));
    eya_memory_typed_t other = eya_memory_typed_empty_initializer(sizeof(double));

    eya_memory_typed_t self_before  = self;
    eya_memory_typed_t other_before = other;

    eya_memory_typed_swap(&self, &other);

    EXPECT_EQ(self.range.begin, other_before.range.begin);
    EXPECT_EQ(self.range.end, other_before.range.end);
    EXPECT_EQ(self.element_size, self_before.element_size);
    EXPECT_EQ(other.range.begin, self_before.range.begin);
    EXPECT_EQ(other.range.end, self_before.range.end);
    EXPECT_EQ(other.element_size, other_before.element_size);
}

TEST(eya_memory_typed_swap, different_element_sizes)
{
    int                array1[3] = {1, 2, 3};
    char               array2[2] = {'a', 'b'};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array1, array1 + 3), sizeof(int));

    eya_memory_typed_t other = eya_memory_typed_initializer(
        eya_memory_range_initializer(array2, array2 + 2), sizeof(char));

    EXPECT_DEATH(eya_memory_typed_swap(&self, &other), ".*");
}

TEST(eya_memory_typed_swap, null_self)
{
    int                array[3] = {1, 2, 3};
    eya_memory_typed_t other =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    EXPECT_DEATH(eya_memory_typed_swap(nullptr, &other), ".*");
}

TEST(eya_memory_typed_swap, null_other)
{
    int                array[3] = {1, 2, 3};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    EXPECT_DEATH(eya_memory_typed_swap(&self, nullptr), ".*");
}

TEST(eya_memory_typed_swap, same_range)
{
    int                array[3] = {1, 2, 3};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    eya_memory_typed_t self_before = self;
    eya_memory_typed_swap(&self, &self);

    EXPECT_EQ(self.range.begin, self_before.range.begin);
    EXPECT_EQ(self.range.end, self_before.range.end);
    EXPECT_EQ(self.element_size, self_before.element_size);
}

TEST(eya_memory_range_is_valid_index, valid_index)
{
    int                array[5] = {1, 2, 3, 4, 5};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 5), sizeof(int));

    bool is_valid = eya_memory_range_is_valid_index(&self, 2);
    EXPECT_TRUE(is_valid);
}

TEST(eya_memory_range_is_valid_index, index_equal_to_size)
{
    int                array[3] = {1, 2, 3};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    bool is_valid = eya_memory_range_is_valid_index(&self, 3);
    EXPECT_FALSE(is_valid);
}

TEST(eya_memory_range_is_valid_index, index_beyond_size)
{
    int                array[3] = {1, 2, 3};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    bool is_valid = eya_memory_range_is_valid_index(&self, 5);
    EXPECT_FALSE(is_valid);
}

TEST(eya_memory_range_is_valid_index, empty_range)
{
    eya_memory_typed_t self = eya_memory_typed_empty_initializer(sizeof(double));
    EXPECT_DEATH(eya_memory_range_is_valid_index(&self, 0), ".*");
}

TEST(eya_memory_range_is_valid_index, null_self)
{
    EXPECT_DEATH(eya_memory_range_is_valid_index(nullptr, 0), ".*");
}

TEST(eya_memory_range_is_valid_index, invalid_range_size)
{
    char               array[5] = {'a', 'b', 'c', 'd', 'e'};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    EXPECT_DEATH(eya_memory_range_is_valid_index(&self, 0), ".*");
}

TEST(eya_memory_typed_at_from_front, valid_index)
{
    int                array[5] = {1, 2, 3, 4, 5};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 5), sizeof(int));

    void *result = eya_memory_typed_at_from_front(&self, 2);

    EXPECT_EQ(result, static_cast<void *>(array + 2));
}

TEST(eya_memory_typed_at_from_front, index_zero)
{
    int                array[3] = {1, 2, 3};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    void *result = eya_memory_typed_at_from_front(&self, 0);

    EXPECT_EQ(result, static_cast<void *>(array));
}

TEST(eya_memory_typed_at_from_front, empty_range)
{
    eya_memory_typed_t self = eya_memory_typed_empty_initializer(sizeof(double));
    EXPECT_DEATH(eya_memory_typed_at_from_front(&self, 0), ".*");
}

TEST(eya_memory_typed_at_from_front, null_self)
{
    EXPECT_DEATH(eya_memory_typed_at_from_front(nullptr, 0), ".*");
}

TEST(eya_memory_typed_at_from_front, invalid_range_size)
{
    char               array[5] = {'a', 'b', 'c', 'd', 'e'};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    EXPECT_DEATH(eya_memory_typed_at_from_front(&self, 0), ".*");
}

TEST(eya_memory_typed_at_from_front, index_equal_to_size)
{
    int                array[3] = {1, 2, 3};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    EXPECT_DEATH(eya_memory_typed_at_from_front(&self, 3), ".*");
}

TEST(eya_memory_typed_at_from_back, valid_index)
{
    int                array[5] = {1, 2, 3, 4, 5};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 5), sizeof(int));

    void *result = eya_memory_typed_at_from_back(&self, 1);
    EXPECT_EQ(result, static_cast<void *>(array + 3));
}

TEST(eya_memory_typed_at_from_back, index_zero)
{
    int                array[3] = {1, 2, 3};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    void *result = eya_memory_typed_at_from_back(&self, 0);
    EXPECT_EQ(result, static_cast<void *>(array + 2));
}

TEST(eya_memory_typed_at_from_back, empty_range)
{
    eya_memory_typed_t self = eya_memory_typed_empty_initializer(sizeof(double));
    EXPECT_DEATH(eya_memory_typed_at_from_back(&self, 0), ".*");
}

TEST(eya_memory_typed_at_from_back, null_self)
{
    EXPECT_DEATH(eya_memory_typed_at_from_back(nullptr, 0), ".*");
}

TEST(eya_memory_typed_at_from_back, invalid_range_size)
{
    char               array[5] = {'a', 'b', 'c', 'd', 'e'};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    EXPECT_DEATH(eya_memory_typed_at_from_back(&self, 0), ".*");
}

TEST(eya_memory_typed_at_from_back, index_equal_to_size)
{
    int                array[3] = {1, 2, 3};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    EXPECT_DEATH(eya_memory_typed_at_from_back(&self, 3), ".*");
}

TEST(eya_memory_typed_front, valid_range)
{
    int                array[5] = {1, 2, 3, 4, 5};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 5), sizeof(int));

    void *result = eya_memory_typed_front(&self);
    EXPECT_EQ(result, static_cast<void *>(array));
}

TEST(eya_memory_typed_front, single_element)
{
    char               array[1] = {'a'};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 1), sizeof(char));

    void *result = eya_memory_typed_front(&self);
    EXPECT_EQ(result, static_cast<void *>(array));
}

TEST(eya_memory_typed_front, empty_range)
{
    eya_memory_typed_t self = eya_memory_typed_empty_initializer(sizeof(double));

    EXPECT_DEATH(eya_memory_typed_front(&self), ".*");
}

TEST(eya_memory_typed_front, null_self)
{
    EXPECT_DEATH(eya_memory_typed_front(nullptr), ".*");
}

TEST(eya_memory_typed_front, invalid_range_size)
{
    char               array[5] = {'a', 'b', 'c', 'd', 'e'};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    EXPECT_DEATH(eya_memory_typed_front(&self), ".*");
}

TEST(eya_memory_typed_back, valid_range)
{
    int                array[5] = {1, 2, 3, 4, 5};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 5), sizeof(int));

    void *result = eya_memory_typed_back(&self);
    EXPECT_EQ(result, static_cast<void *>(array + 4));
}

TEST(eya_memory_typed_back, single_element)
{
    char               array[1] = {'a'};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 1), sizeof(char));

    void *result = eya_memory_typed_back(&self);
    EXPECT_EQ(result, static_cast<void *>(array));
}

TEST(eya_memory_typed_back, empty_range)
{
    eya_memory_typed_t self = eya_memory_typed_empty_initializer(sizeof(double));
    EXPECT_DEATH(eya_memory_typed_back(&self), ".*");
}

TEST(eya_memory_typed_back, null_self)
{
    EXPECT_DEATH(eya_memory_typed_back(nullptr), ".*");
}

TEST(eya_memory_typed_back, invalid_range_size)
{
    char               array[5] = {'a', 'b', 'c', 'd', 'e'};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    EXPECT_DEATH(eya_memory_typed_back(&self), ".*");
}

TEST(eya_memory_typed_is_equal, equal_ranges_same_element_size)
{
    int array[3] = {1, 2, 3};

    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));
    eya_memory_typed_t other =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    EXPECT_TRUE(eya_memory_typed_is_equal(&self, &other));
}

TEST(eya_memory_typed_is_equal, different_element_sizes)
{
    int array[3] = {1, 2, 3};

    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));
    eya_memory_typed_t other =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(char));

    EXPECT_FALSE(eya_memory_typed_is_equal(&self, &other));
}

TEST(eya_memory_typed_is_equal, different_ranges_same_element_size)
{
    int array1[3] = {1, 2, 3};
    int array2[2] = {4, 5};

    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array1, array1 + 3), sizeof(int));
    eya_memory_typed_t other =
        eya_memory_typed_initializer(eya_memory_range_initializer(array2, array2 + 2), sizeof(int));

    EXPECT_FALSE(eya_memory_typed_is_equal(&self, &other));
}

TEST(eya_memory_typed_is_equal, empty_ranges_same_element_size)
{
    eya_memory_typed_t self  = eya_memory_typed_empty_initializer(sizeof(double));
    eya_memory_typed_t other = eya_memory_typed_empty_initializer(sizeof(double));
    EXPECT_TRUE(eya_memory_typed_is_equal(&self, &other));
}

TEST(eya_memory_typed_is_equal, null_self)
{
    int                array[3] = {1, 2, 3};
    eya_memory_typed_t other =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    EXPECT_DEATH(eya_memory_typed_is_equal(nullptr, &other), ".*");
}

TEST(eya_memory_typed_is_equal, null_other)
{
    int                array[3] = {1, 2, 3};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    EXPECT_DEATH(eya_memory_typed_is_equal(&self, nullptr), ".*");
}

TEST(eya_memory_typed_is_equal, same_range)
{
    int                array[3] = {1, 2, 3};
    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    EXPECT_TRUE(eya_memory_typed_is_equal(&self, &self));
}

TEST(eya_memory_typed_is_equal, invalid_range_size)
{
    char array[5] = {'a', 'b', 'c', 'd', 'e'};

    eya_memory_typed_t self =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));
    eya_memory_typed_t other =
        eya_memory_typed_initializer(eya_memory_range_initializer(array, array + 3), sizeof(int));

    EXPECT_TRUE(eya_memory_typed_is_equal(&self, &other));
}