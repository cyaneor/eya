#include <gtest/gtest.h>
#include <eya/interval_util.h>

TEST(eya_interval_contains_value, closed_integer_values)
{
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1, 3, 5));
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1, 1, 5));
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1, 5, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1, 0, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1, 6, 5));
}

TEST(eya_interval_contains_value, closed_float_values)
{
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1.0, 3.0, 5.0));
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1.0, 1.0, 5.0));
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1.0, 5.0, 5.0));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1.0, 0.9, 5.0));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1.0, 5.1, 5.0));
}

TEST(eya_interval_contains_value, left_open_integer_values)
{
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_LEFT_OPEN, 1, 3, 5));
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_LEFT_OPEN, 1, 5, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_LEFT_OPEN, 1, 1, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_LEFT_OPEN, 1, 0, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_LEFT_OPEN, 1, 6, 5));
}

TEST(eya_interval_contains_value, right_open_integer_values)
{
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_RIGHT_OPEN, 1, 3, 5));
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_RIGHT_OPEN, 1, 1, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_RIGHT_OPEN, 1, 5, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_RIGHT_OPEN, 1, 0, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_RIGHT_OPEN, 1, 6, 5));
}

TEST(eya_interval_contains_value, open_integer_values)
{
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_OPEN, 1, 3, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_OPEN, 1, 1, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_OPEN, 1, 5, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_OPEN, 1, 0, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_OPEN, 1, 6, 5));
}

TEST(eya_interval_contains_range, closed_intervals)
{
    EXPECT_TRUE(eya_interval_contains_range(EYA_INTERVAL_TYPE_CLOSED, 1, 10, 2, 8));
    EXPECT_TRUE(eya_interval_contains_range(EYA_INTERVAL_TYPE_CLOSED, 1, 10, 1, 10));
    EXPECT_FALSE(eya_interval_contains_range(EYA_INTERVAL_TYPE_CLOSED, 1, 5, 0, 6));
    EXPECT_FALSE(eya_interval_contains_range(EYA_INTERVAL_TYPE_CLOSED, 1, 5, 2, 6));
}

TEST(eya_interval_contains_range, left_open_intervals)
{
    EXPECT_TRUE(eya_interval_contains_range(EYA_INTERVAL_TYPE_LEFT_OPEN, 1, 10, 2, 8));
    EXPECT_TRUE(eya_interval_contains_range(EYA_INTERVAL_TYPE_LEFT_OPEN, 1, 10, 2, 10));
    EXPECT_FALSE(eya_interval_contains_range(EYA_INTERVAL_TYPE_LEFT_OPEN, 1, 5, 1, 5));
    EXPECT_FALSE(eya_interval_contains_range(EYA_INTERVAL_TYPE_LEFT_OPEN, 1, 5, 0, 6));
}

TEST(eya_interval_contains_range, right_open_intervals)
{
    EXPECT_TRUE(eya_interval_contains_range(EYA_INTERVAL_TYPE_RIGHT_OPEN, 1, 10, 2, 8));
    EXPECT_TRUE(eya_interval_contains_range(EYA_INTERVAL_TYPE_RIGHT_OPEN, 1, 10, 1, 8));
    EXPECT_FALSE(eya_interval_contains_range(EYA_INTERVAL_TYPE_RIGHT_OPEN, 1, 5, 2, 5));
    EXPECT_FALSE(eya_interval_contains_range(EYA_INTERVAL_TYPE_RIGHT_OPEN, 1, 5, 0, 6));
}

TEST(eya_interval_contains_range, open_intervals)
{
    EXPECT_TRUE(eya_interval_contains_range(EYA_INTERVAL_TYPE_OPEN, 1, 10, 2, 8));
    EXPECT_FALSE(eya_interval_contains_range(EYA_INTERVAL_TYPE_OPEN, 1, 5, 1, 5));
    EXPECT_FALSE(eya_interval_contains_range(EYA_INTERVAL_TYPE_OPEN, 1, 5, 2, 5));
    EXPECT_FALSE(eya_interval_contains_range(EYA_INTERVAL_TYPE_OPEN, 1, 5, 0, 6));
}