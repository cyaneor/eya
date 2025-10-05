#include <eya/numeric_interval_util.h>
#include <gtest/gtest.h>

TEST(eya_numeric_interval_contains_value_closed, integer_values)
{
    EXPECT_TRUE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_CLOSED, 1, 3, 5));
    EXPECT_TRUE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_CLOSED, 1, 1, 5));
    EXPECT_TRUE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_CLOSED, 1, 5, 5));
    EXPECT_FALSE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_CLOSED, 1, 0, 5));
    EXPECT_FALSE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_CLOSED, 1, 6, 5));
}

TEST(eya_numeric_interval_contains_value_closed, float_values)
{
    EXPECT_TRUE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_CLOSED, 1.0, 3.0, 5.0));
    EXPECT_TRUE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_CLOSED, 1.0, 1.0, 5.0));
    EXPECT_TRUE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_CLOSED, 1.0, 5.0, 5.0));
    EXPECT_FALSE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_CLOSED, 1.0, 0.9, 5.0));
    EXPECT_FALSE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_CLOSED, 1.0, 5.1, 5.0));
}

TEST(eya_numeric_interval_contains_value_left_open, integer_values)
{
    EXPECT_TRUE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_OPEN_LEFT, 1, 3, 5));
    EXPECT_TRUE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_OPEN_LEFT, 1, 5, 5));
    EXPECT_FALSE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_OPEN_LEFT, 1, 1, 5));
    EXPECT_FALSE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_OPEN_LEFT, 1, 0, 5));
    EXPECT_FALSE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_OPEN_LEFT, 1, 6, 5));
}

TEST(eya_numeric_interval_contains_value_right_open, integer_values)
{
    EXPECT_TRUE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_OPEN_RIGHT, 1, 3, 5));
    EXPECT_TRUE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_OPEN_RIGHT, 1, 1, 5));
    EXPECT_FALSE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_OPEN_RIGHT, 1, 5, 5));
    EXPECT_FALSE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_OPEN_RIGHT, 1, 0, 5));
    EXPECT_FALSE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_OPEN_RIGHT, 1, 6, 5));
}

TEST(eya_numeric_interval_contains_value_open, integer_values)
{
    EXPECT_TRUE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_OPEN, 1, 3, 5));
    EXPECT_FALSE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_OPEN, 1, 1, 5));
    EXPECT_FALSE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_OPEN, 1, 5, 5));
    EXPECT_FALSE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_OPEN, 1, 0, 5));
    EXPECT_FALSE(eya_numeric_interval_contains_value(EYA_INTERVAL_FLAGS_OPEN, 1, 6, 5));
}

TEST(eya_numeric_interval_contains_range_closed, integer_ranges)
{
    EXPECT_TRUE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_CLOSED, 1, 5, 2, 4));
    EXPECT_TRUE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_CLOSED, 1, 5, 1, 5));
    EXPECT_TRUE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_CLOSED, 1, 5, 1, 3));
    EXPECT_TRUE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_CLOSED, 1, 5, 3, 5));

    EXPECT_FALSE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_CLOSED, 1, 5, 0, 3));
    EXPECT_FALSE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_CLOSED, 1, 5, 3, 6));
    EXPECT_FALSE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_CLOSED, 1, 5, 0, 6));
}

TEST(eya_numeric_interval_contains_range_left_open, integer_ranges)
{
    EXPECT_TRUE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_OPEN_LEFT, 1, 5, 2, 4));
    EXPECT_TRUE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_OPEN_LEFT, 1, 5, 2, 5));
    EXPECT_FALSE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_OPEN_LEFT, 1, 5, 1, 5));
    EXPECT_FALSE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_OPEN_LEFT, 1, 5, 0, 3));
}

