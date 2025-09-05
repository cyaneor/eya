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

TEST(eya_interval_closed_add, integer_values_with_overflow)
{
    int value = 3;
    int overflow;

    eya_interval_closed_add(int, value, 5, 1, 10, overflow);
    EXPECT_EQ(value, 8);
    EXPECT_EQ(overflow, 0);

    value = 8;
    eya_interval_closed_add(int, value, 5, 1, 10, overflow);
    EXPECT_EQ(value, 3);
    EXPECT_EQ(overflow, 1);
}

TEST(eya_interval_ropen_add, integer_values_with_overflow)
{
    int value = 3;
    int overflow;

    eya_interval_ropen_add(int, value, 5, 1, 10, overflow);
    EXPECT_EQ(value, 8);
    EXPECT_EQ(overflow, 0);

    value = 8;
    eya_interval_ropen_add(int, value, 5, 1, 10, overflow);
    EXPECT_EQ(value, 4);
    EXPECT_EQ(overflow, 1);
}

TEST(eya_interval_lopen_add, integer_values_with_overflow)
{
    int value = 4;
    int overflow;

    eya_interval_lopen_add(int, value, 5, 1, 10, overflow);
    EXPECT_EQ(value, 9);
    EXPECT_EQ(overflow, 0);

    value = 9;
    eya_interval_lopen_add(int, value, 5, 1, 10, overflow);
    EXPECT_EQ(value, 5);
    EXPECT_EQ(overflow, 1);
}

TEST(eya_interval_open_add, integer_values_with_overflow)
{
    int value = 4;
    int overflow;

    eya_interval_open_add(int, value, 5, 1, 10, overflow);
    EXPECT_EQ(value, 9);
    EXPECT_EQ(overflow, 0);

    value = 9;
    eya_interval_open_add(int, value, 5, 1, 10, overflow);
    EXPECT_EQ(value, 6);
    EXPECT_EQ(overflow, 1);
}

TEST(eya_interval_closed_sub, integer_values_with_overflow)
{
    int value = 8;
    int overflow;

    eya_interval_closed_sub(int, value, 5, 1, 10, overflow);
    EXPECT_EQ(value, 3);
    EXPECT_EQ(overflow, 0);

    value = 3;
    eya_interval_closed_sub(int, value, 5, 1, 10, overflow);
    EXPECT_EQ(value, 8);
    EXPECT_EQ(overflow, -1);
}

TEST(eya_interval_ropen_sub, integer_values_with_overflow)
{
    int value = 8;
    int overflow;

    eya_interval_ropen_sub(int, value, 5, 1, 10, overflow);
    EXPECT_EQ(value, 3);
    EXPECT_EQ(overflow, 0);

    value = 3;
    eya_interval_ropen_sub(int, value, 5, 1, 10, overflow);
    EXPECT_EQ(value, 7);
    EXPECT_EQ(overflow, -1);
}

TEST(eya_interval_lopen_sub, integer_values_with_overflow)
{
    int value = 9;
    int overflow;

    eya_interval_lopen_sub(int, value, 5, 1, 10, overflow);
    EXPECT_EQ(value, 4);
    EXPECT_EQ(overflow, 0);

    value = 4;
    eya_interval_lopen_sub(int, value, 5, 1, 10, overflow);
    EXPECT_EQ(value, 8);
    EXPECT_EQ(overflow, -1);
}

TEST(eya_interval_open_sub, integer_values_with_overflow)
{
    int value = 9;
    int overflow;

    eya_interval_open_sub(int, value, 5, 1, 10, overflow);
    EXPECT_EQ(value, 4);
    EXPECT_EQ(overflow, 0);

    value = 4;
    eya_interval_open_sub(int, value, 5, 1, 10, overflow);
    EXPECT_EQ(value, 7);
    EXPECT_EQ(overflow, -1);
}

TEST(eya_interval_closed_mul, integer_values_with_overflow)
{
    int value = 3;
    int overflow;

    eya_interval_closed_mul(int, value, 2, 1, 10, overflow);
    EXPECT_EQ(value, 6);
    EXPECT_EQ(overflow, 0);

    value = 6;
    eya_interval_closed_mul(int, value, 2, 1, 10, overflow);
    EXPECT_EQ(value, 2);
    EXPECT_EQ(overflow, 1);
}

