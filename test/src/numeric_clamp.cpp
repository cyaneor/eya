#include <eya/numeric_clamp.h>
#include <gtest/gtest.h>

TEST(eya_numeric_clamp_ropen, within_range)
{
    int value = 5, overflow = 0;
    eya_numeric_clamp_ropen(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 5);
    EXPECT_EQ(overflow, 0);
}

TEST(eya_numeric_clamp_ropen, positive_overflow)
{
    int value = 25, overflow = 0;
    eya_numeric_clamp_ropen(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 5);
    EXPECT_EQ(overflow, 2);
}

TEST(eya_numeric_clamp_ropen, negative_overflow)
{
    int value = -5, overflow = 0;
    eya_numeric_clamp_ropen(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 5);
    EXPECT_EQ(overflow, -1);
}

TEST(eya_numeric_clamp_ropen, boundaries)
{
    int value = 0, overflow = 0;
    eya_numeric_clamp_ropen(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 0);
    EXPECT_EQ(overflow, 0);

    value = 9;
    eya_numeric_clamp_ropen(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 9);
    EXPECT_EQ(overflow, 0);
}

TEST(eya_numeric_clamp_ropen, large_positive)
{
    int value = 12345, overflow = 0;
    eya_numeric_clamp_ropen(int, value, 0, 100, overflow, 0);
    EXPECT_EQ(value, 45);
    EXPECT_EQ(overflow, 123);
}

TEST(eya_numeric_clamp_ropen, large_negative)
{
    int value = -12345, overflow = 0;
    eya_numeric_clamp_ropen(int, value, 0, 100, overflow, 0);
    EXPECT_EQ(value, 55);
    EXPECT_EQ(overflow, -124);
}

TEST(eya_numeric_clamp_ropen, unsigned_int)
{
    unsigned int value = 25, overflow = 0;
    eya_numeric_clamp_ropen(unsigned int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 5u);
    EXPECT_EQ(overflow, 2);
}

TEST(eya_numeric_clamp_ropen, negative_range)
{
    int value = -15, overflow = 0;
    eya_numeric_clamp_ropen(int, value, -20, -10, overflow, 0);
    EXPECT_EQ(value, -15);
    EXPECT_EQ(overflow, 0);

    value = -25;
    eya_numeric_clamp_ropen(int, value, -20, -10, overflow, 0);
    EXPECT_EQ(value, -15);
    EXPECT_EQ(overflow, -1);
}

TEST(numeric_clamp_closed, within_range)
{
    int value = 5, overflow = 0;
    eya_numeric_clamp_closed(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 5);
    EXPECT_EQ(overflow, 0);
}

TEST(numeric_clamp_closed, lower_boundary)
{
    int value = 0, overflow = 0;
    eya_numeric_clamp_closed(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 0);
    EXPECT_EQ(overflow, 0);
}

TEST(numeric_clamp_closed, upper_boundary)
{
    int value = 10, overflow = 0;
    eya_numeric_clamp_closed(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 10);
    EXPECT_EQ(overflow, 0);
}

TEST(numeric_clamp_closed, positive_overflow)
{
    int value = 25, overflow = 0;
    eya_numeric_clamp_closed(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 3);
    EXPECT_EQ(overflow, 2);
}

TEST(numeric_clamp_closed, negative_overflow)
{
    int value = -5, overflow = 0;
    eya_numeric_clamp_closed(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 6);
    EXPECT_EQ(overflow, -1);
}

TEST(numeric_clamp_closed, single_value_range)
{
    int value = 5, overflow = 0;
    eya_numeric_clamp_closed(int, value, 5, 5, overflow, 0);
    EXPECT_EQ(value, 5);
    EXPECT_EQ(overflow, 0);

    value = 6;
    eya_numeric_clamp_closed(int, value, 5, 5, overflow, 0);
    EXPECT_EQ(value, 5);
    EXPECT_EQ(overflow, 1);

    value = 4;
    eya_numeric_clamp_closed(int, value, 5, 5, overflow, 0);
    EXPECT_EQ(value, 5);
    EXPECT_EQ(overflow, -1);
}

TEST(numeric_clamp_lopen, within_range)
{
    int value = 5, overflow = 0;
    eya_numeric_clamp_lopen(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 5);
    EXPECT_EQ(overflow, 0);
}

TEST(numeric_clamp_lopen, lower_boundary)
{
    int value = 0, overflow = 0;
    eya_numeric_clamp_lopen(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 10);
    EXPECT_EQ(overflow, -1);
}

TEST(numeric_clamp_lopen, upper_boundary)
{
    int value = 10, overflow = 0;
    eya_numeric_clamp_lopen(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 10);
    EXPECT_EQ(overflow, 0);
}

TEST(numeric_clamp_lopen, positive_overflow)
{
    int value = 25, overflow = 0;
    eya_numeric_clamp_lopen(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 5);
    EXPECT_EQ(overflow, 2);
}

TEST(numeric_clamp_lopen, negative_overflow)
{
    int value = -5, overflow = 0;
    eya_numeric_clamp_lopen(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 5);
    EXPECT_EQ(overflow, -1);
}

TEST(numeric_clamp_open, within_range)
{
    int value = 5, overflow = 0;
    eya_numeric_clamp_open(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 5);
    EXPECT_EQ(overflow, 0);
}

TEST(numeric_clamp_open, lower_boundary)
{
    int value = 0, overflow = 0;
    eya_numeric_clamp_open(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 9);
    EXPECT_EQ(overflow, -1);
}

TEST(numeric_clamp_open, upper_boundary)
{
    int value = 10, overflow = 0;
    eya_numeric_clamp_open(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(overflow, 1);
}

TEST(numeric_clamp_open, positive_overflow)
{
    int value = 25, overflow = 0;
    eya_numeric_clamp_open(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 7);
    EXPECT_EQ(overflow, 2);
}

TEST(numeric_clamp_open, negative_overflow)
{
    int value = -5, overflow = 0;
    eya_numeric_clamp_open(int, value, 0, 10, overflow, 0);
    EXPECT_EQ(value, 4);
    EXPECT_EQ(overflow, -1);
}