#include <gtest/gtest.h>
#include <eya/interval_util.h>

TEST(eya_interval_contains_value_closed, integer_values)
{
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1, 3, 5));
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1, 1, 5));
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1, 5, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1, 0, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1, 6, 5));
}

TEST(eya_interval_contains_value_closed_float, float_values)
{
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1.0, 3.0, 5.0));
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1.0, 1.0, 5.0));
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1.0, 5.0, 5.0));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1.0, 0.9, 5.0));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_CLOSED, 1.0, 5.1, 5.0));
}

TEST(eya_interval_contains_value_left_open, integer_values)
{
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_LEFT_OPEN, 1, 3, 5));
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_LEFT_OPEN, 1, 5, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_LEFT_OPEN, 1, 1, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_LEFT_OPEN, 1, 0, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_LEFT_OPEN, 1, 6, 5));
}

TEST(eya_interval_contains_value_right_open, integer_values)
{
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_RIGHT_OPEN, 1, 3, 5));
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_RIGHT_OPEN, 1, 1, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_RIGHT_OPEN, 1, 5, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_RIGHT_OPEN, 1, 0, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_RIGHT_OPEN, 1, 6, 5));
}

TEST(eya_interval_contains_value_open, integer_values)
{
    EXPECT_TRUE(eya_interval_contains_value(EYA_INTERVAL_TYPE_OPEN, 1, 3, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_OPEN, 1, 1, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_OPEN, 1, 5, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_OPEN, 1, 0, 5));
    EXPECT_FALSE(eya_interval_contains_value(EYA_INTERVAL_TYPE_OPEN, 1, 6, 5));
}
