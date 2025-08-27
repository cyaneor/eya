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