TEST(eya_numeric_interval_contains_range_right_open, integer_ranges)
{
    EXPECT_TRUE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_OPEN_RIGHT, 1, 5, 2, 4));
    EXPECT_TRUE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_OPEN_RIGHT, 1, 5, 1, 4));
    EXPECT_FALSE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_OPEN_RIGHT, 1, 5, 1, 5));
    EXPECT_FALSE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_OPEN_RIGHT, 1, 5, 3, 6));
}

TEST(eya_numeric_interval_contains_range_open, integer_ranges)
{
    EXPECT_TRUE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_OPEN, 1, 5, 2, 4));
    EXPECT_FALSE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_OPEN, 1, 5, 1, 5));
    EXPECT_FALSE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_OPEN, 1, 5, 1, 4));
    EXPECT_FALSE(eya_numeric_interval_contains_range(EYA_INTERVAL_FLAGS_OPEN, 1, 5, 2, 5));
}

TEST(eya_numeric_interval_capacity, closed_interval)
{
    EXPECT_EQ(eya_numeric_interval_capacity(EYA_INTERVAL_FLAGS_CLOSED, 1, 5), 5);
}

TEST(eya_numeric_interval_capacity, left_open_interval)
{
    EXPECT_EQ(eya_numeric_interval_capacity(EYA_INTERVAL_FLAGS_OPEN_LEFT, 1, 5), 4);
}

TEST(eya_numeric_interval_capacity, right_open_interval)
{
    EXPECT_EQ(eya_numeric_interval_capacity(EYA_INTERVAL_FLAGS_OPEN_RIGHT, 1, 5), 4);
}

TEST(eya_numeric_interval_capacity, open_interval)
{
    EXPECT_EQ(eya_numeric_interval_capacity(EYA_INTERVAL_FLAGS_OPEN, 1, 5), 3);
}

TEST(eya_numeric_interval_capacity, closed_interval_min_equals_max)
{
    EXPECT_EQ(eya_numeric_interval_capacity(EYA_INTERVAL_FLAGS_CLOSED, 5, 5), 1);
}

TEST(eya_numeric_interval_capacity, left_open_interval_min_equals_max)
{
    EXPECT_EQ(eya_numeric_interval_capacity(EYA_INTERVAL_FLAGS_OPEN_LEFT, 5, 5), 0);
}

TEST(eya_numeric_interval_capacity, right_open_interval_min_equals_max)
{
    EXPECT_EQ(eya_numeric_interval_capacity(EYA_INTERVAL_FLAGS_OPEN_RIGHT, 5, 5), 0);
}

TEST(eya_numeric_interval_capacity, open_interval_min_equals_max)
{
    EXPECT_EQ(eya_numeric_interval_capacity(EYA_INTERVAL_FLAGS_OPEN, 5, 5), -1);
}

TEST(eya_numeric_interval_capacity, closed_interval_negative_range)
{
    EXPECT_EQ(eya_numeric_interval_capacity(EYA_INTERVAL_FLAGS_CLOSED, 5, 1), -3);
}

TEST(eya_numeric_interval_capacity, left_open_interval_negative_range)
{
    EXPECT_EQ(eya_numeric_interval_capacity(EYA_INTERVAL_FLAGS_OPEN_LEFT, 5, 1), -4);
}

TEST(eya_numeric_interval_capacity, right_open_interval_negative_range)
{
    EXPECT_EQ(eya_numeric_interval_capacity(EYA_INTERVAL_FLAGS_OPEN_RIGHT, 5, 1), -4);
}

TEST(eya_numeric_interval_capacity, open_interval_negative_range)
{
    EXPECT_EQ(eya_numeric_interval_capacity(EYA_INTERVAL_FLAGS_OPEN, 5, 1), -5);
}

TEST(eya_numeric_interval_capacity, zero_range_closed)
{
    EXPECT_EQ(eya_numeric_interval_capacity(EYA_INTERVAL_FLAGS_CLOSED, 0, 0), 1);
}

TEST(eya_numeric_interval_capacity, large_values_closed)
{
    EXPECT_EQ(eya_numeric_interval_capacity(EYA_INTERVAL_FLAGS_CLOSED, 1000000, 1000005), 6);
}

