#include <eya/numeric_limits.h>
#include <gtest/gtest.h>

TEST(eya_numeric_limits, char_type_size)
{
    EXPECT_EQ(sizeof(char), EYA_CHAR_T_SIZE);
}

TEST(eya_numeric_limits, short_type_size)
{
    EXPECT_EQ(sizeof(short), EYA_SHORT_T_SIZE);
}

TEST(eya_numeric_limits, int_type_size)
{
    EXPECT_EQ(sizeof(int), EYA_INT_T_SIZE);
}

TEST(eya_numeric_limits, long_type_size)
{
    EXPECT_EQ(sizeof(long), EYA_LONG_T_SIZE);
}

TEST(eya_numeric_limits, llong_type_size)
{
    EXPECT_EQ(sizeof(long long), EYA_LLONG_T_SIZE);
}

TEST(eya_numeric_limits, uchar_type_limits)
{
    EXPECT_EQ(std::numeric_limits<unsigned char>::min(), EYA_UCHAR_T_MIN);
    EXPECT_EQ(std::numeric_limits<unsigned char>::max(), EYA_UCHAR_T_MAX);
}

TEST(eya_numeric_limits, ushort_type_limits)
{
    EXPECT_EQ(std::numeric_limits<unsigned short>::min(), EYA_USHORT_T_MIN);
    EXPECT_EQ(std::numeric_limits<unsigned short>::max(), EYA_USHORT_T_MAX);
}

TEST(eya_numeric_limits, uint_type_limits)
{
    EXPECT_EQ(std::numeric_limits<unsigned int>::min(), EYA_UINT_T_MIN);
    EXPECT_EQ(std::numeric_limits<unsigned int>::max(), EYA_UINT_T_MAX);
}

TEST(eya_numeric_limits, ulong_type_limits)
{
    EXPECT_EQ(std::numeric_limits<unsigned long>::min(), EYA_ULONG_T_MIN);
    EXPECT_EQ(std::numeric_limits<unsigned long>::max(), EYA_ULONG_T_MAX);
}

TEST(eya_numeric_limits, ullong_type_limits)
{
    EXPECT_EQ(std::numeric_limits<unsigned long long>::min(), EYA_ULLONG_T_MIN);
    EXPECT_EQ(std::numeric_limits<unsigned long long>::max(), EYA_ULLONG_T_MAX);
}

TEST(eya_numeric_limits, schar_type_limits)
{
    EXPECT_EQ(std::numeric_limits<signed char>::min(), EYA_SCHAR_T_MIN);
    EXPECT_EQ(std::numeric_limits<signed char>::max(), EYA_SCHAR_T_MAX);
}

TEST(eya_numeric_limits, sshort_type_limits)
{
    EXPECT_EQ(std::numeric_limits<signed short>::min(), EYA_SSHORT_T_MIN);
    EXPECT_EQ(std::numeric_limits<signed short>::max(), EYA_SSHORT_T_MAX);
}

TEST(eya_numeric_limits, sint_type_limits)
{
    EXPECT_EQ(std::numeric_limits<signed int>::min(), EYA_SINT_T_MIN);
    EXPECT_EQ(std::numeric_limits<signed int>::max(), EYA_SINT_T_MAX);
}

TEST(eya_numeric_limits, slong_type_limits)
{
    EXPECT_EQ(std::numeric_limits<signed long>::min(), EYA_SLONG_T_MIN);
    EXPECT_EQ(std::numeric_limits<signed long>::max(), EYA_SLONG_T_MAX);
}

TEST(eya_numeric_limits, sllong_type_limits)
{
    EXPECT_EQ(std::numeric_limits<signed long long>::min(), EYA_SLLONG_T_MIN);
    EXPECT_EQ(std::numeric_limits<signed long long>::max(), EYA_SLLONG_T_MAX);
}