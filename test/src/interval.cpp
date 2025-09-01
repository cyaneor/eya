#include <gtest/gtest.h>
#include <eya/interval_util.h>

TEST(eya_interval_closed_is_valid, valid_and_invalid_intervals)
{
    EXPECT_TRUE(eya_interval_closed_is_valid(1, 5));
    EXPECT_TRUE(eya_interval_closed_is_valid(0, 0));
    EXPECT_TRUE(eya_interval_closed_is_valid(-5, -1));
    EXPECT_TRUE(eya_interval_closed_is_valid(1.0, 5.0));
    EXPECT_TRUE(eya_interval_closed_is_valid(0.0, 0.0));

    EXPECT_FALSE(eya_interval_closed_is_valid(5, 1));
    EXPECT_FALSE(eya_interval_closed_is_valid(5.0, 1.0));
}

TEST(eya_interval_lopen_is_valid, valid_and_invalid_intervals)
{
    EXPECT_TRUE(eya_interval_lopen_is_valid(1, 5));
    EXPECT_TRUE(eya_interval_lopen_is_valid(-5, -1));
    EXPECT_TRUE(eya_interval_lopen_is_valid(1.0, 5.0));

    EXPECT_FALSE(eya_interval_lopen_is_valid(5, 5));
    EXPECT_FALSE(eya_interval_lopen_is_valid(5, 1));
    EXPECT_FALSE(eya_interval_lopen_is_valid(5.0, 5.0));
    EXPECT_FALSE(eya_interval_lopen_is_valid(5.0, 1.0));
}

TEST(eya_interval_ropen_is_valid, valid_and_invalid_intervals)
{
    EXPECT_TRUE(eya_interval_ropen_is_valid(1, 5));
    EXPECT_TRUE(eya_interval_ropen_is_valid(-5, -1));
    EXPECT_TRUE(eya_interval_ropen_is_valid(1.0, 5.0));

    EXPECT_FALSE(eya_interval_ropen_is_valid(5, 5));
    EXPECT_FALSE(eya_interval_ropen_is_valid(5, 1));
    EXPECT_FALSE(eya_interval_ropen_is_valid(5.0, 5.0));
    EXPECT_FALSE(eya_interval_ropen_is_valid(5.0, 1.0));
}

TEST(eya_interval_open_is_valid, valid_and_invalid_intervals)
{
    EXPECT_TRUE(eya_interval_open_is_valid(1, 5));
    EXPECT_TRUE(eya_interval_open_is_valid(-5, -1));
    EXPECT_TRUE(eya_interval_open_is_valid(1.0, 5.0));

    EXPECT_FALSE(eya_interval_open_is_valid(5, 5));
    EXPECT_FALSE(eya_interval_open_is_valid(5, 1));
    EXPECT_FALSE(eya_interval_open_is_valid(5.0, 5.0));
    EXPECT_FALSE(eya_interval_open_is_valid(5.0, 1.0));
}

TEST(eya_interval_closed_contains_value, integer_and_float_values)
{
    EXPECT_TRUE(eya_interval_closed_contains_value(1, 5, 3));
    EXPECT_TRUE(eya_interval_closed_contains_value(1, 5, 1));
    EXPECT_TRUE(eya_interval_closed_contains_value(1, 5, 5));
    EXPECT_FALSE(eya_interval_closed_contains_value(1, 5, 0));
    EXPECT_FALSE(eya_interval_closed_contains_value(1, 5, 6));

    EXPECT_TRUE(eya_interval_closed_contains_value(1.0, 5.0, 3.0));
    EXPECT_TRUE(eya_interval_closed_contains_value(1.0, 5.0, 1.0));
    EXPECT_TRUE(eya_interval_closed_contains_value(1.0, 5.0, 5.0));
    EXPECT_FALSE(eya_interval_closed_contains_value(1.0, 5.0, 0.9));
    EXPECT_FALSE(eya_interval_closed_contains_value(1.0, 5.0, 5.1));
}

TEST(eya_interval_lopen_contains_value, integer_and_float_values)
{
    EXPECT_TRUE(eya_interval_lopen_contains_value(1, 5, 3));
    EXPECT_TRUE(eya_interval_lopen_contains_value(1, 5, 5));
    EXPECT_FALSE(eya_interval_lopen_contains_value(1, 5, 1));
    EXPECT_FALSE(eya_interval_lopen_contains_value(1, 5, 0));
    EXPECT_FALSE(eya_interval_lopen_contains_value(1, 5, 6));

    EXPECT_TRUE(eya_interval_lopen_contains_value(1.0, 5.0, 3.0));
    EXPECT_TRUE(eya_interval_lopen_contains_value(1.0, 5.0, 5.0));
    EXPECT_FALSE(eya_interval_lopen_contains_value(1.0, 5.0, 1.0));
    EXPECT_FALSE(eya_interval_lopen_contains_value(1.0, 5.0, 0.9));
    EXPECT_FALSE(eya_interval_lopen_contains_value(1.0, 5.0, 5.1));
}