TEST(eya_numeric_interval_wrap, closed_positive_above_upper_wraps_with_overflow)
{
    unsigned char value    = 25;
    size_t        overflow = 0;

    eya_numeric_interval_wrap(unsigned char, EYA_INTERVAL_FLAGS_CLOSED, 0, 23, value, overflow);

    EXPECT_EQ(overflow, 1);
    EXPECT_EQ(value, 1);
}

TEST(eya_numeric_interval_wrap, closed_positive_upper_bound_no_overflow)
{
    unsigned char value    = 23;
    size_t        overflow = 0;

    eya_numeric_interval_wrap(unsigned char, EYA_INTERVAL_FLAGS_CLOSED, 0, 23, value, overflow);

    EXPECT_EQ(overflow, 0);
    EXPECT_EQ(value, 23);
}

TEST(eya_numeric_interval_wrap, closed_negative_below_lower_wraps_with_overflow)
{
    signed char value    = -1;
    size_t      overflow = 0;

    eya_numeric_interval_wrap(unsigned char, EYA_INTERVAL_FLAGS_CLOSED, 0, 23, value, overflow);

    EXPECT_EQ(overflow, 1);
    EXPECT_EQ(value, 23);
}

TEST(eya_numeric_interval_wrap, closed_negative_far_below_lower_wraps_multiple_times)
{
    signed char value    = -25;
    size_t      overflow = 0;

    eya_numeric_interval_wrap(unsigned char, EYA_INTERVAL_FLAGS_CLOSED, 0, 23, value, overflow);

    EXPECT_EQ(overflow, 2);
    EXPECT_EQ(value, 23);
}

TEST(eya_numeric_interval_wrap, closed_positive_above_upper_with_negative_bounds)
{
    signed char value    = 6;
    signed char overflow = 0;

    eya_numeric_interval_wrap(signed char, EYA_INTERVAL_FLAGS_CLOSED, -10, 5, value, overflow);

    EXPECT_EQ(overflow, 1);
    EXPECT_EQ(value, -10);
}

TEST(eya_numeric_interval_wrap, closed_negative_below_lower_with_negative_bounds)
{
    signed char value    = -11;
    signed char overflow = 0;

    eya_numeric_interval_wrap(signed char, EYA_INTERVAL_FLAGS_CLOSED, -10, 5, value, overflow);

    EXPECT_EQ(overflow, 1);
    EXPECT_EQ(value, 5);
}

TEST(eya_numeric_interval_wrap, closed_negative_far_below_lower_wraps_twice)
{
    signed char value    = -27;
    signed char overflow = 0;

    eya_numeric_interval_wrap(signed char, EYA_INTERVAL_FLAGS_CLOSED, -10, 5, value, overflow);

    EXPECT_EQ(overflow, 2);
    EXPECT_EQ(value, 5);
}

TEST(eya_numeric_interval_wrap, closed_positive_far_above_upper_wraps_twice)
{
    signed char value    = 22;
    signed char overflow = 0;

    eya_numeric_interval_wrap(signed char, EYA_INTERVAL_FLAGS_CLOSED, -10, 5, value, overflow);

    EXPECT_EQ(overflow, 2);
    EXPECT_EQ(value, -10);
}

TEST(eya_numeric_interval_wrap, open_left_excludes_lower_bound)
{
    signed char value    = 0;
    signed char overflow = 0;

    eya_numeric_interval_wrap(signed char, EYA_INTERVAL_FLAGS_OPEN_LEFT, 0, 10, value, overflow);
    EXPECT_EQ(overflow, 1);
    EXPECT_EQ(value, 10);
}

TEST(eya_numeric_interval_wrap, open_left_includes_upper_bound)
{
    signed char value    = 10;
    signed char overflow = 0;

    eya_numeric_interval_wrap(signed char, EYA_INTERVAL_FLAGS_OPEN_LEFT, 0, 10, value, overflow);
    EXPECT_EQ(overflow, 0);
    EXPECT_EQ(value, 10);
}

