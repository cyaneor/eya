#include <eya/array.h>
#include <gtest/gtest.h>

TEST(eya_array_make, should_create_with_correct_capacity)
{
    eya_array_t array = eya_array_make(sizeof(int), 10);
    EXPECT_EQ(eya_array_capacity(&array), 10);
    eya_array_free(&array);
}

TEST(eya_array_resize, should_increase_capacity_and_size)
{
    eya_array_t array = eya_array_make(sizeof(int), 5);
    eya_array_resize(&array, 10);
    EXPECT_EQ(eya_array_capacity(&array), 10);
    EXPECT_EQ(eya_array_get_size(&array), 10);
    eya_array_free(&array);
}

TEST(eya_array_resize, should_decrease_size_but_keep_capacity)
{
    eya_array_t array = eya_array_make(sizeof(int), 10);
    eya_array_resize(&array, 5);
    EXPECT_EQ(eya_array_capacity(&array), 10);
    EXPECT_EQ(eya_array_get_size(&array), 5);
    eya_array_free(&array);
}

TEST(eya_array_is_valid_index, should_validate_bounds_correctly)
{
    eya_array_t array = eya_array_make(sizeof(int), 10);
    EXPECT_TRUE(eya_array_is_valid_index(&array, 5));
    EXPECT_FALSE(eya_array_is_valid_index(&array, 10));
    eya_array_free(&array);
}

TEST(eya_array_at_from_front, should_access_elements_correctly)
{
    eya_array_t array = eya_array_make(sizeof(int), 10);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(*(int *)eya_array_at_from_front(&array, i), 0);
    }
    eya_array_free(&array);
}

TEST(eya_array_at_from_back, should_access_elements_correctly)
{
    eya_array_t array = eya_array_make(sizeof(int), 10);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(*(int *)eya_array_at_from_back(&array, i), 0);
    }
    eya_array_free(&array);
}

TEST(eya_array_at, should_access_with_direction_flag)
{
    eya_array_t array = eya_array_make(sizeof(int), 10);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(*(int *)eya_array_at(&array, i, false), 0);
        EXPECT_EQ(*(int *)eya_array_at(&array, i, true), 0);
    }
    eya_array_free(&array);
}

TEST(eya_array_front, should_return_first_element)
{
    eya_array_t array = eya_array_make(sizeof(int), 10);
    EXPECT_EQ(*(int *)eya_array_front(&array), 0);
    eya_array_free(&array);
}

TEST(eya_array_back, should_return_last_element)
{
    eya_array_t array = eya_array_make(sizeof(int), 10);
    EXPECT_EQ(*(int *)eya_array_back(&array), 0);
    eya_array_free(&array);
}

TEST(eya_array_is_empty, should_detect_empty_state)
{
    eya_array_t array = eya_array_make(sizeof(int), 0);
    EXPECT_TRUE(eya_array_is_empty(&array));
    eya_array_resize(&array, 10);
    EXPECT_FALSE(eya_array_is_empty(&array));
    eya_array_clear(&array);
    EXPECT_TRUE(eya_array_is_empty(&array));
    eya_array_free(&array);
}

TEST(eya_array_reserve, should_increase_capacity_without_changing_size)
{
    eya_usize_t element_size = 4;
    eya_usize_t size         = 10;
    eya_array_t array        = eya_array_make(element_size, size);
    EXPECT_EQ(size, array.size);

    eya_array_reserve(&array, 20);
    EXPECT_EQ(size, array.size);

    eya_array_reserve(&array, 50);
    EXPECT_EQ(size, array.size);
}

TEST(eya_array_is_full, returns_true_when_size_equals_capacity)
{
    eya_array_t array = eya_array_make(sizeof(int), 10);
    EXPECT_TRUE(eya_array_is_full(&array));
}