TEST(eya_interval_ropen_contains_value, integer_and_float_values)
{
    EXPECT_TRUE(eya_interval_ropen_contains_value(1, 5, 3));
    EXPECT_TRUE(eya_interval_ropen_contains_value(1, 5, 1));
    EXPECT_FALSE(eya_interval_ropen_contains_value(1, 5, 5));
    EXPECT_FALSE(eya_interval_ropen_contains_value(1, 5, 0));
    EXPECT_FALSE(eya_interval_ropen_contains_value(1, 5, 6));

    EXPECT_TRUE(eya_interval_ropen_contains_value(1.0, 5.0, 3.0));
    EXPECT_TRUE(eya_interval_ropen_contains_value(1.0, 5.0, 1.0));
    EXPECT_FALSE(eya_interval_ropen_contains_value(1.0, 5.0, 5.0));
    EXPECT_FALSE(eya_interval_ropen_contains_value(1.0, 5.0, 0.9));
    EXPECT_FALSE(eya_interval_ropen_contains_value(1.0, 5.0, 5.1));
}

TEST(eya_interval_open_contains_value, integer_and_float_values)
{
    EXPECT_TRUE(eya_interval_open_contains_value(1, 5, 3));
    EXPECT_FALSE(eya_interval_open_contains_value(1, 5, 1));
    EXPECT_FALSE(eya_interval_open_contains_value(1, 5, 5));
    EXPECT_FALSE(eya_interval_open_contains_value(1, 5, 0));
    EXPECT_FALSE(eya_interval_open_contains_value(1, 5, 6));

    EXPECT_TRUE(eya_interval_open_contains_value(1.0, 5.0, 3.0));
    EXPECT_FALSE(eya_interval_open_contains_value(1.0, 5.0, 1.0));
    EXPECT_FALSE(eya_interval_open_contains_value(1.0, 5.0, 5.0));
    EXPECT_FALSE(eya_interval_open_contains_value(1.0, 5.0, 0.9));
    EXPECT_FALSE(eya_interval_open_contains_value(1.0, 5.0, 5.1));
}

TEST(eya_interval_closed_contains_range, valid_and_invalid_ranges)
{
    EXPECT_TRUE(eya_interval_closed_contains_range(1, 10, 2, 8));
    EXPECT_TRUE(eya_interval_closed_contains_range(1, 10, 1, 10));
    EXPECT_TRUE(eya_interval_closed_contains_range(1.0, 10.0, 2.0, 8.0));

    EXPECT_FALSE(eya_interval_closed_contains_range(1, 5, 0, 6));
    EXPECT_FALSE(eya_interval_closed_contains_range(1, 5, 2, 6));
    EXPECT_FALSE(eya_interval_closed_contains_range(1.0, 5.0, 0.0, 6.0));
}

TEST(eya_interval_lopen_contains_range, valid_and_invalid_ranges)
{
    EXPECT_TRUE(eya_interval_lopen_contains_range(1, 10, 2, 8));
    EXPECT_TRUE(eya_interval_lopen_contains_range(1, 10, 2, 10));
    EXPECT_TRUE(eya_interval_lopen_contains_range(1.0, 10.0, 2.0, 8.0));

    EXPECT_FALSE(eya_interval_lopen_contains_range(1, 5, 1, 5));
    EXPECT_FALSE(eya_interval_lopen_contains_range(1, 5, 0, 6));
    EXPECT_FALSE(eya_interval_lopen_contains_range(1.0, 5.0, 1.0, 5.0));
}

TEST(eya_interval_ropen_contains_range, valid_and_invalid_ranges)
{
    EXPECT_TRUE(eya_interval_ropen_contains_range(1, 10, 2, 8));
    EXPECT_TRUE(eya_interval_ropen_contains_range(1, 10, 1, 8));
    EXPECT_TRUE(eya_interval_ropen_contains_range(1.0, 10.0, 2.0, 8.0));

    EXPECT_FALSE(eya_interval_ropen_contains_range(1, 5, 2, 5));
    EXPECT_FALSE(eya_interval_ropen_contains_range(1, 5, 0, 6));
    EXPECT_FALSE(eya_interval_ropen_contains_range(1.0, 5.0, 2.0, 5.0));
}

TEST(eya_interval_open_contains_range, valid_and_invalid_ranges)
{
    EXPECT_TRUE(eya_interval_open_contains_range(1, 10, 2, 8));
    EXPECT_TRUE(eya_interval_open_contains_range(1.0, 10.0, 2.0, 8.0));

    EXPECT_FALSE(eya_interval_open_contains_range(1, 5, 1, 5));
    EXPECT_FALSE(eya_interval_open_contains_range(1, 5, 2, 5));
    EXPECT_FALSE(eya_interval_open_contains_range(1, 5, 0, 6));
    EXPECT_FALSE(eya_interval_open_contains_range(1.0, 5.0, 1.0, 5.0));
}