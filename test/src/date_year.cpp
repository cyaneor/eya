#include <eya/date_year.h>
#include <gtest/gtest.h>

TEST(eya_date_year_is_leap, gregorian_calendar)
{
    EXPECT_FALSE(eya_date_year_is_leap(2023));
    EXPECT_FALSE(eya_date_year_is_leap(1901));

    EXPECT_TRUE(eya_date_year_is_leap(2024));
    EXPECT_TRUE(eya_date_year_is_leap(2004));
    EXPECT_TRUE(eya_date_year_is_leap(1996));

    EXPECT_FALSE(eya_date_year_is_leap(1900));
    EXPECT_FALSE(eya_date_year_is_leap(2100));
    EXPECT_FALSE(eya_date_year_is_leap(1800));

    EXPECT_TRUE(eya_date_year_is_leap(2000));
    EXPECT_TRUE(eya_date_year_is_leap(1600));
    EXPECT_TRUE(eya_date_year_is_leap(2400));
}