TEST(eya_numeric_interval_wrap, open_left_above_upper_wraps)
{
    signed char value    = 15;
    signed char overflow = 0;

    eya_numeric_interval_wrap(signed char, EYA_INTERVAL_FLAGS_OPEN_LEFT, 0, 10, value, overflow);
    EXPECT_EQ(overflow, 1);
    EXPECT_EQ(value, 5);
}

TEST(eya_numeric_interval_wrap, open_right_excludes_upper_bound)
{
    signed char value    = 10;
    signed char overflow = 0;

    eya_numeric_interval_wrap(signed char, EYA_INTERVAL_FLAGS_OPEN_RIGHT, 0, 10, value, overflow);
    EXPECT_EQ(overflow, 1);
    EXPECT_EQ(value, 0);
}

TEST(eya_numeric_interval_wrap, open_right_includes_lower_bound)
{
    signed char value    = 0;
    signed char overflow = 0;

    eya_numeric_interval_wrap(signed char, EYA_INTERVAL_FLAGS_OPEN_RIGHT, 0, 10, value, overflow);
    EXPECT_EQ(overflow, 0);
    EXPECT_EQ(value, 0);
}

TEST(eya_numeric_interval_wrap, open_right_below_lower_wraps)
{
    signed char value    = -5;
    signed char overflow = 0;

    eya_numeric_interval_wrap(signed char, EYA_INTERVAL_FLAGS_OPEN_RIGHT, 0, 10, value, overflow);
    EXPECT_EQ(overflow, 1);
    EXPECT_EQ(value, 5);
}

TEST(eya_numeric_interval_wrap, open_excludes_both_bounds)
{
    signed char value    = 0;
    signed char overflow = 0;

    eya_numeric_interval_wrap(signed char, EYA_INTERVAL_FLAGS_OPEN, 0, 10, value, overflow);
    EXPECT_EQ(overflow, 1);
    EXPECT_EQ(value, 9);
}

TEST(eya_numeric_interval_wrap, open_excludes_upper_bound)
{
    signed char value    = 10;
    signed char overflow = 0;

    eya_numeric_interval_wrap(signed char, EYA_INTERVAL_FLAGS_OPEN, 0, 10, value, overflow);
    EXPECT_EQ(overflow, 1);
    EXPECT_EQ(value, 1);
}

TEST(eya_numeric_interval_wrap, open_valid_internal_value)
{
    signed char value    = 5;
    signed char overflow = 0;

    eya_numeric_interval_wrap(signed char, EYA_INTERVAL_FLAGS_OPEN, 0, 10, value, overflow);
    EXPECT_EQ(overflow, 0);
    EXPECT_EQ(value, 5);
}

TEST(eya_numeric_interval_wrap, open_negative_bounds_excludes_lower)
{
    signed char value    = -5;
    signed char overflow = 0;

    eya_numeric_interval_wrap(signed char, EYA_INTERVAL_FLAGS_OPEN_LEFT, -5, 5, value, overflow);
    EXPECT_EQ(overflow, 1);
    EXPECT_EQ(value, 5);
}

TEST(eya_numeric_interval_wrap, open_negative_bounds_excludes_upper)
{
    signed char value    = 5;
    signed char overflow = 0;

    eya_numeric_interval_wrap(signed char, EYA_INTERVAL_FLAGS_OPEN_RIGHT, -5, 5, value, overflow);
    EXPECT_EQ(overflow, 1);
    EXPECT_EQ(value, -5);
}

TEST(eya_numeric_interval_wrap, fully_open_negative_bounds)
{
    signed char value    = -5;
    signed char overflow = 0;

    eya_numeric_interval_wrap(signed char, EYA_INTERVAL_FLAGS_OPEN, -5, 5, value, overflow);
    EXPECT_EQ(overflow, 1);
    EXPECT_EQ(value, 4);
}