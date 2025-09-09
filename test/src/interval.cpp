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

TEST(eya_interval_contains_value_closed, float_values)
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

TEST(eya_interval_cardinality, closed_interval)
{
    EXPECT_EQ(eya_interval_cardinality(EYA_INTERVAL_TYPE_CLOSED, 1, 5), 5);
}

TEST(eya_interval_cardinality, left_open_interval)
{
    EXPECT_EQ(eya_interval_cardinality(EYA_INTERVAL_TYPE_LEFT_OPEN, 1, 5), 4);
}

TEST(eya_interval_cardinality, right_open_interval)
{
    EXPECT_EQ(eya_interval_cardinality(EYA_INTERVAL_TYPE_RIGHT_OPEN, 1, 5), 4);
}

TEST(eya_interval_cardinality, open_interval)
{
    EXPECT_EQ(eya_interval_cardinality(EYA_INTERVAL_TYPE_OPEN, 1, 5), 3);
}

TEST(eya_interval_cardinality, closed_interval_min_equals_max)
{
    EXPECT_EQ(eya_interval_cardinality(EYA_INTERVAL_TYPE_CLOSED, 5, 5), 1);
}

TEST(eya_interval_cardinality, left_open_interval_min_equals_max)
{
    EXPECT_EQ(eya_interval_cardinality(EYA_INTERVAL_TYPE_LEFT_OPEN, 5, 5), 0);
}

TEST(eya_interval_cardinality, right_open_interval_min_equals_max)
{
    EXPECT_EQ(eya_interval_cardinality(EYA_INTERVAL_TYPE_RIGHT_OPEN, 5, 5), 0);
}

TEST(eya_interval_cardinality, open_interval_min_equals_max)
{
    EXPECT_EQ(eya_interval_cardinality(EYA_INTERVAL_TYPE_OPEN, 5, 5), -1);
}

TEST(eya_interval_cardinality, closed_interval_negative_range)
{
    EXPECT_EQ(eya_interval_cardinality(EYA_INTERVAL_TYPE_CLOSED, 5, 1), -3);
}

TEST(eya_interval_cardinality, left_open_interval_negative_range)
{
    EXPECT_EQ(eya_interval_cardinality(EYA_INTERVAL_TYPE_LEFT_OPEN, 5, 1), -4);
}

TEST(eya_interval_cardinality, right_open_interval_negative_range)
{
    EXPECT_EQ(eya_interval_cardinality(EYA_INTERVAL_TYPE_RIGHT_OPEN, 5, 1), -4);
}

TEST(eya_interval_cardinality, open_interval_negative_range)
{
    EXPECT_EQ(eya_interval_cardinality(EYA_INTERVAL_TYPE_OPEN, 5, 1), -5);
}

TEST(eya_interval_cardinality, zero_range_closed)
{
    EXPECT_EQ(eya_interval_cardinality(EYA_INTERVAL_TYPE_CLOSED, 0, 0), 1);
}

TEST(eya_interval_cardinality, large_values_closed)
{
    EXPECT_EQ(eya_interval_cardinality(EYA_INTERVAL_TYPE_CLOSED, 1000000, 1000005), 6);
}

TEST(eya_interval_wrap_around_unsigned, closed_interval)
{
    uint32_t x;
    int      cycles;

    x = 0;
    eya_interval_wrap_around(uint32_t, EYA_INTERVAL_TYPE_CLOSED, x, 0, 9, cycles);
    EXPECT_EQ(x, 0u);
    EXPECT_EQ(cycles, 0);

    x = 9;
    eya_interval_wrap_around(uint32_t, EYA_INTERVAL_TYPE_CLOSED, x, 0, 9, cycles);
    EXPECT_EQ(x, 9u);
    EXPECT_EQ(cycles, 0);

    x = 10;
    eya_interval_wrap_around(uint32_t, EYA_INTERVAL_TYPE_CLOSED, x, 0, 9, cycles);
    EXPECT_EQ(x, 0u);
    EXPECT_EQ(cycles, 1);

    x = 25;
    eya_interval_wrap_around(uint32_t, EYA_INTERVAL_TYPE_CLOSED, x, 0, 9, cycles);
    EXPECT_EQ(x, 5u);
    EXPECT_EQ(cycles, 2);
}

