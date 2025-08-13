#include <eya/error.h>
#include <gtest/gtest.h>

constexpr const auto EYA_ERROR_CODE_SOME_ERROR = 666;

TEST(eya_error, get_code)
{
    eya_error_t err{15};
    EXPECT_EQ(eya_error_get_code(&err), 15);
}

TEST(eya_error, get_code_null)
{
    EXPECT_DEATH(eya_error_get_code(nullptr), ".*");
}

TEST(eya_error, get_desc)
{
    eya_error_t err{0, "Test error"};
    EXPECT_STREQ(eya_error_get_desc(&err), "Test error");
}

TEST(eya_error, get_desc_null)
{
    EXPECT_DEATH(eya_error_get_desc(nullptr), ".*");
}

TEST(eya_error, set)
{
    eya_error_t err{};
    eya_error_set(&err, EYA_ERROR_CODE_SOME_ERROR, "Test error");

    EXPECT_EQ(err.code, EYA_ERROR_CODE_SOME_ERROR);
    EXPECT_STREQ(err.desc, "Test error");
}

TEST(eya_error, set_null)
{
    EXPECT_DEATH(eya_error_set(nullptr, EYA_ERROR_CODE_SOME_ERROR, "Test error"), ".*");
}

TEST(eya_error, set_code)
{
    eya_error_t err{};
    eya_error_set_code(&err, EYA_ERROR_CODE_SOME_ERROR);
    EXPECT_EQ(err.code, EYA_ERROR_CODE_SOME_ERROR);
    EXPECT_EQ(err.desc, nullptr);
}

TEST(eya_error, unpack)
{
    eya_error_t      err{EYA_ERROR_CODE_SOME_ERROR, "Test error"};
    eya_error_code_t code;
    const char      *desc;
    eya_error_unpack(&err, &code, &desc);
    EXPECT_EQ(code, EYA_ERROR_CODE_SOME_ERROR);
    EXPECT_STREQ(desc, "Test error");
}

TEST(eya_error, unpack_partial)
{
    eya_error_t err{EYA_ERROR_CODE_SOME_ERROR, "Test error"};

    eya_error_code_t code;
    eya_error_unpack(&err, &code, nullptr);
    EXPECT_EQ(code, EYA_ERROR_CODE_SOME_ERROR);

    const char *desc;
    eya_error_unpack(&err, nullptr, &desc);
    EXPECT_STREQ(desc, "Test error");
}

TEST(eya_error, assign)
{
    eya_error_t err{};
    eya_error_t other{EYA_ERROR_CODE_SOME_ERROR, "Test error"};
    eya_error_assign(&err, &other);
    EXPECT_EQ(err.code, EYA_ERROR_CODE_SOME_ERROR);
    EXPECT_STREQ(err.desc, "Test error");
}

TEST(eya_error, clear)
{
    eya_error_t err{EYA_ERROR_CODE_SOME_ERROR, "Test error"};
    eya_error_clear(&err);
    EXPECT_EQ(err.code, EYA_ERROR_CODE_NONE);
    EXPECT_EQ(err.desc, nullptr);
}

TEST(eya_error, get_code_and_clear)
{
    eya_error_t      err{EYA_ERROR_CODE_SOME_ERROR, "Test error"};
    eya_error_code_t code = eya_error_get_code_and_clear(&err);
    EXPECT_EQ(code, EYA_ERROR_CODE_SOME_ERROR);
    EXPECT_EQ(err.code, EYA_ERROR_CODE_NONE);
    EXPECT_EQ(err.desc, nullptr);
}

TEST(eya_error, is_code)
{
    eya_error_t err{EYA_ERROR_CODE_SOME_ERROR, "Test error"};
    EXPECT_TRUE(eya_error_is_equal_code_to(&err, EYA_ERROR_CODE_SOME_ERROR));
    EXPECT_FALSE(eya_error_is_equal_code_to(&err, EYA_ERROR_CODE_NONE));
}

TEST(eya_error, is_code_equal)
{
    eya_error_t err1{EYA_ERROR_CODE_SOME_ERROR, "Test error"};
    eya_error_t err2{EYA_ERROR_CODE_SOME_ERROR, "Other error"};
    EXPECT_TRUE(eya_error_is_equal_code(&err1, &err2));

    eya_error_t err3{EYA_ERROR_CODE_NONE, "Test error"};
    EXPECT_FALSE(eya_error_is_equal_code(&err1, &err3));
}

TEST(eya_error, is_ok)
{
    eya_error_t err{EYA_ERROR_CODE_NONE, nullptr};
    EXPECT_TRUE(eya_error_is_ok(&err));

    eya_error_t err2{EYA_ERROR_CODE_SOME_ERROR, "Test error"};
    EXPECT_FALSE(eya_error_is_ok(&err2));
}