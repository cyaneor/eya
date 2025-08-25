#include <eya/array.h>
#include <gtest/gtest.h>

TEST(eya_array, creation) {
    eya_array_t array = eya_array_make(sizeof(int), 10);
    EXPECT_EQ(eya_array_capacity(&array), 10);
    eya_array_free(&array);
}

TEST(eya_array, resize_increase) {
    eya_array_t array = eya_array_make(sizeof(int), 5);
    eya_array_resize(&array, 10);
    EXPECT_EQ(eya_array_capacity(&array), 10);
    EXPECT_EQ(eya_array_get_size(&array), 10);
    eya_array_free(&array);
}

TEST(eya_array, resize_decrease) {
    eya_array_t array = eya_array_make(sizeof(int), 10);
    eya_array_resize(&array, 5);
    EXPECT_EQ(eya_array_capacity(&array), 10);
    EXPECT_EQ(eya_array_get_size(&array), 5);
    eya_array_free(&array);
}

TEST(eya_array, validation_index) {
    eya_array_t array = eya_array_make(sizeof(int), 10);
    EXPECT_TRUE(eya_array_is_valid_index(&array, 5));
    EXPECT_FALSE(eya_array_is_valid_index(&array, 10));
    eya_array_free(&array);
}

TEST(eya_array, access_from_front) {
    eya_array_t array = eya_array_make(sizeof(int), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(*(int*)eya_array_at_from_front(&array, i), 0);
    }
    eya_array_free(&array);
}

TEST(eya_array, access_from_back) {
    eya_array_t array = eya_array_make(sizeof(int), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(*(int*)eya_array_at_from_back(&array, i), 0);
    }
    eya_array_free(&array);
}

TEST(eya_array, access) {
    eya_array_t array = eya_array_make(sizeof(int), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(*(int*)eya_array_at(&array, i, false), 0);
        EXPECT_EQ(*(int*)eya_array_at(&array, i, true), 0);
    }
    eya_array_free(&array);
}

TEST(eya_array, front_access) {
    eya_array_t array = eya_array_make(sizeof(int), 10);
    EXPECT_EQ(*(int*)eya_array_front(&array), 0);
    eya_array_free(&array);
}

TEST(eya_array, back_access) {
    eya_array_t array = eya_array_make(sizeof(int), 10);
    EXPECT_EQ(*(int*)eya_array_back(&array), 0);
    eya_array_free(&array);
}

TEST(eya_array, empty_checks) {
    eya_array_t array = eya_array_make(sizeof(int), 0);
    EXPECT_TRUE(eya_array_is_empty(&array));
    eya_array_resize(&array, 10);
    EXPECT_FALSE(eya_array_is_empty(&array));
    eya_array_clear(&array);
    EXPECT_TRUE(eya_array_is_empty(&array));
    eya_array_free(&array);
}

TEST(eya_array, clear) {
    eya_array_t array = eya_array_make(sizeof(int), 10);
    eya_array_clear(&array);
    EXPECT_EQ(eya_array_get_size(&array), 0);
    EXPECT_EQ(eya_array_capacity(&array), 10);
    eya_array_free(&array);
}