TEST(eya_interval_wrap_around_unsigned, right_open_interval)
{
    uint32_t x;
    int      cycles;

    x = 0;
    eya_interval_wrap_around(uint32_t, EYA_INTERVAL_TYPE_RIGHT_OPEN, x, 0, 10, cycles);
    EXPECT_EQ(x, 0u);
    EXPECT_EQ(cycles, 0);

    x = 9;
    eya_interval_wrap_around(uint32_t, EYA_INTERVAL_TYPE_RIGHT_OPEN, x, 0, 10, cycles);
    EXPECT_EQ(x, 9u);
    EXPECT_EQ(cycles, 0);

    x = 10;
    eya_interval_wrap_around(uint32_t, EYA_INTERVAL_TYPE_RIGHT_OPEN, x, 0, 10, cycles);
    EXPECT_EQ(x, 0u);
    EXPECT_EQ(cycles, 1);

    x = 25;
    eya_interval_wrap_around(uint32_t, EYA_INTERVAL_TYPE_RIGHT_OPEN, x, 0, 10, cycles);
    EXPECT_EQ(x, 5u);
    EXPECT_EQ(cycles, 2);
}

TEST(eya_interval_wrap_around_unsigned, left_open_interval)
{
    uint32_t x;
    int      cycles;

    x = 1;
    eya_interval_wrap_around(uint32_t, EYA_INTERVAL_TYPE_LEFT_OPEN, x, 0, 10, cycles);
    EXPECT_EQ(x, 1u);
    EXPECT_EQ(cycles, 0);

    x = 10;
    eya_interval_wrap_around(uint32_t, EYA_INTERVAL_TYPE_LEFT_OPEN, x, 0, 10, cycles);
    EXPECT_EQ(x, 10u);
    EXPECT_EQ(cycles, 0);

    x = 11;
    eya_interval_wrap_around(uint32_t, EYA_INTERVAL_TYPE_LEFT_OPEN, x, 0, 10, cycles);
    EXPECT_EQ(x, 1u);
    EXPECT_EQ(cycles, 1);
}

TEST(eya_interval_wrap_around_unsigned, open_interval)
{
    uint32_t x;
    int      cycles;

    x = 1;
    eya_interval_wrap_around(uint32_t, EYA_INTERVAL_TYPE_OPEN, x, 0, 9, cycles);
    EXPECT_EQ(x, 1u);
    EXPECT_EQ(cycles, 0);

    x = 8;
    eya_interval_wrap_around(uint32_t, EYA_INTERVAL_TYPE_OPEN, x, 0, 9, cycles);
    EXPECT_EQ(x, 8u);
    EXPECT_EQ(cycles, 0);

    x = 9;
    eya_interval_wrap_around(uint32_t, EYA_INTERVAL_TYPE_OPEN, x, 0, 9, cycles);
    EXPECT_EQ(x, 1u);
    EXPECT_EQ(cycles, 1);

    x = 17;
    eya_interval_wrap_around(uint32_t, EYA_INTERVAL_TYPE_OPEN, x, 0, 9, cycles);
    EXPECT_EQ(x, 1u);
    EXPECT_EQ(cycles, 2);
}

