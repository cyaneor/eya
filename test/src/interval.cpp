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

TEST(eya_interval_size, closed_interval)
{
    int min = 1;
    int max = 5;
    EXPECT_EQ(eya_interval_size(EYA_INTERVAL_TYPE_CLOSED, min, max), 5);
}

TEST(eya_interval_size, left_open_interval)
{
    int min = 1;
    int max = 5;
    EXPECT_EQ(eya_interval_size(EYA_INTERVAL_TYPE_LEFT_OPEN, min, max), 4);
}

TEST(eya_interval_size, right_open_interval)
{
    int min = 1;
    int max = 5;
    EXPECT_EQ(eya_interval_size(EYA_INTERVAL_TYPE_RIGHT_OPEN, min, max), 4);
}

TEST(eya_interval_size, open_interval)
{
    int min = 1;
    int max = 5;
    EXPECT_EQ(eya_interval_size(EYA_INTERVAL_TYPE_OPEN, min, max), 3);
}

TEST(eya_interval_size, invalid_interval_type)
{
    EXPECT_EQ(eya_interval_size(999, 1, 5), 0);
}

TEST(eya_interval_size, closed_interval_min_equals_max)
{
    int min = 5;
    int max = 5;
    EXPECT_EQ(eya_interval_size(EYA_INTERVAL_TYPE_CLOSED, min, max), 1);
}

TEST(eya_interval_size, left_open_interval_min_equals_max)
{
    int min = 5;
    int max = 5;
    EXPECT_EQ(eya_interval_size(EYA_INTERVAL_TYPE_LEFT_OPEN, min, max), 0);
}

TEST(eya_interval_size, right_open_interval_min_equals_max)
{
    int min = 5;
    int max = 5;
    EXPECT_EQ(eya_interval_size(EYA_INTERVAL_TYPE_RIGHT_OPEN, min, max), 0);
}

TEST(eya_interval_size, open_interval_min_equals_max)
{
    int min = 5;
    int max = 5;
    EXPECT_EQ(eya_interval_size(EYA_INTERVAL_TYPE_OPEN, min, max), -1);
}

TEST(eya_interval_size, closed_interval_negative_range)
{
    int min = 5;
    int max = 1;
    EXPECT_EQ(eya_interval_size(EYA_INTERVAL_TYPE_CLOSED, min, max), -3);
}

TEST(eya_interval_size, left_open_interval_negative_range)
{
    int min = 5;
    int max = 1;
    EXPECT_EQ(eya_interval_size(EYA_INTERVAL_TYPE_LEFT_OPEN, min, max), -4);
}

TEST(eya_interval_size, right_open_interval_negative_range)
{
    int min = 5;
    int max = 1;
    EXPECT_EQ(eya_interval_size(EYA_INTERVAL_TYPE_RIGHT_OPEN, min, max), -4);
}

TEST(eya_interval_size, open_interval_negative_range)
{
    int min = 5;
    int max = 1;
    EXPECT_EQ(eya_interval_size(EYA_INTERVAL_TYPE_OPEN, min, max), -5);
}

TEST(eya_interval_size, zero_range_closed)
{
    int min = 0;
    int max = 0;
    EXPECT_EQ(eya_interval_size(EYA_INTERVAL_TYPE_CLOSED, min, max), 1);
}

TEST(eya_interval_size, large_values_closed)
{
    int min = 1000000;
    int max = 1000005;
    EXPECT_EQ(eya_interval_size(EYA_INTERVAL_TYPE_CLOSED, min, max), 6);
}