TEST(eya_interval_ropen_mul, integer_values_with_overflow)
{
    int value = 3;
    int overflow;

    eya_interval_ropen_mul(int, value, 2, 1, 10, overflow);
    EXPECT_EQ(value, 6);
    EXPECT_EQ(overflow, 0);

    value = 6;
    eya_interval_ropen_mul(int, value, 2, 1, 10, overflow);
    EXPECT_EQ(value, 3);
    EXPECT_EQ(overflow, 1);
}

TEST(eya_interval_lopen_mul, integer_values_with_overflow)
{
    int value = 4;
    int overflow;

    eya_interval_lopen_mul(int, value, 2, 1, 10, overflow);
    EXPECT_EQ(value, 8);
    EXPECT_EQ(overflow, 0);

    value = 8;
    eya_interval_lopen_mul(int, value, 2, 1, 10, overflow);
    EXPECT_EQ(value, 7);
    EXPECT_EQ(overflow, 1);
}

TEST(eya_interval_open_mul, integer_values_with_overflow)
{
    int value = 4;
    int overflow;

    eya_interval_open_mul(int, value, 2, 1, 10, overflow);
    EXPECT_EQ(value, 8);
    EXPECT_EQ(overflow, 0);

    value = 8;
    eya_interval_open_mul(int, value, 2, 1, 10, overflow);
    EXPECT_EQ(value, 8);
    EXPECT_EQ(overflow, 1);
}

TEST(eya_interval_closed_div, integer_values_with_overflow)
{
    int value = 8;
    int overflow;

    eya_interval_closed_div(int, value, 2, 1, 10, overflow);
    EXPECT_EQ(value, 4);
    EXPECT_EQ(overflow, 0);

    value = 20;
    eya_interval_closed_div(int, value, 2, 1, 10, overflow);
    EXPECT_EQ(value, 10);
    EXPECT_EQ(overflow, 0);
}

TEST(eya_interval_ropen_div, integer_values_with_overflow)
{
    int value = 8;
    int overflow;

    eya_interval_ropen_div(int, value, 2, 1, 10, overflow);
    EXPECT_EQ(value, 4);
    EXPECT_EQ(overflow, 0);

    value = 20;
    eya_interval_ropen_div(int, value, 2, 1, 10, overflow);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(overflow, 1);
}

TEST(eya_interval_lopen_div, integer_values_with_overflow)
{
    int value = 8;
    int overflow;

    eya_interval_lopen_div(int, value, 2, 1, 10, overflow);
    EXPECT_EQ(value, 4);
    EXPECT_EQ(overflow, 0);

    value = 3;
    eya_interval_lopen_div(int, value, 2, 1, 10, overflow);
    EXPECT_EQ(value, 10);
    EXPECT_EQ(overflow, -1);
}

TEST(eya_interval_open_div, integer_values_with_overflow)
{
    int value = 8;
    int overflow;

    eya_interval_open_div(int, value, 2, 1, 10, overflow);
    EXPECT_EQ(value, 4);
    EXPECT_EQ(overflow, 0);

    value = 3;
    eya_interval_open_div(int, value, 2, 1, 10, overflow);
    EXPECT_EQ(value, 9);
    EXPECT_EQ(overflow, -1);
}

TEST(eya_interval_closed_add, edge_cases_and_zero_values)
{
    int value = 1;
    int overflow;

    eya_interval_closed_add(int, value, 0, 1, 10, overflow);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(overflow, 0);

    value = 10;
    eya_interval_closed_add(int, value, 1, 1, 10, overflow);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(overflow, 1);
}

TEST(eya_interval_ropen_add, edge_cases_and_zero_values)
{
    int value = 1;
    int overflow;

    eya_interval_ropen_add(int, value, 0, 1, 10, overflow);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(overflow, 0);

    value = 9;
    eya_interval_ropen_add(int, value, 1, 1, 10, overflow);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(overflow, 1);
}

TEST(eya_interval_operations, negative_values_and_ranges)
{
    int value = -3;
    int overflow;

    eya_interval_closed_add(int, value, 5, -5, 5, overflow);
    EXPECT_EQ(value, 2);
    EXPECT_EQ(overflow, 0);

    value = 3;
    eya_interval_closed_add(int, value, -5, -5, 5, overflow);
    EXPECT_EQ(value, -2);
    EXPECT_EQ(overflow, 0);
}