TEST(eya_interval_wrap_around_signed, closed_interval)
{
    int32_t x;
    int     cycles;

    x = -5;
    eya_interval_wrap_around(int32_t, EYA_INTERVAL_TYPE_CLOSED, x, -5, 5, cycles);
    EXPECT_EQ(x, -5);
    EXPECT_EQ(cycles, 0);

    x = 5;
    eya_interval_wrap_around(int32_t, EYA_INTERVAL_TYPE_CLOSED, x, -5, 5, cycles);
    EXPECT_EQ(x, 5);
    EXPECT_EQ(cycles, 0);

    x = 6;
    eya_interval_wrap_around(int32_t, EYA_INTERVAL_TYPE_CLOSED, x, -5, 5, cycles);
    EXPECT_EQ(x, -5);
    EXPECT_EQ(cycles, 1);

    x = 17;
    eya_interval_wrap_around(int32_t, EYA_INTERVAL_TYPE_CLOSED, x, -5, 5, cycles);
    EXPECT_EQ(x, -5);
    EXPECT_EQ(cycles, 2);

    x = -6;
    eya_interval_wrap_around(int32_t, EYA_INTERVAL_TYPE_CLOSED, x, -5, 5, cycles);
    EXPECT_EQ(x, 5);
    EXPECT_EQ(cycles, -1);
}

TEST(eya_interval_wrap_around_signed, right_open_interval)
{
    int32_t x;
    int     cycles;

    x = -5;
    eya_interval_wrap_around(int32_t, EYA_INTERVAL_TYPE_RIGHT_OPEN, x, -5, 6, cycles);
    EXPECT_EQ(x, -5);
    EXPECT_EQ(cycles, 0);

    x = 5;
    eya_interval_wrap_around(int32_t, EYA_INTERVAL_TYPE_RIGHT_OPEN, x, -5, 6, cycles);
    EXPECT_EQ(x, 5);
    EXPECT_EQ(cycles, 0);

    x = 6;
    eya_interval_wrap_around(int32_t, EYA_INTERVAL_TYPE_RIGHT_OPEN, x, -5, 6, cycles);
    EXPECT_EQ(x, -5);
    EXPECT_EQ(cycles, 1);

    x = -6;
    eya_interval_wrap_around(int32_t, EYA_INTERVAL_TYPE_RIGHT_OPEN, x, -5, 6, cycles);
    EXPECT_EQ(x, 5);
    EXPECT_EQ(cycles, -1);
}

TEST(eya_interval_wrap_around_signed, left_open_interval)
{
    int32_t x;
    int     cycles;

    x = -4;
    eya_interval_wrap_around(int32_t, EYA_INTERVAL_TYPE_LEFT_OPEN, x, -5, 5, cycles);
    EXPECT_EQ(x, -4);
    EXPECT_EQ(cycles, 0);

    x = 5;
    eya_interval_wrap_around(int32_t, EYA_INTERVAL_TYPE_LEFT_OPEN, x, -5, 5, cycles);
    EXPECT_EQ(x, 5);
    EXPECT_EQ(cycles, 0);

    x = 6;
    eya_interval_wrap_around(int32_t, EYA_INTERVAL_TYPE_LEFT_OPEN, x, -5, 5, cycles);
    EXPECT_EQ(x, -4);
    EXPECT_EQ(cycles, 1);

    x = -5;
    eya_interval_wrap_around(int32_t, EYA_INTERVAL_TYPE_LEFT_OPEN, x, -5, 5, cycles);
    EXPECT_EQ(x, 5);
    EXPECT_EQ(cycles, -1);
}

TEST(eya_interval_wrap_around_signed, open_interval)
{
    int32_t x;
    int     cycles;

    x = -4;
    eya_interval_wrap_around(int32_t, EYA_INTERVAL_TYPE_OPEN, x, -5, 5, cycles);
    EXPECT_EQ(x, -4);
    EXPECT_EQ(cycles, 0);

    x = 4;
    eya_interval_wrap_around(int32_t, EYA_INTERVAL_TYPE_OPEN, x, -5, 5, cycles);
    EXPECT_EQ(x, 4);
    EXPECT_EQ(cycles, 0);

    x = 5;
    eya_interval_wrap_around(int32_t, EYA_INTERVAL_TYPE_OPEN, x, -5, 5, cycles);
    EXPECT_EQ(x, -4);
    EXPECT_EQ(cycles, 1);

    x = -5;
    eya_interval_wrap_around(int32_t, EYA_INTERVAL_TYPE_OPEN, x, -5, 5, cycles);
    EXPECT_EQ(x, 4);
    EXPECT_EQ(cycles, -1);
}