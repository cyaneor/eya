#include <eya/memory_range.h>
#include <gtest/gtest.h>

TEST(eya_memory_range_unpack, unpacks_begin_and_end_correctly)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x2000};
    void              *begin = nullptr;
    void              *end   = nullptr;
    eya_memory_range_unpack(&range, &begin, &end);
    EXPECT_EQ(begin, (void *)0x1000);
    EXPECT_EQ(end, (void *)0x2000);
}

TEST(eya_memory_range_unpack, handles_null_begin_pointer)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x2000};
    void              *end   = nullptr;
    eya_memory_range_unpack(&range, nullptr, &end);
    EXPECT_EQ(end, (void *)0x2000);
}

TEST(eya_memory_range_unpack, handles_null_end_pointer)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x2000};
    void              *begin = nullptr;
    eya_memory_range_unpack(&range, &begin, nullptr);
    EXPECT_EQ(begin, (void *)0x1000);
}

TEST(eya_memory_range_unpack, handles_null_self_pointer_gracefully)
{
    void *begin = nullptr;
    void *end   = nullptr;
    EXPECT_DEATH(eya_memory_range_unpack(nullptr, &begin, &end), ".*");
}

TEST(eya_memory_range_get_begin, returns_correct_begin_pointer)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    void              *result = eya_memory_range_get_begin(&range);
    EXPECT_EQ(result, (void *)0x1000);
}

TEST(eya_memory_range_get_begin, handles_null_pointer_gracefully)
{
    EXPECT_DEATH(eya_memory_range_get_begin(nullptr), ".*");
}

TEST(eya_memory_range_get_end, returns_correct_end_pointer)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    void              *result = eya_memory_range_get_end(&range);
    EXPECT_EQ(result, (void *)0x2000);
}

TEST(eya_memory_range_get_end, handles_null_pointer_gracefully)
{
    EXPECT_DEATH(eya_memory_range_get_end(nullptr), ".*");
}

TEST(eya_memory_range_get_state, returns_uninitialized_for_null_begin_and_end)
{
    eya_memory_range_t       range  = {nullptr, nullptr};
    eya_memory_range_state_t result = eya_memory_range_get_state(&range);
    EXPECT_EQ(result, EYA_MEMORY_RANGE_UNINITIALIZED);
}

TEST(eya_memory_range_get_state, returns_empty_for_same_non_null_begin_and_end)
{
    void                    *ptr    = (void *)0x1000;
    eya_memory_range_t       range  = {ptr, ptr};
    eya_memory_range_state_t result = eya_memory_range_get_state(&range);
    EXPECT_EQ(result, EYA_MEMORY_RANGE_EMPTY);
}

TEST(eya_memory_range_get_state, returns_invalid_null_begin)
{
    eya_memory_range_t       range  = {nullptr, (void *)0x2000};
    eya_memory_range_state_t result = eya_memory_range_get_state(&range);
    EXPECT_EQ(result, EYA_MEMORY_RANGE_INVALID_NULL_BEGIN);
}

TEST(eya_memory_range_get_state, returns_invalid_null_end)
{
    eya_memory_range_t       range  = {(void *)0x1000, nullptr};
    eya_memory_range_state_t result = eya_memory_range_get_state(&range);
    EXPECT_EQ(result, EYA_MEMORY_RANGE_INVALID_NULL_END);
}

TEST(eya_memory_range_get_state, returns_has_data_for_valid_range)
{
    eya_memory_range_t       range  = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_state_t result = eya_memory_range_get_state(&range);
    EXPECT_EQ(result, EYA_MEMORY_RANGE_HAS_DATA);
}

TEST(eya_memory_range_get_state, returns_invalid_dangling_for_invalid_range)
{
    eya_memory_range_t       range  = {(void *)0x2000, (void *)0x1000};
    eya_memory_range_state_t result = eya_memory_range_get_state(&range);
    EXPECT_EQ(result, EYA_MEMORY_RANGE_INVALID_DANGLING);
}

TEST(eya_memory_range_get_state, handles_null_pointer_gracefully)
{
    EXPECT_DEATH(eya_memory_range_get_state(nullptr), ".*");
}

TEST(eya_memory_range_is_uninit, returns_true_for_uninitialized_range)
{
    eya_memory_range_t range  = {nullptr, nullptr};
    bool               result = eya_memory_range_is_uninit(&range);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_uninit, returns_false_for_non_uninitialized_range)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    bool               result = eya_memory_range_is_uninit(&range);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_is_uninit, handles_null_pointer_gracefully)
{
    EXPECT_DEATH(eya_memory_range_is_uninit(nullptr), ".*");
}

TEST(eya_memory_range_is_empty, returns_true_for_empty_range)
{
    void              *ptr    = (void *)0x1000;
    eya_memory_range_t range  = {ptr, ptr};
    bool               result = eya_memory_range_is_empty(&range);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_empty, returns_false_for_non_empty_range)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    bool               result = eya_memory_range_is_empty(&range);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_is_empty, handles_null_pointer_gracefully)
{
    EXPECT_DEATH(eya_memory_range_is_empty(nullptr), ".*");
}

TEST(eya_memory_range_has_data, returns_true_for_valid_data_range)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    bool               result = eya_memory_range_has_data(&range);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_has_data, returns_false_for_non_data_range)
{
    eya_memory_range_t range  = {nullptr, nullptr};
    bool               result = eya_memory_range_has_data(&range);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_has_data, handles_null_pointer_gracefully)
{
    EXPECT_DEATH(eya_memory_range_has_data(nullptr), ".*");
}

TEST(eya_memory_range_is_invalid, returns_true_for_uninitialized_range)
{
    eya_memory_range_t range  = {nullptr, nullptr};
    bool               result = eya_memory_range_is_invalid(&range);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_invalid, returns_true_for_null_begin_range)
{
    eya_memory_range_t range  = {nullptr, (void *)0x2000};
    bool               result = eya_memory_range_is_invalid(&range);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_invalid, returns_true_for_null_end_range)
{
    eya_memory_range_t range  = {(void *)0x1000, nullptr};
    bool               result = eya_memory_range_is_invalid(&range);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_invalid, returns_true_for_dangling_range)
{
    eya_memory_range_t range  = {(void *)0x2000, (void *)0x1000};
    bool               result = eya_memory_range_is_invalid(&range);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_invalid, returns_false_for_valid_range)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    bool               result = eya_memory_range_is_invalid(&range);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_is_invalid, handles_null_pointer_gracefully)
{
    EXPECT_DEATH(eya_memory_range_is_invalid(nullptr), ".*");
}

TEST(eya_memory_range_is_valid, returns_true_for_valid_range)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    bool               result = eya_memory_range_is_valid(&range);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_valid, returns_false_for_invalid_range)
{
    eya_memory_range_t range  = {nullptr, nullptr};
    bool               result = eya_memory_range_is_valid(&range);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_is_valid, handles_null_pointer_gracefully)
{
    EXPECT_DEATH(eya_memory_range_is_valid(nullptr), ".*");
}

TEST(eya_memory_range_unpack_v, unpacks_valid_range_correctly)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x2000};
    void              *begin = nullptr;
    void              *end   = nullptr;
    eya_memory_range_unpack_v(&range, &begin, &end);
    EXPECT_EQ(begin, (void *)0x1000);
    EXPECT_EQ(end, (void *)0x2000);
}

TEST(eya_memory_range_unpack_v, handles_null_begin_pointer)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x2000};
    void              *end   = nullptr;
    eya_memory_range_unpack_v(&range, nullptr, &end);
    EXPECT_EQ(end, (void *)0x2000);
}

TEST(eya_memory_range_unpack_v, handles_null_end_pointer)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x2000};
    void              *begin = nullptr;
    eya_memory_range_unpack_v(&range, &begin, nullptr);
    EXPECT_EQ(begin, (void *)0x1000);
}

TEST(eya_memory_range_unpack_v, handles_null_self_pointer_gracefully)
{
    void *begin = nullptr;
    void *end   = nullptr;
    EXPECT_DEATH(eya_memory_range_unpack_v(nullptr, &begin, &end), ".*");
}

TEST(eya_memory_range_unpack_v, fails_on_uninitialized_range)
{
    eya_memory_range_t range = {nullptr, nullptr};
    void              *begin = nullptr;
    void              *end   = nullptr;
    EXPECT_DEATH(eya_memory_range_unpack_v(&range, &begin, &end), ".*");
}

TEST(eya_memory_range_unpack_v, fails_on_invalid_null_begin_range)
{
    eya_memory_range_t range = {nullptr, (void *)0x2000};
    void              *begin = nullptr;
    void              *end   = nullptr;
    EXPECT_DEATH(eya_memory_range_unpack_v(&range, &begin, &end), ".*");
}

TEST(eya_memory_range_unpack_v, fails_on_invalid_null_end_range)
{
    eya_memory_range_t range = {(void *)0x1000, nullptr};
    void              *begin = nullptr;
    void              *end   = nullptr;
    EXPECT_DEATH(eya_memory_range_unpack_v(&range, &begin, &end), ".*");
}

TEST(eya_memory_range_unpack_v, fails_on_dangling_range)
{
    eya_memory_range_t range = {(void *)0x2000, (void *)0x1000};
    void              *begin = nullptr;
    void              *end   = nullptr;
    EXPECT_DEATH(eya_memory_range_unpack_v(&range, &begin, &end), ".*");
}

TEST(eya_memory_range_unpack_v, succeeds_on_empty_range)
{
    void              *ptr   = (void *)0x1000;
    eya_memory_range_t range = {ptr, ptr};
    void              *begin = nullptr;
    void              *end   = nullptr;
    eya_memory_range_unpack_v(&range, &begin, &end);
    EXPECT_EQ(begin, ptr);
    EXPECT_EQ(end, ptr);
}

TEST(eya_memory_range_diff, returns_correct_difference_for_valid_range)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    eya_uaddr_t        result = eya_memory_range_diff(&range);
    EXPECT_EQ(result, 0x1000);
}

TEST(eya_memory_range_diff, returns_zero_for_empty_range)
{
    void              *ptr    = (void *)0x1000;
    eya_memory_range_t range  = {ptr, ptr};
    eya_uaddr_t        result = eya_memory_range_diff(&range);
    EXPECT_EQ(result, 0);
}

TEST(eya_memory_range_diff, handles_null_self_pointer_gracefully)
{
    EXPECT_DEATH(eya_memory_range_diff(nullptr), ".*");
}

TEST(eya_memory_range_diff, fails_on_uninitialized_range)
{
    eya_memory_range_t range = {nullptr, nullptr};
    EXPECT_DEATH(eya_memory_range_diff(&range), ".*");
}

TEST(eya_memory_range_diff, fails_on_invalid_null_begin_range)
{
    eya_memory_range_t range = {nullptr, (void *)0x2000};
    EXPECT_DEATH(eya_memory_range_diff(&range), ".*");
}

TEST(eya_memory_range_diff, fails_on_invalid_null_end_range)
{
    eya_memory_range_t range = {(void *)0x1000, nullptr};
    EXPECT_DEATH(eya_memory_range_diff(&range), ".*");
}

TEST(eya_memory_range_diff, fails_on_dangling_range)
{
    eya_memory_range_t range = {(void *)0x2000, (void *)0x1000};
    EXPECT_DEATH(eya_memory_range_diff(&range), ".*");
}

TEST(eya_memory_range_get_size, returns_correct_size_for_valid_range)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    eya_usize_t        result = eya_memory_range_get_size(&range);
    EXPECT_EQ(result, 0x1000);
}

TEST(eya_memory_range_get_size, returns_zero_for_empty_range)
{
    void              *ptr    = (void *)0x1000;
    eya_memory_range_t range  = {ptr, ptr};
    eya_usize_t        result = eya_memory_range_get_size(&range);
    EXPECT_EQ(result, 0);
}

TEST(eya_memory_range_get_size, handles_null_self_pointer_gracefully)
{
    EXPECT_DEATH(eya_memory_range_get_size(nullptr), ".*");
}

TEST(eya_memory_range_get_size, fails_on_uninitialized_range)
{
    eya_memory_range_t range = {nullptr, nullptr};
    EXPECT_DEATH(eya_memory_range_get_size(&range), ".*");
}

TEST(eya_memory_range_get_size, fails_on_invalid_null_begin_range)
{
    eya_memory_range_t range = {nullptr, (void *)0x2000};
    EXPECT_DEATH(eya_memory_range_get_size(&range), ".*");
}

TEST(eya_memory_range_get_size, fails_on_invalid_null_end_range)
{
    eya_memory_range_t range = {(void *)0x1000, nullptr};
    EXPECT_DEATH(eya_memory_range_get_size(&range), ".*");
}

TEST(eya_memory_range_get_size, fails_on_dangling_range)
{
    eya_memory_range_t range = {(void *)0x2000, (void *)0x1000};
    EXPECT_DEATH(eya_memory_range_get_size(&range), ".*");
}

TEST(eya_memory_range_is_aligned, returns_true_for_aligned_begin)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    eya_usize_t        align  = 0x1000; // 4KB alignment
    bool               result = eya_memory_range_is_aligned(&range, align);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_aligned, returns_false_for_unaligned_begin)
{
    eya_memory_range_t range  = {(void *)0x1001, (void *)0x2000};
    eya_usize_t        align  = 0x1000; // 4KB alignment
    bool               result = eya_memory_range_is_aligned(&range, align);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_is_aligned, handles_null_self_pointer_gracefully)
{
    eya_usize_t align = 0x1000;
    EXPECT_DEATH(eya_memory_range_is_aligned(nullptr, align), ".*");
}

TEST(eya_memory_range_is_aligned, fails_on_non_power_of_two_alignment)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x2000};
    eya_usize_t        align = 0x1001; // Not a power of 2
    EXPECT_DEATH(eya_memory_range_is_aligned(&range, align), ".*");
}

TEST(eya_memory_range_is_aligned, fails_on_uninitialized_range)
{
    eya_memory_range_t range = {nullptr, nullptr};
    eya_usize_t        align = 0x1000;
    EXPECT_DEATH(eya_memory_range_is_aligned(&range, align), ".*");
}

TEST(eya_memory_range_is_aligned, fails_on_invalid_null_begin_range)
{
    eya_memory_range_t range = {nullptr, (void *)0x2000};
    eya_usize_t        align = 0x1000;
    EXPECT_DEATH(eya_memory_range_is_aligned(&range, align), ".*");
}

TEST(eya_memory_range_is_aligned, fails_on_invalid_null_end_range)
{
    eya_memory_range_t range = {(void *)0x1000, nullptr};
    eya_usize_t        align = 0x1000;
    EXPECT_DEATH(eya_memory_range_is_aligned(&range, align), ".*");
}

TEST(eya_memory_range_is_aligned, fails_on_dangling_range)
{
    eya_memory_range_t range = {(void *)0x2000, (void *)0x1000};
    eya_usize_t        align = 0x1000;
    EXPECT_DEATH(eya_memory_range_is_aligned(&range, align), ".*");
}

TEST(eya_memory_range_is_aligned, succeeds_on_empty_range)
{
    void              *ptr    = (void *)0x1000;
    eya_memory_range_t range  = {ptr, ptr};
    eya_usize_t        align  = 0x1000;
    bool               result = eya_memory_range_is_aligned(&range, align);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_multiple_of_size, returns_true_for_multiple_size)
{
    eya_memory_range_t range        = {(void *)0x1000, (void *)0x3000}; // Size 0x2000
    eya_usize_t        element_size = 0x1000;                           // 4KB
    bool               result       = eya_memory_range_is_multiple_of_size(&range, element_size);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_multiple_of_size, returns_false_for_non_multiple_size)
{
    eya_memory_range_t range        = {(void *)0x1000, (void *)0x2500}; // Size 0x1500
    eya_usize_t        element_size = 0x1000;                           // 4KB
    bool               result       = eya_memory_range_is_multiple_of_size(&range, element_size);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_is_multiple_of_size, returns_true_for_empty_range)
{
    void              *ptr          = (void *)0x1000;
    eya_memory_range_t range        = {ptr, ptr}; // Size 0
    eya_usize_t        element_size = 0x1000;
    bool               result       = eya_memory_range_is_multiple_of_size(&range, element_size);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_multiple_of_size, handles_null_self_pointer_gracefully)
{
    eya_usize_t element_size = 0x1000;
    EXPECT_DEATH(eya_memory_range_is_multiple_of_size(nullptr, element_size), ".*");
}

TEST(eya_memory_range_is_multiple_of_size, fails_on_zero_element_size)
{
    eya_memory_range_t range        = {(void *)0x1000, (void *)0x2000};
    eya_usize_t        element_size = 0;
    EXPECT_DEATH(eya_memory_range_is_multiple_of_size(&range, element_size), ".*");
}

TEST(eya_memory_range_is_multiple_of_size, fails_on_uninitialized_range)
{
    eya_memory_range_t range        = {nullptr, nullptr};
    eya_usize_t        element_size = 0x1000;
    EXPECT_DEATH(eya_memory_range_is_multiple_of_size(&range, element_size), ".*");
}

TEST(eya_memory_range_is_multiple_of_size, fails_on_invalid_null_begin_range)
{
    eya_memory_range_t range        = {nullptr, (void *)0x2000};
    eya_usize_t        element_size = 0x1000;
    EXPECT_DEATH(eya_memory_range_is_multiple_of_size(&range, element_size), ".*");
}

TEST(eya_memory_range_is_multiple_of_size, fails_on_invalid_null_end_range)
{
    eya_memory_range_t range        = {(void *)0x1000, nullptr};
    eya_usize_t        element_size = 0x1000;
    EXPECT_DEATH(eya_memory_range_is_multiple_of_size(&range, element_size), ".*");
}

TEST(eya_memory_range_is_multiple_of_size, fails_on_dangling_range)
{
    eya_memory_range_t range        = {(void *)0x2000, (void *)0x1000};
    eya_usize_t        element_size = 0x1000;
    EXPECT_DEATH(eya_memory_range_is_multiple_of_size(&range, element_size), ".*");
}

TEST(eya_memory_range_contains_ptr, returns_true_for_ptr_within_range)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    void              *ptr    = (void *)0x1500;
    bool               result = eya_memory_range_contains_ptr(&range, ptr);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_contains_ptr, returns_false_for_ptr_before_range)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    void              *ptr    = (void *)0x0fff;
    bool               result = eya_memory_range_contains_ptr(&range, ptr);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_contains_ptr, returns_false_for_ptr_at_end)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    void              *ptr    = (void *)0x2000;
    bool               result = eya_memory_range_contains_ptr(&range, ptr);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_contains_ptr, returns_true_for_ptr_at_begin)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    void              *ptr    = (void *)0x1000;
    bool               result = eya_memory_range_contains_ptr(&range, ptr);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_contains_ptr, returns_false_for_empty_range)
{
    void              *ptr    = (void *)0x1000;
    eya_memory_range_t range  = {ptr, ptr};
    bool               result = eya_memory_range_contains_ptr(&range, ptr);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_contains_ptr, handles_null_self_pointer_gracefully)
{
    void *ptr = (void *)0x1500;
    EXPECT_DEATH(eya_memory_range_contains_ptr(nullptr, ptr), ".*");
}

TEST(eya_memory_range_contains_ptr, fails_on_uninitialized_range)
{
    eya_memory_range_t range = {nullptr, nullptr};
    void              *ptr   = (void *)0x1500;
    EXPECT_DEATH(eya_memory_range_contains_ptr(&range, ptr), ".*");
}

TEST(eya_memory_range_contains_ptr, fails_on_invalid_null_begin_range)
{
    eya_memory_range_t range = {nullptr, (void *)0x2000};
    void              *ptr   = (void *)0x1500;
    EXPECT_DEATH(eya_memory_range_contains_ptr(&range, ptr), ".*");
}

TEST(eya_memory_range_contains_ptr, fails_on_invalid_null_end_range)
{
    eya_memory_range_t range = {(void *)0x1000, nullptr};
    void              *ptr   = (void *)0x1500;
    EXPECT_DEATH(eya_memory_range_contains_ptr(&range, ptr), ".*");
}

TEST(eya_memory_range_contains_ptr, fails_on_dangling_range)
{
    eya_memory_range_t range = {(void *)0x2000, (void *)0x1000};
    void              *ptr   = (void *)0x1500;
    EXPECT_DEATH(eya_memory_range_contains_ptr(&range, ptr), ".*");
}

TEST(eya_memory_range_contains_range, returns_true_for_contained_range)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x3000};
    void              *begin  = (void *)0x1500;
    void              *end    = (void *)0x2500;
    bool               result = eya_memory_range_contains_range(&range, begin, end);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_contains_range, returns_false_for_same_range)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    void              *begin  = (void *)0x1000;
    void              *end    = (void *)0x2000;
    bool               result = eya_memory_range_contains_range(&range, begin, end);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_contains_range, returns_false_for_range_exceeding_end)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    void              *begin  = (void *)0x1500;
    void              *end    = (void *)0x2500;
    bool               result = eya_memory_range_contains_range(&range, begin, end);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_contains_range, returns_false_for_range_before_begin)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    void              *begin  = (void *)0x0500;
    void              *end    = (void *)0x0fff;
    bool               result = eya_memory_range_contains_range(&range, begin, end);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_contains_range, returns_false_for_empty_self_range)
{
    void              *ptr    = (void *)0x1000;
    eya_memory_range_t range  = {ptr, ptr};
    void              *begin  = (void *)0x1000;
    void              *end    = (void *)0x1000;
    bool               result = eya_memory_range_contains_range(&range, begin, end);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_contains_range, handles_null_self_pointer_gracefully)
{
    void *begin = (void *)0x1500;
    void *end   = (void *)0x2500;
    EXPECT_DEATH(eya_memory_range_contains_range(nullptr, begin, end), ".*");
}

TEST(eya_memory_range_contains_range, fails_on_uninitialized_self_range)
{
    eya_memory_range_t range = {nullptr, nullptr};
    void              *begin = (void *)0x1500;
    void              *end   = (void *)0x2500;
    EXPECT_DEATH(eya_memory_range_contains_range(&range, begin, end), ".*");
}

TEST(eya_memory_range_contains_range, fails_on_invalid_null_begin_self_range)
{
    eya_memory_range_t range = {nullptr, (void *)0x2000};
    void              *begin = (void *)0x1500;
    void              *end   = (void *)0x2500;
    EXPECT_DEATH(eya_memory_range_contains_range(&range, begin, end), ".*");
}

TEST(eya_memory_range_contains_range, fails_on_invalid_null_end_self_range)
{
    eya_memory_range_t range = {(void *)0x1000, nullptr};
    void              *begin = (void *)0x1500;
    void              *end   = (void *)0x2500;
    EXPECT_DEATH(eya_memory_range_contains_range(&range, begin, end), ".*");
}

TEST(eya_memory_range_contains_range, fails_on_dangling_self_range)
{
    eya_memory_range_t range = {(void *)0x2000, (void *)0x1000};
    void              *begin = (void *)0x1500;
    void              *end   = (void *)0x2500;
    EXPECT_DEATH(eya_memory_range_contains_range(&range, begin, end), ".*");
}

TEST(eya_memory_range_contains, returns_true_for_contained_range)
{
    eya_memory_range_t self   = {(void *)0x1000, (void *)0x3000};
    eya_memory_range_t other  = {(void *)0x1500, (void *)0x2500};
    bool               result = eya_memory_range_contains(&self, &other);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_contains, returns_false_for_same_range)
{
    eya_memory_range_t self   = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t other  = {(void *)0x1000, (void *)0x2000};
    bool               result = eya_memory_range_contains(&self, &other);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_contains, returns_false_for_range_exceeding_end)
{
    eya_memory_range_t self   = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t other  = {(void *)0x1500, (void *)0x2500};
    bool               result = eya_memory_range_contains(&self, &other);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_contains, returns_false_for_range_before_begin)
{
    eya_memory_range_t self   = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t other  = {(void *)0x0500, (void *)0x0fff};
    bool               result = eya_memory_range_contains(&self, &other);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_contains, returns_false_for_empty_self_range)
{
    void              *ptr    = (void *)0x1000;
    eya_memory_range_t self   = {ptr, ptr};
    eya_memory_range_t other  = {ptr, ptr};
    bool               result = eya_memory_range_contains(&self, &other);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_contains, handles_null_self_pointer_gracefully)
{
    eya_memory_range_t other = {(void *)0x1500, (void *)0x2500};
    EXPECT_DEATH(eya_memory_range_contains(nullptr, &other), ".*");
}

TEST(eya_memory_range_contains, handles_null_other_pointer_gracefully)
{
    eya_memory_range_t self = {(void *)0x1000, (void *)0x2000};
    EXPECT_DEATH(eya_memory_range_contains(&self, nullptr), ".*");
}

TEST(eya_memory_range_contains, fails_on_uninitialized_self_range)
{
    eya_memory_range_t self  = {nullptr, nullptr};
    eya_memory_range_t other = {(void *)0x1500, (void *)0x2500};
    EXPECT_DEATH(eya_memory_range_contains(&self, &other), ".*");
}

TEST(eya_memory_range_contains, fails_on_uninitialized_other_range)
{
    eya_memory_range_t self  = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t other = {nullptr, nullptr};
    EXPECT_DEATH(eya_memory_range_contains(&self, &other), ".*");
}

TEST(eya_memory_range_contains, fails_on_invalid_null_begin_self_range)
{
    eya_memory_range_t self  = {nullptr, (void *)0x2000};
    eya_memory_range_t other = {(void *)0x1500, (void *)0x2500};
    EXPECT_DEATH(eya_memory_range_contains(&self, &other), ".*");
}

TEST(eya_memory_range_contains, fails_on_invalid_null_begin_other_range)
{
    eya_memory_range_t self  = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t other = {nullptr, (void *)0x2500};
    EXPECT_DEATH(eya_memory_range_contains(&self, &other), ".*");
}

TEST(eya_memory_range_contains, fails_on_invalid_null_end_self_range)
{
    eya_memory_range_t self  = {(void *)0x1000, nullptr};
    eya_memory_range_t other = {(void *)0x1500, (void *)0x2500};
    EXPECT_DEATH(eya_memory_range_contains(&self, &other), ".*");
}

TEST(eya_memory_range_contains, fails_on_invalid_null_end_other_range)
{
    eya_memory_range_t self  = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t other = {(void *)0x1500, nullptr};
    EXPECT_DEATH(eya_memory_range_contains(&self, &other), ".*");
}

TEST(eya_memory_range_contains, fails_on_dangling_self_range)
{
    eya_memory_range_t self  = {(void *)0x2000, (void *)0x1000};
    eya_memory_range_t other = {(void *)0x1500, (void *)0x2500};
    EXPECT_DEATH(eya_memory_range_contains(&self, &other), ".*");
}

TEST(eya_memory_range_contains, fails_on_dangling_other_range)
{
    eya_memory_range_t self  = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t other = {(void *)0x2500, (void *)0x1500};
    EXPECT_DEATH(eya_memory_range_contains(&self, &other), ".*");
}

TEST(eya_memory_range_is_valid_offset, returns_true_for_valid_offset)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000}; // Size 0x1000
    eya_uoffset_t      offset = 0x500;
    bool               result = eya_memory_range_is_valid_offset(&range, offset);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_valid_offset, returns_false_for_offset_equal_to_size)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000}; // Size 0x1000
    eya_uoffset_t      offset = 0x1000;
    bool               result = eya_memory_range_is_valid_offset(&range, offset);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_is_valid_offset, returns_false_for_offset_exceeding_size)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000}; // Size 0x1000
    eya_uoffset_t      offset = 0x1001;
    bool               result = eya_memory_range_is_valid_offset(&range, offset);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_is_valid_offset, returns_false_for_empty_range)
{
    void              *ptr    = (void *)0x1000;
    eya_memory_range_t range  = {ptr, ptr}; // Size 0
    eya_uoffset_t      offset = 0;
    bool               result = eya_memory_range_is_valid_offset(&range, offset);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_is_valid_offset, handles_null_self_pointer_gracefully)
{
    eya_uoffset_t offset = 0x500;
    EXPECT_DEATH(eya_memory_range_is_valid_offset(nullptr, offset), ".*");
}

TEST(eya_memory_range_is_valid_offset, fails_on_uninitialized_range)
{
    eya_memory_range_t range  = {nullptr, nullptr};
    eya_uoffset_t      offset = 0x500;
    EXPECT_DEATH(eya_memory_range_is_valid_offset(&range, offset), ".*");
}

TEST(eya_memory_range_is_valid_offset, fails_on_invalid_null_begin_range)
{
    eya_memory_range_t range  = {nullptr, (void *)0x2000};
    eya_uoffset_t      offset = 0x500;
    EXPECT_DEATH(eya_memory_range_is_valid_offset(&range, offset), ".*");
}

TEST(eya_memory_range_is_valid_offset, fails_on_invalid_null_end_range)
{
    eya_memory_range_t range  = {(void *)0x1000, nullptr};
    eya_uoffset_t      offset = 0x500;
    EXPECT_DEATH(eya_memory_range_is_valid_offset(&range, offset), ".*");
}

TEST(eya_memory_range_is_valid_offset, fails_on_dangling_range)
{
    eya_memory_range_t range  = {(void *)0x2000, (void *)0x1000};
    eya_uoffset_t      offset = 0x500;
    EXPECT_DEATH(eya_memory_range_is_valid_offset(&range, offset), ".*");
}

TEST(eya_memory_range_at_f, returns_correct_pointer_for_valid_offset)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    eya_uoffset_t      offset = 0x500;
    void              *result = eya_memory_range_at_from_front(&range, offset);
    EXPECT_EQ(result, (void *)0x1500);
}

TEST(eya_memory_range_at_f, returns_begin_for_zero_offset)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    eya_uoffset_t      offset = 0;
    void              *result = eya_memory_range_at_from_front(&range, offset);
    EXPECT_EQ(result, (void *)0x1000);
}

TEST(eya_memory_range_at_f, fails_on_offset_equal_to_size)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000}; // Size 0x1000
    eya_uoffset_t      offset = 0x1000;
    EXPECT_DEATH(eya_memory_range_at_from_front(&range, offset), ".*");
}

TEST(eya_memory_range_at_f, fails_on_offset_exceeding_size)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000}; // Size 0x1000
    eya_uoffset_t      offset = 0x1001;
    EXPECT_DEATH(eya_memory_range_at_from_front(&range, offset), ".*");
}

TEST(eya_memory_range_at_f, fails_on_empty_range)
{
    void              *ptr    = (void *)0x1000;
    eya_memory_range_t range  = {ptr, ptr}; // Size 0
    eya_uoffset_t      offset = 0;
    EXPECT_DEATH(eya_memory_range_at_from_front(&range, offset), ".*");
}

TEST(eya_memory_range_at_f, handles_null_self_pointer_gracefully)
{
    eya_uoffset_t offset = 0x500;
    EXPECT_DEATH(eya_memory_range_at_from_front(nullptr, offset), ".*");
}

TEST(eya_memory_range_at_f, fails_on_uninitialized_range)
{
    eya_memory_range_t range  = {nullptr, nullptr};
    eya_uoffset_t      offset = 0x500;
    EXPECT_DEATH(eya_memory_range_at_from_front(&range, offset), ".*");
}

TEST(eya_memory_range_at_f, fails_on_invalid_null_begin_range)
{
    eya_memory_range_t range  = {nullptr, (void *)0x2000};
    eya_uoffset_t      offset = 0x500;
    EXPECT_DEATH(eya_memory_range_at_from_front(&range, offset), ".*");
}

TEST(eya_memory_range_at_f, fails_on_invalid_null_end_range)
{
    eya_memory_range_t range  = {(void *)0x1000, nullptr};
    eya_uoffset_t      offset = 0x500;
    EXPECT_DEATH(eya_memory_range_at_from_front(&range, offset), ".*");
}

TEST(eya_memory_range_at_f, fails_on_dangling_range)
{
    eya_memory_range_t range  = {(void *)0x2000, (void *)0x1000};
    eya_uoffset_t      offset = 0x500;
    EXPECT_DEATH(eya_memory_range_at_from_front(&range, offset), ".*");
}

TEST(eya_memory_range_at_b, returns_correct_pointer_for_valid_offset)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000}; // Size 0x1000
    eya_uoffset_t      offset = 0;
    void              *result = eya_memory_range_at_from_back(&range, offset);
    EXPECT_EQ(result, (void *)0x1fff); // size - (0 + 1) = 0x1000 - 1 = 0x1fff
}

TEST(eya_memory_range_at_b, returns_correct_pointer_for_non_zero_offset)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000}; // Size 0x1000
    eya_uoffset_t      offset = 1;
    void              *result = eya_memory_range_at_from_back(&range, offset);
    EXPECT_EQ(result, (void *)0x1ffe); // size - (1 + 1) = 0x1000 - 2 = 0x1ffe
}

TEST(eya_memory_range_at_b, fails_on_offset_exceeding_size)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000}; // Size 0x1000
    eya_uoffset_t      offset = 0x1000;
    EXPECT_DEATH(eya_memory_range_at_from_back(&range, offset), ".*");
}

TEST(eya_memory_range_at_b, fails_on_empty_range)
{
    void              *ptr    = (void *)0x1000;
    eya_memory_range_t range  = {ptr, ptr}; // Size 0
    eya_uoffset_t      offset = 0;
    EXPECT_DEATH(eya_memory_range_at_from_back(&range, offset), ".*");
}

TEST(eya_memory_range_at_b, handles_null_self_pointer_gracefully)
{
    eya_uoffset_t offset = 0;
    EXPECT_DEATH(eya_memory_range_at_from_back(nullptr, offset), ".*");
}

TEST(eya_memory_range_at_b, fails_on_uninitialized_range)
{
    eya_memory_range_t range  = {nullptr, nullptr};
    eya_uoffset_t      offset = 0;
    EXPECT_DEATH(eya_memory_range_at_from_back(&range, offset), ".*");
}

TEST(eya_memory_range_at_b, fails_on_invalid_null_begin_range)
{
    eya_memory_range_t range  = {nullptr, (void *)0x2000};
    eya_uoffset_t      offset = 0;
    EXPECT_DEATH(eya_memory_range_at_from_back(&range, offset), ".*");
}

TEST(eya_memory_range_at_b, fails_on_invalid_null_end_range)
{
    eya_memory_range_t range  = {(void *)0x1000, nullptr};
    eya_uoffset_t      offset = 0;
    EXPECT_DEATH(eya_memory_range_at_from_back(&range, offset), ".*");
}

TEST(eya_memory_range_at_b, fails_on_dangling_range)
{
    eya_memory_range_t range  = {(void *)0x2000, (void *)0x1000};
    eya_uoffset_t      offset = 0;
    EXPECT_DEATH(eya_memory_range_at_from_back(&range, offset), ".*");
}

TEST(eya_memory_range_at, returns_correct_pointer_for_valid_offset_forward)
{
    eya_memory_range_t range    = {(void *)0x1000, (void *)0x2000}; // Size 0x1000
    eya_uoffset_t      offset   = 0x500;
    bool               reversed = false;
    void              *result   = eya_memory_range_at(&range, offset, reversed);
    EXPECT_EQ(result, (void *)0x1500);
}

TEST(eya_memory_range_at, returns_correct_pointer_for_valid_offset_reversed)
{
    eya_memory_range_t range    = {(void *)0x1000, (void *)0x2000}; // Size 0x1000
    eya_uoffset_t      offset   = 0;
    bool               reversed = true;
    void              *result   = eya_memory_range_at(&range, offset, reversed);
    EXPECT_EQ(result, (void *)0x1fff); // size - (0 + 1) = 0x1000 - 1 = 0x1fff
}

TEST(eya_memory_range_at, returns_begin_for_zero_offset_forward)
{
    eya_memory_range_t range    = {(void *)0x1000, (void *)0x2000};
    eya_uoffset_t      offset   = 0;
    bool               reversed = false;
    void              *result   = eya_memory_range_at(&range, offset, reversed);
    EXPECT_EQ(result, (void *)0x1000);
}

TEST(eya_memory_range_at, fails_on_offset_equal_to_size_forward)
{
    eya_memory_range_t range    = {(void *)0x1000, (void *)0x2000}; // Size 0x1000
    eya_uoffset_t      offset   = 0x1000;
    bool               reversed = false;
    EXPECT_DEATH(eya_memory_range_at(&range, offset, reversed), ".*");
}

TEST(eya_memory_range_at, fails_on_offset_exceeding_size_forward)
{
    eya_memory_range_t range    = {(void *)0x1000, (void *)0x2000}; // Size 0x1000
    eya_uoffset_t      offset   = 0x1001;
    bool               reversed = false;
    EXPECT_DEATH(eya_memory_range_at(&range, offset, reversed), ".*");
}

TEST(eya_memory_range_at, fails_on_offset_exceeding_size_reversed)
{
    eya_memory_range_t range    = {(void *)0x1000, (void *)0x2000}; // Size 0x1000
    eya_uoffset_t      offset   = 0x1000;
    bool               reversed = true;
    EXPECT_DEATH(eya_memory_range_at(&range, offset, reversed), ".*");
}

TEST(eya_memory_range_at, fails_on_empty_range_forward)
{
    void              *ptr      = (void *)0x1000;
    eya_memory_range_t range    = {ptr, ptr}; // Size 0
    eya_uoffset_t      offset   = 0;
    bool               reversed = false;
    EXPECT_DEATH(eya_memory_range_at(&range, offset, reversed), ".*");
}

TEST(eya_memory_range_at, fails_on_empty_range_reversed)
{
    void              *ptr      = (void *)0x1000;
    eya_memory_range_t range    = {ptr, ptr}; // Size 0
    eya_uoffset_t      offset   = 0;
    bool               reversed = true;
    EXPECT_DEATH(eya_memory_range_at(&range, offset, reversed), ".*");
}

TEST(eya_memory_range_at, handles_null_self_pointer_gracefully)
{
    eya_uoffset_t offset   = 0x500;
    bool          reversed = false;
    EXPECT_DEATH(eya_memory_range_at(nullptr, offset, reversed), ".*");
}

TEST(eya_memory_range_at, fails_on_uninitialized_range_forward)
{
    eya_memory_range_t range    = {nullptr, nullptr};
    eya_uoffset_t      offset   = 0x500;
    bool               reversed = false;
    EXPECT_DEATH(eya_memory_range_at(&range, offset, reversed), ".*");
}

TEST(eya_memory_range_at, fails_on_uninitialized_range_reversed)
{
    eya_memory_range_t range    = {nullptr, nullptr};
    eya_uoffset_t      offset   = 0x500;
    bool               reversed = true;
    EXPECT_DEATH(eya_memory_range_at(&range, offset, reversed), ".*");
}

TEST(eya_memory_range_at, fails_on_invalid_null_begin_range_forward)
{
    eya_memory_range_t range    = {nullptr, (void *)0x2000};
    eya_uoffset_t      offset   = 0x500;
    bool               reversed = false;
    EXPECT_DEATH(eya_memory_range_at(&range, offset, reversed), ".*");
}

TEST(eya_memory_range_at, fails_on_invalid_null_begin_range_reversed)
{
    eya_memory_range_t range    = {nullptr, (void *)0x2000};
    eya_uoffset_t      offset   = 0x500;
    bool               reversed = true;
    EXPECT_DEATH(eya_memory_range_at(&range, offset, reversed), ".*");
}

TEST(eya_memory_range_at, fails_on_invalid_null_end_range_forward)
{
    eya_memory_range_t range    = {(void *)0x1000, nullptr};
    eya_uoffset_t      offset   = 0x500;
    bool               reversed = false;
    EXPECT_DEATH(eya_memory_range_at(&range, offset, reversed), ".*");
}

TEST(eya_memory_range_at, fails_on_invalid_null_end_range_reversed)
{
    eya_memory_range_t range    = {(void *)0x1000, nullptr};
    eya_uoffset_t      offset   = 0x500;
    bool               reversed = true;
    EXPECT_DEATH(eya_memory_range_at(&range, offset, reversed), ".*");
}

TEST(eya_memory_range_at, fails_on_dangling_range_forward)
{
    eya_memory_range_t range    = {(void *)0x2000, (void *)0x1000};
    eya_uoffset_t      offset   = 0x500;
    bool               reversed = false;
    EXPECT_DEATH(eya_memory_range_at(&range, offset, reversed), ".*");
}

TEST(eya_memory_range_at, fails_on_dangling_range_reversed)
{
    eya_memory_range_t range    = {(void *)0x2000, (void *)0x1000};
    eya_uoffset_t      offset   = 0x500;
    bool               reversed = true;
    EXPECT_DEATH(eya_memory_range_at(&range, offset, reversed), ".*");
}

TEST(eya_memory_range_front, returns_begin_for_valid_range)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    void              *result = eya_memory_range_front(&range);
    EXPECT_EQ(result, (void *)0x1000);
}

TEST(eya_memory_range_front, fails_on_empty_range)
{
    void              *ptr   = (void *)0x1000;
    eya_memory_range_t range = {ptr, ptr};
    EXPECT_DEATH(eya_memory_range_front(&range), ".*");
}

TEST(eya_memory_range_front, handles_null_self_pointer_gracefully)
{
    EXPECT_DEATH(eya_memory_range_front(nullptr), ".*");
}

TEST(eya_memory_range_front, fails_on_uninitialized_range)
{
    eya_memory_range_t range = {nullptr, nullptr};
    EXPECT_DEATH(eya_memory_range_front(&range), ".*");
}

TEST(eya_memory_range_front, fails_on_invalid_null_begin_range)
{
    eya_memory_range_t range = {nullptr, (void *)0x2000};
    EXPECT_DEATH(eya_memory_range_front(&range), ".*");
}

TEST(eya_memory_range_front, fails_on_invalid_null_end_range)
{
    eya_memory_range_t range = {(void *)0x1000, nullptr};
    EXPECT_DEATH(eya_memory_range_front(&range), ".*");
}

TEST(eya_memory_range_front, fails_on_dangling_range)
{
    eya_memory_range_t range = {(void *)0x2000, (void *)0x1000};
    EXPECT_DEATH(eya_memory_range_front(&range), ".*");
}

TEST(eya_memory_range_back, returns_end_minus_one_for_valid_range)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    void              *result = eya_memory_range_back(&range);
    EXPECT_EQ(result, (void *)0x1FFF); // предполагая, что диапазон [begin, end)
}

TEST(eya_memory_range_back, fails_on_empty_range)
{
    void              *ptr   = (void *)0x1000;
    eya_memory_range_t range = {ptr, ptr};
    EXPECT_DEATH(eya_memory_range_back(&range), ".*");
}

TEST(eya_memory_range_back, handles_null_self_pointer_gracefully)
{
    EXPECT_DEATH(eya_memory_range_back(nullptr), ".*");
}

TEST(eya_memory_range_back, fails_on_uninitialized_range)
{
    eya_memory_range_t range = {nullptr, nullptr};
    EXPECT_DEATH(eya_memory_range_back(&range), ".*");
}

TEST(eya_memory_range_back, fails_on_invalid_null_begin_range)
{
    eya_memory_range_t range = {nullptr, (void *)0x2000};
    EXPECT_DEATH(eya_memory_range_back(&range), ".*");
}

TEST(eya_memory_range_back, fails_on_invalid_null_end_range)
{
    eya_memory_range_t range = {(void *)0x1000, nullptr};
    EXPECT_DEATH(eya_memory_range_back(&range), ".*");
}

TEST(eya_memory_range_back, fails_on_dangling_range)
{
    eya_memory_range_t range = {(void *)0x2000, (void *)0x1000};
    EXPECT_DEATH(eya_memory_range_back(&range), ".*");
}

TEST(eya_memory_range_is_equal_begin_to, returns_true_for_equal_begin)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    void              *ptr    = (void *)0x1000;
    bool               result = eya_memory_range_is_equal_begin_to(&range, ptr);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_equal_begin_to, returns_false_for_unequal_begin)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    void              *ptr    = (void *)0x1001;
    bool               result = eya_memory_range_is_equal_begin_to(&range, ptr);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_is_equal_begin_to, handles_null_self_pointer_gracefully)
{
    void *ptr = (void *)0x1000;
    EXPECT_DEATH(eya_memory_range_is_equal_begin_to(nullptr, ptr), ".*");
}

TEST(eya_memory_range_is_equal_end_to, returns_true_for_equal_end)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    void              *ptr    = (void *)0x2000;
    bool               result = eya_memory_range_is_equal_end_to(&range, ptr);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_equal_end_to, returns_false_for_unequal_end)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    void              *ptr    = (void *)0x2001;
    bool               result = eya_memory_range_is_equal_end_to(&range, ptr);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_is_equal_end_to, handles_null_self_pointer_gracefully)
{
    void *ptr = (void *)0x2000;
    EXPECT_DEATH(eya_memory_range_is_equal_end_to(nullptr, ptr), ".*");
}

TEST(eya_memory_range_is_equal_begin, returns_true_for_equal_begins)
{
    eya_memory_range_t range1 = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t range2 = {(void *)0x1000, (void *)0x3000};
    bool               result = eya_memory_range_is_equal_begin(&range1, &range2);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_equal_begin, returns_false_for_unequal_begins)
{
    eya_memory_range_t range1 = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t range2 = {(void *)0x1001, (void *)0x2000};
    bool               result = eya_memory_range_is_equal_begin(&range1, &range2);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_is_equal_begin, handles_null_self_pointer_gracefully)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x2000};
    EXPECT_DEATH(eya_memory_range_is_equal_begin(nullptr, &range), ".*");
}

TEST(eya_memory_range_is_equal_begin, handles_null_other_pointer_gracefully)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x2000};
    EXPECT_DEATH(eya_memory_range_is_equal_begin(&range, nullptr), ".*");
}

TEST(eya_memory_range_is_equal_end, returns_true_for_equal_ends)
{
    eya_memory_range_t range1 = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t range2 = {(void *)0x1500, (void *)0x2000};
    bool               result = eya_memory_range_is_equal_end(&range1, &range2);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_equal_end, returns_false_for_unequal_ends)
{
    eya_memory_range_t range1 = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t range2 = {(void *)0x1000, (void *)0x2001};
    bool               result = eya_memory_range_is_equal_end(&range1, &range2);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_is_equal_end, handles_null_self_pointer_gracefully)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x2000};
    EXPECT_DEATH(eya_memory_range_is_equal_end(nullptr, &range), ".*");
}

TEST(eya_memory_range_is_equal_end, handles_null_other_pointer_gracefully)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x2000};
    EXPECT_DEATH(eya_memory_range_is_equal_end(&range, nullptr), ".*");
}

TEST(eya_memory_range_is_equal, returns_true_for_same_object)
{
    eya_memory_range_t range  = {(void *)0x1000, (void *)0x2000};
    bool               result = eya_memory_range_is_equal(&range, &range);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_equal, returns_true_for_equal_ranges)
{
    eya_memory_range_t range1 = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t range2 = {(void *)0x1000, (void *)0x2000};
    bool               result = eya_memory_range_is_equal(&range1, &range2);
    EXPECT_TRUE(result);
}

TEST(eya_memory_range_is_equal, returns_false_for_unequal_begins)
{
    eya_memory_range_t range1 = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t range2 = {(void *)0x1001, (void *)0x2000};
    bool               result = eya_memory_range_is_equal(&range1, &range2);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_is_equal, returns_false_for_unequal_ends)
{
    eya_memory_range_t range1 = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t range2 = {(void *)0x1000, (void *)0x2001};
    bool               result = eya_memory_range_is_equal(&range1, &range2);
    EXPECT_FALSE(result);
}

TEST(eya_memory_range_is_equal, handles_null_self_pointer_gracefully)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x2000};
    EXPECT_DEATH(eya_memory_range_is_equal(nullptr, &range), ".*");
}

TEST(eya_memory_range_is_equal, handles_null_other_pointer_gracefully)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x2000};
    EXPECT_DEATH(eya_memory_range_is_equal(&range, nullptr), ".*");
}

TEST(eya_memory_range_assign_v, copies_range_correctly)
{
    eya_memory_range_t src = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t dst;

    eya_memory_range_assign_v(&dst, &src);

    EXPECT_EQ(dst.begin, src.begin);
    EXPECT_EQ(dst.end, src.end);
}

TEST(eya_memory_range_assign_v, handles_null_self_pointer_gracefully)
{
    eya_memory_range_t src = {(void *)0x1000, (void *)0x2000};
    EXPECT_DEATH(eya_memory_range_assign_v(nullptr, &src), ".*");
}

TEST(eya_memory_range_assign_v, handles_null_other_pointer_gracefully)
{
    eya_memory_range_t dst;
    EXPECT_DEATH(eya_memory_range_assign_v(&dst, nullptr), ".*");
}

TEST(eya_memory_range_clear, sets_null_pointers)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x2000};

    eya_memory_range_clear(&range);

    EXPECT_EQ(range.begin, nullptr);
    EXPECT_EQ(range.end, nullptr);
}

TEST(eya_memory_range_clear, handles_null_pointer_gracefully)
{
    EXPECT_DEATH(eya_memory_range_clear(nullptr), ".*");
}

TEST(eya_memory_range_assign_v, assigns_valid_range)
{
    eya_memory_range_t src = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t dst;

    eya_memory_range_assign_v(&dst, &src);

    EXPECT_EQ(dst.begin, src.begin);
    EXPECT_EQ(dst.end, src.end);
}

TEST(eya_memory_range_assign_v, fails_on_invalid_range)
{
    eya_memory_range_t src = {nullptr, (void *)0x2000};
    eya_memory_range_t dst;

    EXPECT_DEATH(eya_memory_range_assign_v(&dst, &src), ".*");
}

TEST(eya_memory_range_reset_v, sets_valid_range)
{
    eya_memory_range_t range;

    eya_memory_range_reset_v(&range, (void *)0x1000, (void *)0x2000);

    EXPECT_EQ(range.begin, (void *)0x1000);
    EXPECT_EQ(range.end, (void *)0x2000);
}

TEST(eya_memory_range_reset_v, fails_on_invalid_range)
{
    eya_memory_range_t range;

    EXPECT_DEATH(eya_memory_range_reset_v(&range, nullptr, (void *)0x2000), ".*");
}

TEST(eya_memory_range_reset_s, sets_range_from_begin_and_size)
{
    eya_memory_range_t range;

    eya_memory_range_reset_s(&range, (void *)0x1000, 0x1000);

    EXPECT_EQ(range.begin, (void *)0x1000);
    EXPECT_EQ(range.end, (void *)0x2000);
}

TEST(eya_memory_range_reset_s, fails_on_null_begin)
{
    eya_memory_range_t range;

    EXPECT_DEATH(eya_memory_range_reset_s(&range, nullptr, 0x1000), ".*");
}

TEST(eya_memory_range_reset_f, sets_range_when_begin_not_null)
{
    eya_memory_range_t range;

    eya_memory_range_reset_f(&range, (void *)0x1000, 0x1000);

    EXPECT_EQ(range.begin, (void *)0x1000);
    EXPECT_EQ(range.end, (void *)0x2000);
}

TEST(eya_memory_range_reset_f, clears_range_when_begin_null)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x2000};

    eya_memory_range_reset_f(&range, nullptr, 0x1000);

    EXPECT_EQ(range.begin, nullptr);
    EXPECT_EQ(range.end, nullptr);
}

TEST(eya_memory_range_swap, swaps_ranges_correctly)
{
    eya_memory_range_t a = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t b = {(void *)0x3000, (void *)0x4000};

    eya_memory_range_swap(&a, &b);

    EXPECT_EQ(a.begin, (void *)0x3000);
    EXPECT_EQ(a.end, (void *)0x4000);
    EXPECT_EQ(b.begin, (void *)0x1000);
    EXPECT_EQ(b.end, (void *)0x2000);
}

TEST(eya_memory_range_swap, handles_null_first_pointer_gracefully)
{
    eya_memory_range_t b = {(void *)0x3000, (void *)0x4000};
    EXPECT_DEATH(eya_memory_range_swap(nullptr, &b), ".*");
}

TEST(eya_memory_range_swap, handles_null_second_pointer_gracefully)
{
    eya_memory_range_t a = {(void *)0x1000, (void *)0x2000};
    EXPECT_DEATH(eya_memory_range_swap(&a, nullptr), ".*");
}

TEST(eya_memory_range_exchange, clears_first_and_swaps)
{
    eya_memory_range_t a = {(void *)0x1000, (void *)0x2000};
    eya_memory_range_t b = {(void *)0x3000, (void *)0x4000};

    eya_memory_range_exchange(&a, &b);

    EXPECT_EQ(a.begin, (void *)0x3000);
    EXPECT_EQ(a.end, (void *)0x4000);
    EXPECT_EQ(b.begin, nullptr);
    EXPECT_EQ(b.end, nullptr);
}

TEST(eya_memory_range_make, creates_range_correctly)
{
    void *begin = (void *)0x1000;
    void *end   = (void *)0x2000;

    eya_memory_range_t range = eya_memory_range_make(begin, end);

    EXPECT_EQ(range.begin, begin);
    EXPECT_EQ(range.end, end);
}

TEST(eya_memory_range_slice, creates_valid_slice)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x3000};

    eya_memory_range_t slice = eya_memory_range_slice(&range, 0x500, 0x1000);

    EXPECT_EQ(slice.begin, (void *)0x1500);
    EXPECT_EQ(slice.end, (void *)0x2500);
}

TEST(eya_memory_range_slice, fails_on_invalid_offset)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x2000};

    EXPECT_DEATH(eya_memory_range_slice(&range, 0x1001, 0), ".*");
}

TEST(eya_memory_range_slice, fails_on_invalid_size)
{
    eya_memory_range_t range = {(void *)0x1000, (void *)0x2000};

    EXPECT_DEATH(eya_memory_range_slice(&range, 0, 0x1001), ".*");
}

TEST(eya_memory_range_find_range, uninitialized_range)
{
    int                data[1] = {1};
    eya_memory_range_t view    = {nullptr, nullptr};
    EXPECT_DEATH(eya_memory_range_find_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_find_range, invalid_null_begin)
{
    int                data[1] = {1};
    int                dummy;
    eya_memory_range_t view = {nullptr, &dummy};
    EXPECT_DEATH(eya_memory_range_find_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_find_range, invalid_null_end)
{
    int                data[1] = {1};
    int                dummy;
    eya_memory_range_t view = {&dummy, nullptr};
    EXPECT_DEATH(eya_memory_range_find_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_find_range, invalid_dangling)
{
    int                data[2] = {1, 2};
    eya_memory_range_t view    = {&data[1], &data[0]};
    EXPECT_DEATH(eya_memory_range_find_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_find_range, empty_range)
{
    int                data[1] = {1};
    eya_memory_range_t view    = {&data[0], &data[0]};
    EXPECT_EQ(eya_memory_range_find_range(&view, &data[0], &data[1]), nullptr);
}

TEST(eya_memory_range_find_range, empty_search_range)
{
    int                data[4] = {1, 2, 3, 4};
    eya_memory_range_t view    = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_find_range(&view, &data[0], &data[0]), nullptr);
}

TEST(eya_memory_range_find_range, not_found)
{
    int                data[4]   = {1, 2, 3, 4};
    int                search[1] = {5};
    eya_memory_range_t view      = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_find_range(&view, &search[0], &search[1]), nullptr);
}

TEST(eya_memory_range_find_range, found_at_begin)
{
    int                data[4]   = {1, 2, 3, 4};
    int                search[1] = {1};
    eya_memory_range_t view      = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_find_range(&view, &search[0], &search[1]), &data[0]);
}

TEST(eya_memory_range_find_range, found_at_middle)
{
    int                data[4]   = {1, 2, 3, 4};
    int                search[1] = {3};
    eya_memory_range_t view      = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_find_range(&view, &search[0], &search[1]), &data[2]);
}

TEST(eya_memory_range_find_range, found_multibyte)
{
    char               data[]   = "hello world";
    char               search[] = "world";
    eya_memory_range_t view     = {&data[0], &data[sizeof(data) - 1]};
    EXPECT_EQ(eya_memory_range_find_range(&view, &search[0], &search[sizeof(search) - 1]),
              &data[6]);
}

TEST(eya_memory_range_find, uninitialized_other)
{
    int                data[1] = {1};
    eya_memory_range_t view    = {&data[0], &data[1]};
    eya_memory_range_t other   = {nullptr, nullptr};
    EXPECT_DEATH(eya_memory_range_find(&view, &other), ".*");
}

TEST(eya_memory_range_find, empty_other)
{
    int                data[4] = {1, 2, 3, 4};
    eya_memory_range_t view    = {&data[0], &data[4]};
    eya_memory_range_t other   = {&data[0], &data[0]};
    EXPECT_EQ(eya_memory_range_find(&view, &other), nullptr);
}

TEST(eya_memory_range_find, found_subview)
{
    int                data[4]    = {1, 2, 3, 4};
    int                subdata[2] = {2, 3};
    eya_memory_range_t view       = {&data[0], &data[4]};
    eya_memory_range_t other      = {&subdata[0], &subdata[2]};
    EXPECT_EQ(eya_memory_range_find(&view, &other), &data[1]);
}

TEST(eya_memory_range_rfind_range, uninitialized_range)
{
    int                data[1] = {1};
    eya_memory_range_t view    = {nullptr, nullptr};
    EXPECT_DEATH(eya_memory_range_rfind_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_rfind_range, invalid_null_begin)
{
    int                data[1] = {1};
    int                dummy;
    eya_memory_range_t view = {nullptr, &dummy};
    EXPECT_DEATH(eya_memory_range_rfind_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_rfind_range, invalid_null_end)
{
    int                data[1] = {1};
    int                dummy;
    eya_memory_range_t view = {&dummy, nullptr};
    EXPECT_DEATH(eya_memory_range_rfind_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_rfind_range, invalid_dangling)
{
    int                data[2] = {1, 2};
    eya_memory_range_t view    = {&data[1], &data[0]};
    EXPECT_DEATH(eya_memory_range_rfind_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_rfind_range, empty_range)
{
    int                data[1] = {1};
    eya_memory_range_t view    = {&data[0], &data[0]};
    EXPECT_EQ(eya_memory_range_rfind_range(&view, &data[0], &data[1]), nullptr);
}

TEST(eya_memory_range_rfind_range, empty_search_range)
{
    int                data[4] = {1, 2, 3, 4};
    eya_memory_range_t view    = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_rfind_range(&view, &data[0], &data[0]), nullptr);
}

TEST(eya_memory_range_rfind_range, not_found)
{
    int                data[4]   = {1, 2, 3, 4};
    int                search[1] = {5};
    eya_memory_range_t view      = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_rfind_range(&view, &search[0], &search[1]), nullptr);
}

TEST(eya_memory_range_rfind_range, found_at_begin)
{
    int                data[4]   = {1, 2, 1, 4};
    int                search[1] = {1};
    eya_memory_range_t view      = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_rfind_range(&view, &search[0], &search[1]), &data[2]);
}

TEST(eya_memory_range_rfind_range, found_at_end)
{
    int                data[4]   = {1, 2, 3, 4};
    int                search[1] = {4};
    eya_memory_range_t view      = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_rfind_range(&view, &search[0], &search[1]), &data[3]);
}

TEST(eya_memory_range_rfind_range, found_multibyte)
{
    char               data[]   = "hello world world";
    char               search[] = "world";
    eya_memory_range_t view     = {&data[0], &data[sizeof(data) - 1]};
    EXPECT_EQ(eya_memory_range_rfind_range(&view, &search[0], &search[sizeof(search) - 1]),
              &data[12]);
}

TEST(eya_memory_range_rfind, uninitialized_other)
{
    int                data[1] = {1};
    eya_memory_range_t view    = {&data[0], &data[1]};
    eya_memory_range_t other   = {nullptr, nullptr};
    EXPECT_DEATH(eya_memory_range_rfind(&view, &other), ".*");
}

TEST(eya_memory_range_rfind, empty_other)
{
    int                data[4] = {1, 2, 3, 4};
    eya_memory_range_t view    = {&data[0], &data[4]};
    eya_memory_range_t other   = {&data[0], &data[0]};
    EXPECT_EQ(eya_memory_range_rfind(&view, &other), nullptr);
}

TEST(eya_memory_range_rfind, found_last_subview)
{
    int                data[6]    = {1, 2, 3, 2, 3, 4};
    int                subdata[2] = {2, 3};
    eya_memory_range_t view       = {&data[0], &data[6]};
    eya_memory_range_t other      = {&subdata[0], &subdata[2]};
    EXPECT_EQ(eya_memory_range_rfind(&view, &other), &data[3]);
}

TEST(eya_memory_range_rfind, identical_ranges)
{
    int                data[4] = {1, 2, 3, 4};
    eya_memory_range_t view    = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_rfind(&view, &view), &data[0]);
}

TEST(eya_memory_range_compare_range, invalid_null_end)
{
    int                data[1] = {1};
    int                dummy;
    eya_memory_range_t view = {&dummy, nullptr};
    EXPECT_DEATH(eya_memory_range_compare_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_compare_range, invalid_dangling)
{
    int                data[2] = {1, 2};
    eya_memory_range_t view    = {&data[1], &data[0]};
    EXPECT_DEATH(eya_memory_range_compare_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_compare_range, empty_range)
{
    int                data[1] = {1};
    eya_memory_range_t view    = {&data[0], &data[0]};
    EXPECT_EQ(eya_memory_range_compare_range(&view, &data[0], &data[1]), nullptr);
}

TEST(eya_memory_range_compare_range, empty_compare_range)
{
    int                data[4] = {1, 2, 3, 4};
    eya_memory_range_t view    = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_compare_range(&view, &data[0], &data[0]), nullptr);
}

TEST(eya_memory_range_compare_range, identical_content)
{
    int                data[4]    = {1, 2, 3, 4};
    int                compare[4] = {1, 2, 3, 4};
    eya_memory_range_t view       = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_compare_range(&view, &compare[0], &compare[4]), nullptr);
}

TEST(eya_memory_range_compare_range, different_content)
{
    int                data[4]    = {1, 2, 3, 4};
    int                compare[4] = {1, 2, 0, 4};
    eya_memory_range_t view       = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_compare_range(&view, &compare[0], &compare[4]), &data[2]);
}

TEST(eya_memory_range_compare_range, multibyte_string)
{
    char               data[]    = "hello world";
    char               compare[] = "hello there";
    eya_memory_range_t view      = {&data[0], &data[sizeof(data) - 1]};
    EXPECT_EQ(eya_memory_range_compare_range(&view, &compare[0], &compare[sizeof(compare) - 1]),
              &data[6]);
}

TEST(eya_memory_range_compare, uninitialized_other)
{
    int                data[1] = {1};
    eya_memory_range_t view    = {&data[0], &data[1]};
    eya_memory_range_t other   = {nullptr, nullptr};
    EXPECT_DEATH(eya_memory_range_compare(&view, &other), ".*");
}

TEST(eya_memory_range_compare, empty_other)
{
    int                data[4] = {1, 2, 3, 4};
    eya_memory_range_t view    = {&data[0], &data[4]};
    eya_memory_range_t other   = {&data[0], &data[0]};
    EXPECT_EQ(eya_memory_range_compare(&view, &other), nullptr);
}

TEST(eya_memory_range_compare, identical_ranges)
{
    int                data[4] = {1, 2, 3, 4};
    eya_memory_range_t view    = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_compare(&view, &view), nullptr);
}

TEST(eya_memory_range_compare, different_ranges)
{
    int                data[4]       = {1, 2, 3, 4};
    int                other_data[4] = {1, 2, 0, 4};
    eya_memory_range_t view          = {&data[0], &data[4]};
    eya_memory_range_t other         = {&other_data[0], &other_data[4]};
    EXPECT_EQ(eya_memory_range_compare(&view, &other), &data[2]);
}

TEST(eya_memory_range_rcompare_range, invalid_null_end)
{
    int                data[1] = {1};
    int                dummy;
    eya_memory_range_t view = {&dummy, nullptr};
    EXPECT_DEATH(eya_memory_range_rcompare_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_rcompare_range, invalid_dangling)
{
    int                data[2] = {1, 2};
    eya_memory_range_t view    = {&data[1], &data[0]};
    EXPECT_DEATH(eya_memory_range_rcompare_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_rcompare_range, empty_range)
{
    int                data[1] = {1};
    eya_memory_range_t view    = {&data[0], &data[0]};
    EXPECT_EQ(eya_memory_range_rcompare_range(&view, &data[0], &data[1]), nullptr);
}

TEST(eya_memory_range_rcompare_range, empty_compare_range)
{
    int                data[4] = {1, 2, 3, 4};
    eya_memory_range_t view    = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_rcompare_range(&view, &data[0], &data[0]), nullptr);
}

TEST(eya_memory_range_rcompare_range, identical_content)
{
    int                data[4]    = {1, 2, 3, 4};
    int                compare[4] = {1, 2, 3, 4};
    eya_memory_range_t view       = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_rcompare_range(&view, &compare[0], &compare[4]), nullptr);
}

TEST(eya_memory_range_rcompare_range, different_content)
{
    int                data[4]    = {1, 2, 3, 4};
    int                compare[4] = {1, 2, 3, 0};
    eya_memory_range_t view       = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_rcompare_range(&view, &compare[0], &compare[4]), &data[3]);
}

TEST(eya_memory_range_rcompare_range, multibyte_string)
{
    char               data[]    = "hello world";
    char               compare[] = "world hello";
    eya_memory_range_t view      = {&data[0], &data[sizeof(data) - 1]};
    EXPECT_EQ(eya_memory_range_rcompare_range(&view, &compare[0], &compare[sizeof(compare) - 1]),
              &data[10]);
}

TEST(eya_memory_range_rcompare, uninitialized_other)
{
    int                data[1] = {1};
    eya_memory_range_t view    = {&data[0], &data[1]};
    eya_memory_range_t other   = {nullptr, nullptr};
    EXPECT_DEATH(eya_memory_range_rcompare(&view, &other), ".*");
}

TEST(eya_memory_range_rcompare, empty_other)
{
    int                data[4] = {1, 2, 3, 4};
    eya_memory_range_t view    = {&data[0], &data[4]};
    eya_memory_range_t other   = {&data[0], &data[0]};
    EXPECT_EQ(eya_memory_range_rcompare(&view, &other), nullptr);
}

TEST(eya_memory_range_rcompare, identical_ranges)
{
    int                data[4] = {1, 2, 3, 4};
    eya_memory_range_t view    = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_rcompare(&view, &view), nullptr);
}

TEST(eya_memory_range_rcompare, different_ranges)
{
    int                data[4]       = {1, 2, 3, 4};
    int                other_data[4] = {1, 2, 3, 0};
    eya_memory_range_t view          = {&data[0], &data[4]};
    eya_memory_range_t other         = {&other_data[0], &other_data[4]};
    EXPECT_EQ(eya_memory_range_rcompare(&view, &other), &data[3]);
}

TEST(eya_memory_range_copy_range, invalid_null_end)
{
    int                data[1] = {1};
    int                dummy;
    eya_memory_range_t view = {&dummy, nullptr};
    EXPECT_DEATH(eya_memory_range_copy_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_copy_range, invalid_dangling)
{
    int                data[2] = {1, 2};
    eya_memory_range_t view    = {&data[1], &data[0]};
    EXPECT_DEATH(eya_memory_range_copy_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_copy_range, empty_range)
{
    int                data[1] = {1};
    int                src[1]  = {2};
    eya_memory_range_t view    = {&data[0], &data[0]};
    EXPECT_EQ(eya_memory_range_copy_range(&view, &src[0], &src[0]), &data[0]);
}

TEST(eya_memory_range_copy_range, copy_valid_data)
{
    int                data[4] = {0, 0, 0, 0};
    int                src[4]  = {1, 2, 3, 4};
    eya_memory_range_t view    = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_copy_range(&view, &src[0], &src[4]), &data[4]);
    EXPECT_EQ(data[0], 1);
    EXPECT_EQ(data[1], 2);
    EXPECT_EQ(data[2], 3);
    EXPECT_EQ(data[3], 4);
}

TEST(eya_memory_range_copy, invalid_null_end)
{
    int                data[1] = {1};
    int                dummy;
    eya_memory_range_t view  = {&dummy, nullptr};
    eya_memory_range_t other = {&data[0], &data[1]};
    EXPECT_DEATH(eya_memory_range_copy(&view, &other), ".*");
}

TEST(eya_memory_range_copy, empty_other)
{
    int                data[4] = {1, 2, 3, 4};
    int                src[1]  = {5};
    eya_memory_range_t view    = {&data[0], &data[4]};
    eya_memory_range_t other   = {&src[0], &src[0]};
    EXPECT_EQ(eya_memory_range_copy(&view, &other), &data[0]);
}

TEST(eya_memory_range_copy, copy_valid_data)
{
    int                data[4] = {0, 0, 0, 0};
    int                src[4]  = {1, 2, 3, 4};
    eya_memory_range_t view    = {&data[0], &data[4]};
    eya_memory_range_t other   = {&src[0], &src[4]};
    EXPECT_EQ(eya_memory_range_copy(&view, &other), &data[4]);
    EXPECT_EQ(data[0], 1);
    EXPECT_EQ(data[1], 2);
    EXPECT_EQ(data[2], 3);
    EXPECT_EQ(data[3], 4);
}

TEST(eya_memory_range_copy_rev_range, small_range_copy)
{
    static const char  src[]            = "Hello, world!";
    char               dst[sizeof(src)] = {};
    eya_memory_range_t self             = {dst, dst + sizeof(src)};

    void *ret = eya_memory_range_copy_rev_range(&self, src, src + sizeof(src));
    EXPECT_EQ(ret, dst + sizeof(src));
    for (size_t i = 0; i < sizeof(src); ++i)
    {
        EXPECT_EQ(dst[i], src[sizeof(src) - 1 - i]);
    }
}

TEST(eya_memory_range_copy_rev_range, large_range_copy)
{
    static const size_t size = 1024 * 1024;
    std::vector<char>   src(size, 0); // Heap allocation
    std::vector<char>   dst(size, 0); // Heap allocation

    eya_memory_range_t self = {dst.data(), dst.data() + size};
    eya_memory_range_set(&self, 0);

    for (size_t i = 0; i < size; ++i)
    {
        src[i] = static_cast<char>(i & 0xFF);
    }

    void *ret = eya_memory_range_copy_rev_range(&self, src.data(), src.data() + size);
    EXPECT_EQ(ret, dst.data() + size);

    for (size_t i = 0; i < size; ++i)
    {
        EXPECT_EQ(dst[i], src[size - 1 - i]);
    }
}

TEST(eya_memory_range_copy_rev_range, one_byte_copy)
{
    static const char  src[]  = {42};
    char               dst[1] = {};
    eya_memory_range_t self   = {dst, dst + 1};

    void *ret = eya_memory_range_copy_rev_range(&self, src, src + 1);
    EXPECT_EQ(ret, dst + 1);
    EXPECT_EQ(dst[0], src[0]);
}

TEST(eya_memory_range_copy_rev_range, nullptr_self)
{
    static const char src[] = "data";
    EXPECT_DEATH(eya_memory_range_copy_rev_range(nullptr, src, src + sizeof(src)), ".*");
}

TEST(eya_memory_range_copy_rev_range, nullptr_end)
{
    char               dst[10];
    eya_memory_range_t self  = {dst, dst + 10};
    static const char  src[] = "data";
    EXPECT_DEATH(eya_memory_range_copy_rev_range(&self, src, nullptr), ".*");
}

TEST(eya_memory_range_copy_rev_range, zero_length_range)
{
    static const char  src[]            = "Test data";
    char               dst[sizeof(src)] = {};
    eya_memory_range_t self             = {dst, dst};

    void *ret = eya_memory_range_copy_rev_range(&self, src, src);
    EXPECT_EQ(ret, dst);
}

TEST(eya_memory_range_copy_rev, small_range_copy)
{
    static const char  src[]            = "Hello, world!";
    char               dst[sizeof(src)] = {};
    eya_memory_range_t self             = {dst, dst + sizeof(src)};
    eya_memory_range_t other            = {(void *)src, (void *)(src + sizeof(src))};

    void *ret = eya_memory_range_copy_rev(&self, &other);
    EXPECT_EQ(ret, dst + sizeof(src));
    for (size_t i = 0; i < sizeof(src); ++i)
    {
        EXPECT_EQ(dst[i], src[sizeof(src) - 1 - i]);
    }
}

TEST(eya_memory_range_copy_rev, large_range_copy)
{
    static const size_t size      = 1024 * 1024;
    static char         src[size] = {}; // Static, in data segment
    std::vector<char>   dst(size, 0);   // Heap allocation

    eya_memory_range_t self = {dst.data(), dst.data() + size};
    eya_memory_range_set(&self, 0);
    eya_memory_range_t other = {src, src + size};

    for (size_t i = 0; i < size; ++i)
    {
        src[i] = static_cast<char>(i & 0xFF);
    }

    void *ret = eya_memory_range_copy_rev(&self, &other);
    EXPECT_EQ(ret, dst.data() + size);
    for (size_t i = 0; i < size; ++i)
    {
        EXPECT_EQ(dst[i], src[size - 1 - i]);
    }
}

TEST(eya_memory_range_copy_rev, one_byte_copy)
{
    static const char  src[]  = {42};
    char               dst[1] = {};
    eya_memory_range_t self   = {dst, dst + 1};
    eya_memory_range_t other  = {(void *)src, (void *)(src + 1)};

    void *ret = eya_memory_range_copy_rev(&self, &other);
    EXPECT_EQ(ret, dst + 1);
    EXPECT_EQ(dst[0], src[0]);
}

TEST(eya_memory_range_copy_rev, nullptr_other)
{
    char               dst[10];
    eya_memory_range_t self = {dst, dst + 10};
    EXPECT_DEATH(eya_memory_range_copy_rev(&self, nullptr), ".*");
}

TEST(eya_memory_range_copy_rev, return_pointer_is_end_of_copied_range)
{
    static const char  src[]            = "Test data";
    char               dst[sizeof(src)] = {};
    eya_memory_range_t self             = {dst, dst + sizeof(src)};
    eya_memory_range_t other            = {(void *)src, (void *)(src + sizeof(src))};

    void *ret = eya_memory_range_copy_rev(&self, &other);
    EXPECT_EQ(ret, dst + sizeof(src));
}

TEST(eya_memory_range_copy_rev, zero_length_range)
{
    static const char src[]            = "Test data";
    char              dst[sizeof(src)] = {};

    eya_memory_range_t self  = {dst, dst};
    eya_memory_range_t other = {(void *)src, (void *)src};

    void *ret = eya_memory_range_copy_rev(&self, &other);
    EXPECT_EQ(ret, dst);
}

TEST(eya_memory_range_rcopy_range, invalid_null_end)
{
    int                data[1] = {1};
    int                dummy;
    eya_memory_range_t view = {&dummy, nullptr};
    EXPECT_DEATH(eya_memory_range_rcopy_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_rcopy_range, invalid_dangling)
{
    int                data[2] = {1, 2};
    eya_memory_range_t view    = {&data[1], &data[0]};
    EXPECT_DEATH(eya_memory_range_rcopy_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_rcopy_range, empty_range)
{
    int                data[1] = {1};
    int                src[1]  = {2};
    eya_memory_range_t view    = {&data[0], &data[0]};
    EXPECT_EQ(eya_memory_range_rcopy_range(&view, &src[0], &src[0]), &data[0]);
}

TEST(eya_memory_range_rcopy_range, copy_valid_data)
{
    int                data[4] = {0, 0, 0, 0};
    int                src[4]  = {1, 2, 3, 4};
    eya_memory_range_t view    = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_rcopy_range(&view, &src[0], &src[4]), &data[0]);
    EXPECT_EQ(data[0], 1);
    EXPECT_EQ(data[1], 2);
    EXPECT_EQ(data[2], 3);
    EXPECT_EQ(data[3], 4);
}

TEST(eya_memory_range_rcopy, invalid_null_end)
{
    int                data[1] = {1};
    int                dummy;
    eya_memory_range_t view  = {&dummy, nullptr};
    eya_memory_range_t other = {&data[0], &data[1]};
    EXPECT_DEATH(eya_memory_range_rcopy(&view, &other), ".*");
}

TEST(eya_memory_range_rcopy, empty_other)
{
    int                data[4] = {1, 2, 3, 4};
    int                src[1]  = {5};
    eya_memory_range_t view    = {&data[0], &data[4]};
    eya_memory_range_t other   = {&src[0], &src[0]};
    EXPECT_EQ(eya_memory_range_rcopy(&view, &other), &data[0]);
}

TEST(eya_memory_range_rcopy, copy_valid_data)
{
    int                data[4] = {0, 0, 0, 0};
    int                src[4]  = {1, 2, 3, 4};
    eya_memory_range_t view    = {&data[0], &data[4]};
    eya_memory_range_t other   = {&src[0], &src[4]};
    EXPECT_EQ(eya_memory_range_rcopy(&view, &other), &data[0]);
    EXPECT_EQ(data[0], 1);
    EXPECT_EQ(data[1], 2);
    EXPECT_EQ(data[2], 3);
    EXPECT_EQ(data[3], 4);
}

TEST(eya_memory_range_move_range, invalid_null_end)
{
    int                data[1] = {1};
    int                dummy;
    eya_memory_range_t view = {&dummy, nullptr};
    EXPECT_DEATH(eya_memory_range_move_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_move_range, invalid_dangling)
{
    int                data[2] = {1, 2};
    eya_memory_range_t view    = {&data[1], &data[0]};
    EXPECT_DEATH(eya_memory_range_move_range(&view, &data[0], &data[1]), ".*");
}

TEST(eya_memory_range_move_range, empty_range)
{
    int                data[1] = {1};
    int                src[1]  = {2};
    eya_memory_range_t view    = {&data[0], &data[0]};
    EXPECT_EQ(eya_memory_range_move_range(&view, &src[0], &src[0]), &data[0]);
}

TEST(eya_memory_range_move_range, move_valid_data)
{
    int                data[4] = {0, 0, 0, 0};
    int                src[4]  = {1, 2, 3, 4};
    eya_memory_range_t view    = {&data[0], &data[4]};
    EXPECT_EQ(eya_memory_range_move_range(&view, &src[0], &src[4]), &data[4]);
    EXPECT_EQ(data[0], 1);
    EXPECT_EQ(data[1], 2);
    EXPECT_EQ(data[2], 3);
    EXPECT_EQ(data[3], 4);
}

TEST(eya_memory_range_move, invalid_null_end)
{
    int                data[1] = {1};
    int                dummy;
    eya_memory_range_t view  = {&dummy, nullptr};
    eya_memory_range_t other = {&data[0], &data[1]};
    EXPECT_DEATH(eya_memory_range_move(&view, &other), ".*");
}

TEST(eya_memory_range_move, empty_other)
{
    int                data[4] = {1, 2, 3, 4};
    int                src[1]  = {5};
    eya_memory_range_t view    = {&data[0], &data[4]};
    eya_memory_range_t other   = {&src[0], &src[0]};
    EXPECT_EQ(eya_memory_range_move(&view, &other), &data[0]);
}

TEST(eya_memory_range_move, move_valid_data)
{
    int                data[4] = {0, 0, 0, 0};
    int                src[4]  = {1, 2, 3, 4};
    eya_memory_range_t view    = {&data[0], &data[4]};
    eya_memory_range_t other   = {&src[0], &src[4]};
    EXPECT_EQ(eya_memory_range_move(&view, &other), &data[4]);
    EXPECT_EQ(data[0], 1);
    EXPECT_EQ(data[1], 2);
    EXPECT_EQ(data[2], 3);
    EXPECT_EQ(data[3], 4);
}

TEST(eya_memory_range_set, sets_memory_with_given_value)
{
    constexpr size_t size         = 10;
    unsigned char    buffer[size] = {0};

    eya_memory_range_t range = {buffer, buffer + size};

    unsigned char test_value = 0xAB;
    void         *result     = eya_memory_range_set(&range, test_value);

    EXPECT_EQ(result, buffer + size);

    for (unsigned char i : buffer)
    {
        EXPECT_EQ(i, test_value);
    }
}

TEST(eya_memory_range_set, handles_empty_range)
{
    void              *ptr   = (void *)0x1000;
    eya_memory_range_t range = {ptr, ptr};

    unsigned char test_value = 0xAB;
    void         *result     = eya_memory_range_set(&range, test_value);

    EXPECT_EQ(result, ptr);
}

TEST(eya_memory_range_set, handles_null_self_pointer_gracefully)
{
    unsigned char test_value = 0xAB;
    EXPECT_DEATH(eya_memory_range_set(nullptr, test_value), ".*");
}

TEST(eya_memory_range_set, fails_on_uninitialized_range)
{
    eya_memory_range_t range      = {nullptr, nullptr};
    unsigned char      test_value = 0xAB;
    EXPECT_DEATH(eya_memory_range_set(&range, test_value), ".*");
}

TEST(eya_memory_range_set, fails_on_invalid_null_begin_range)
{
    eya_memory_range_t range      = {nullptr, (void *)0x2000};
    unsigned char      test_value = 0xAB;
    EXPECT_DEATH(eya_memory_range_set(&range, test_value), ".*");
}

TEST(eya_memory_range_set, fails_on_invalid_null_end_range)
{
    eya_memory_range_t range      = {(void *)0x1000, nullptr};
    unsigned char      test_value = 0xAB;
    EXPECT_DEATH(eya_memory_range_set(&range, test_value), ".*");
}

TEST(eya_memory_range_set, fails_on_dangling_range)
{
    eya_memory_range_t range      = {(void *)0x2000, (void *)0x1000};
    unsigned char      test_value = 0xAB;
    EXPECT_DEATH(eya_memory_range_set(&range, test_value), ".*");
}

TEST(eya_memory_range_set, sets_zero_value_correctly)
{
    constexpr size_t size         = 5;
    unsigned char    buffer[size] = {0x01, 0x02, 0x03, 0x04, 0x05};

    eya_memory_range_t range  = {buffer, buffer + size};
    void              *result = eya_memory_range_set(&range, 0);

    EXPECT_EQ(result, buffer + size);

    for (unsigned char i : buffer)
    {
        EXPECT_EQ(i, 0);
    }
}

TEST(eya_memory_range_set, sets_max_value_correctly)
{
    constexpr size_t size         = 3;
    unsigned char    buffer[size] = {0};

    eya_memory_range_t range = {buffer, buffer + size};

    unsigned char max_value = 0xFF;
    void         *result    = eya_memory_range_set(&range, max_value);

    EXPECT_EQ(result, buffer + size);

    for (unsigned char i : buffer)
    {
        EXPECT_EQ(i, max_value);
    }
}

TEST(eya_memory_range_set_value, sets_value_at_forward_offset)
{
    constexpr size_t size         = 5;
    unsigned char    buffer[size] = {0x01, 0x02, 0x03, 0x04, 0x05};

    eya_memory_range_t range = {buffer, buffer + size};

    unsigned char test_value = 0xAB;
    eya_memory_range_set_value(&range, 2, false, test_value);

    EXPECT_EQ(buffer[2], test_value);
    EXPECT_EQ(buffer[0], 0x01);
    EXPECT_EQ(buffer[1], 0x02);
    EXPECT_EQ(buffer[3], 0x04);
    EXPECT_EQ(buffer[4], 0x05);
}

TEST(eya_memory_range_set_value, sets_value_at_reversed_offset)
{
    constexpr size_t size         = 5;
    unsigned char    buffer[size] = {0x01, 0x02, 0x03, 0x04, 0x05};

    eya_memory_range_t range = {buffer, buffer + size};

    unsigned char test_value = 0xCD;
    eya_memory_range_set_value(&range, 1, true, test_value);

    EXPECT_EQ(buffer[3], test_value);
    EXPECT_EQ(buffer[0], 0x01);
    EXPECT_EQ(buffer[1], 0x02);
    EXPECT_EQ(buffer[2], 0x03);
    EXPECT_EQ(buffer[4], 0x05);
}

TEST(eya_memory_range_set_value, sets_value_at_zero_offset_forward)
{
    constexpr size_t size         = 3;
    unsigned char    buffer[size] = {0x10, 0x20, 0x30};

    eya_memory_range_t range = {buffer, buffer + size};

    unsigned char test_value = 0x99;
    eya_memory_range_set_value(&range, 0, false, test_value);

    EXPECT_EQ(buffer[0], test_value);
    EXPECT_EQ(buffer[1], 0x20);
    EXPECT_EQ(buffer[2], 0x30);
}

TEST(eya_memory_range_set_value, sets_value_at_zero_offset_reversed)
{
    constexpr size_t size         = 3;
    unsigned char    buffer[size] = {0x10, 0x20, 0x30};

    eya_memory_range_t range = {buffer, buffer + size};

    unsigned char test_value = 0x77;
    eya_memory_range_set_value(&range, 0, true, test_value);

    EXPECT_EQ(buffer[2], test_value);
    EXPECT_EQ(buffer[0], 0x10);
    EXPECT_EQ(buffer[1], 0x20);
}

TEST(eya_memory_range_set_value, handles_null_self_pointer_gracefully)
{
    unsigned char test_value = 0xAB;
    EXPECT_DEATH(eya_memory_range_set_value(nullptr, 0, false, test_value), ".*");
}

TEST(eya_memory_range_set_value, fails_on_uninitialized_range)
{
    eya_memory_range_t range      = {nullptr, nullptr};
    unsigned char      test_value = 0xAB;
    EXPECT_DEATH(eya_memory_range_set_value(&range, 0, false, test_value), ".*");
}

TEST(eya_memory_range_set_value, fails_on_invalid_null_begin_range)
{
    eya_memory_range_t range      = {nullptr, (void *)0x2000};
    unsigned char      test_value = 0xAB;
    EXPECT_DEATH(eya_memory_range_set_value(&range, 0, false, test_value), ".*");
}

TEST(eya_memory_range_set_value, fails_on_invalid_null_end_range)
{
    eya_memory_range_t range      = {(void *)0x1000, nullptr};
    unsigned char      test_value = 0xAB;
    EXPECT_DEATH(eya_memory_range_set_value(&range, 0, false, test_value), ".*");
}

TEST(eya_memory_range_set_value, fails_on_dangling_range)
{
    eya_memory_range_t range      = {(void *)0x2000, (void *)0x1000};
    unsigned char      test_value = 0xAB;
    EXPECT_DEATH(eya_memory_range_set_value(&range, 0, false, test_value), ".*");
}

TEST(eya_memory_range_set_value, fails_on_empty_range_forward)
{
    void              *ptr        = (void *)0x1000;
    eya_memory_range_t range      = {ptr, ptr};
    unsigned char      test_value = 0xAB;
    EXPECT_DEATH(eya_memory_range_set_value(&range, 0, false, test_value), ".*");
}

TEST(eya_memory_range_set_value, fails_on_empty_range_reversed)
{
    void              *ptr        = (void *)0x1000;
    eya_memory_range_t range      = {ptr, ptr};
    unsigned char      test_value = 0xAB;
    EXPECT_DEATH(eya_memory_range_set_value(&range, 0, true, test_value), ".*");
}

TEST(eya_memory_range_set_value, fails_on_offset_exceeding_size_forward)
{
    constexpr size_t size         = 3;
    unsigned char    buffer[size] = {0x01, 0x02, 0x03};

    eya_memory_range_t range      = {buffer, buffer + size};
    unsigned char      test_value = 0xAB;

    EXPECT_DEATH(eya_memory_range_set_value(&range, size, false, test_value), ".*");
    EXPECT_DEATH(eya_memory_range_set_value(&range, size + 1, false, test_value), ".*");
}

TEST(eya_memory_range_set_value, fails_on_offset_exceeding_size_reversed)
{
    constexpr size_t size         = 3;
    unsigned char    buffer[size] = {0x01, 0x02, 0x03};

    eya_memory_range_t range      = {buffer, buffer + size};
    unsigned char      test_value = 0xAB;

    EXPECT_DEATH(eya_memory_range_set_value(&range, size, true, test_value), ".*");
    EXPECT_DEATH(eya_memory_range_set_value(&range, size + 1, true, test_value), ".*");
}

TEST(eya_memory_range_set_value, sets_max_value_correctly)
{
    constexpr size_t size         = 4;
    unsigned char    buffer[size] = {0};

    eya_memory_range_t range = {buffer, buffer + size};

    unsigned char max_value = 0xFF;
    eya_memory_range_set_value(&range, 2, false, max_value);

    EXPECT_EQ(buffer[2], max_value);
}

TEST(eya_memory_range_set_value, sets_zero_value_correctly)
{
    constexpr size_t size         = 4;
    unsigned char    buffer[size] = {0xFF, 0xFF, 0xFF, 0xFF};

    eya_memory_range_t range = {buffer, buffer + size};
    eya_memory_range_set_value(&range, 1, false, 0);

    EXPECT_EQ(buffer[1], 0);
    EXPECT_EQ(buffer[0], 0xFF);
    EXPECT_EQ(buffer[2], 0xFF);
    EXPECT_EQ(buffer[3], 0xFF);
}

TEST(eya_memory_range_set_value, sets_value_at_last_position_forward)
{
    constexpr size_t size         = 5;
    unsigned char    buffer[size] = {0x10, 0x20, 0x30, 0x40, 0x50};

    eya_memory_range_t range = {buffer, buffer + size};

    unsigned char test_value = 0x99;
    eya_memory_range_set_value(&range, size - 1, false, test_value);

    EXPECT_EQ(buffer[size - 1], test_value);
    EXPECT_EQ(buffer[0], 0x10);
    EXPECT_EQ(buffer[1], 0x20);
    EXPECT_EQ(buffer[2], 0x30);
    EXPECT_EQ(buffer[3], 0x40);
}

TEST(eya_memory_range_set_value, sets_value_at_last_position_reversed)
{
    constexpr size_t size         = 5;
    unsigned char    buffer[size] = {0x10, 0x20, 0x30, 0x40, 0x50};

    eya_memory_range_t range = {buffer, buffer + size};

    unsigned char test_value = 0x99;
    eya_memory_range_set_value(&range, size - 1, true, test_value);

    EXPECT_EQ(buffer[0], test_value);
    EXPECT_EQ(buffer[1], 0x20);
    EXPECT_EQ(buffer[2], 0x30);
    EXPECT_EQ(buffer[3], 0x40);
    EXPECT_EQ(buffer[4], 0x50);
}

TEST(eya_memory_range_set_pattern, sets_pattern_from_valid_range)
{
    constexpr size_t size         = 10;
    unsigned char    buffer[size] = {0};

    unsigned char      pattern_data[] = {0x01, 0x02, 0x03};
    eya_memory_range_t pattern        = {pattern_data, pattern_data + sizeof(pattern_data)};

    eya_memory_range_t range  = {buffer, buffer + size};
    void              *result = eya_memory_range_set_pattern(&range, &pattern);

    EXPECT_EQ(result, buffer + size);
    for (size_t i = 0; i < size; ++i)
    {
        EXPECT_EQ(buffer[i], pattern_data[i % sizeof(pattern_data)]);
    }
}

TEST(eya_memory_range_set_pattern, sets_single_byte_pattern)
{
    constexpr size_t size         = 5;
    unsigned char    buffer[size] = {0};

    unsigned char      pattern_data[] = {0xAA};
    eya_memory_range_t pattern        = {pattern_data, pattern_data + 1};

    eya_memory_range_t range  = {buffer, buffer + size};
    void              *result = eya_memory_range_set_pattern(&range, &pattern);

    EXPECT_EQ(result, buffer + size);
    for (unsigned char i : buffer)
    {
        EXPECT_EQ(i, 0xAA);
    }
}

TEST(eya_memory_range_set_pattern, handles_empty_target_range)
{
    void              *ptr   = (void *)0x1000;
    eya_memory_range_t range = {ptr, ptr};

    unsigned char      pattern_data[] = {0x01, 0x02};
    eya_memory_range_t pattern        = {pattern_data, pattern_data + 2};

    void *result = eya_memory_range_set_pattern(&range, &pattern);
    EXPECT_EQ(result, nullptr);
}

TEST(eya_memory_range_set_pattern, handles_empty_pattern_range)
{
    constexpr size_t size         = 5;
    unsigned char    buffer[size] = {0x10, 0x20, 0x30, 0x40, 0x50};

    void              *ptr     = (void *)0x1000;
    eya_memory_range_t pattern = {ptr, ptr};
    eya_memory_range_t range   = {buffer, buffer + size};
    EXPECT_EQ(eya_memory_range_set_pattern(&range, &pattern), nullptr);
}

TEST(eya_memory_range_set_pattern, handles_null_self_pointer_gracefully)
{
    unsigned char      pattern_data[] = {0x01, 0x02};
    eya_memory_range_t pattern        = {pattern_data, pattern_data + 2};

    EXPECT_DEATH(eya_memory_range_set_pattern(nullptr, &pattern), ".*");
}

TEST(eya_memory_range_set_pattern, handles_null_other_pointer_gracefully)
{
    constexpr size_t   size         = 5;
    unsigned char      buffer[size] = {0};
    eya_memory_range_t range        = {buffer, buffer + size};

    EXPECT_DEATH(eya_memory_range_set_pattern(&range, nullptr), ".*");
}

TEST(eya_memory_range_set_pattern, fails_on_uninitialized_self_range)
{
    eya_memory_range_t range = {nullptr, nullptr};

    unsigned char      pattern_data[] = {0x01, 0x02};
    eya_memory_range_t pattern        = {pattern_data, pattern_data + 2};

    EXPECT_DEATH(eya_memory_range_set_pattern(&range, &pattern), ".*");
}

TEST(eya_memory_range_set_pattern, fails_on_uninitialized_other_range)
{
    constexpr size_t   size         = 5;
    unsigned char      buffer[size] = {0};
    eya_memory_range_t range        = {buffer, buffer + size};

    eya_memory_range_t pattern = {nullptr, nullptr};

    EXPECT_DEATH(eya_memory_range_set_pattern(&range, &pattern), ".*");
}

TEST(eya_memory_range_set_pattern, fails_on_invalid_null_begin_self_range)
{
    eya_memory_range_t range = {nullptr, (void *)0x2000};

    unsigned char      pattern_data[] = {0x01, 0x02};
    eya_memory_range_t pattern        = {pattern_data, pattern_data + 2};

    EXPECT_DEATH(eya_memory_range_set_pattern(&range, &pattern), ".*");
}

TEST(eya_memory_range_set_pattern, fails_on_invalid_null_end_self_range)
{
    eya_memory_range_t range = {(void *)0x1000, nullptr};

    unsigned char      pattern_data[] = {0x01, 0x02};
    eya_memory_range_t pattern        = {pattern_data, pattern_data + 2};

    EXPECT_DEATH(eya_memory_range_set_pattern(&range, &pattern), ".*");
}

TEST(eya_memory_range_set_pattern, fails_on_dangling_self_range)
{
    eya_memory_range_t range = {(void *)0x2000, (void *)0x1000};

    unsigned char      pattern_data[] = {0x01, 0x02};
    eya_memory_range_t pattern        = {pattern_data, pattern_data + 2};

    EXPECT_DEATH(eya_memory_range_set_pattern(&range, &pattern), ".*");
}

TEST(eya_memory_range_set_pattern, fails_on_invalid_null_begin_other_range)
{
    constexpr size_t   size         = 5;
    unsigned char      buffer[size] = {0};
    eya_memory_range_t range        = {buffer, buffer + size};

    eya_memory_range_t pattern = {nullptr, (void *)0x2000};
    EXPECT_DEATH(eya_memory_range_set_pattern(&range, &pattern), ".*");
}

TEST(eya_memory_range_set_pattern, fails_on_invalid_null_end_other_range)
{
    constexpr size_t   size         = 5;
    unsigned char      buffer[size] = {0};
    eya_memory_range_t range        = {buffer, buffer + size};

    eya_memory_range_t pattern = {(void *)0x1000, nullptr};
    EXPECT_DEATH(eya_memory_range_set_pattern(&range, &pattern), ".*");
}

TEST(eya_memory_range_set_pattern, fails_on_dangling_other_range)
{
    constexpr size_t   size         = 5;
    unsigned char      buffer[size] = {0};
    eya_memory_range_t range        = {buffer, buffer + size};

    unsigned char      pattern_data[2] = {0x01, 0x02};
    eya_memory_range_t pattern         = {pattern_data + 1, pattern_data};

    EXPECT_DEATH(eya_memory_range_set_pattern(&range, &pattern), ".*");
}

TEST(eya_memory_range_set_pattern, pattern_size_larger_than_target)
{
    constexpr size_t size         = 3;
    unsigned char    buffer[size] = {0};

    unsigned char      pattern_data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    eya_memory_range_t pattern        = {pattern_data, pattern_data + 5};

    eya_memory_range_t range  = {buffer, buffer + size};
    void              *result = eya_memory_range_set_pattern(&range, &pattern);

    EXPECT_EQ(result, buffer + size);
    EXPECT_EQ(buffer[0], 0x01);
    EXPECT_EQ(buffer[1], 0x02);
    EXPECT_EQ(buffer[2], 0x03);
}

TEST(eya_memory_range_set_pattern, pattern_size_exactly_target_size)
{
    constexpr size_t size         = 4;
    unsigned char    buffer[size] = {0};

    unsigned char      pattern_data[] = {0x0A, 0x0B, 0x0C, 0x0D};
    eya_memory_range_t pattern        = {pattern_data, pattern_data + 4};

    eya_memory_range_t range  = {buffer, buffer + size};
    void              *result = eya_memory_range_set_pattern(&range, &pattern);

    EXPECT_EQ(result, buffer + size);
    for (size_t i = 0; i < size; ++i)
    {
        EXPECT_EQ(buffer[i], pattern_data[i]);
    }
}

TEST(eya_memory_range_set_pattern, pattern_size_smaller_than_target)
{
    constexpr size_t size         = 8;
    unsigned char    buffer[size] = {0};

    unsigned char      pattern_data[] = {0x01, 0x02};
    eya_memory_range_t pattern        = {pattern_data, pattern_data + 2};

    eya_memory_range_t range  = {buffer, buffer + size};
    void              *result = eya_memory_range_set_pattern(&range, &pattern);

    EXPECT_EQ(result, buffer + size);
    for (size_t i = 0; i < size; ++i)
    {
        EXPECT_EQ(buffer[i], pattern_data[i % 2]);
    }
}

TEST(eya_memory_range_set_pattern, overlapping_pattern_repetition)
{
    constexpr size_t size         = 7;
    unsigned char    buffer[size] = {0};

    unsigned char      pattern_data[] = {0x10, 0x20, 0x30};
    eya_memory_range_t pattern        = {pattern_data, pattern_data + 3};

    eya_memory_range_t range  = {buffer, buffer + size};
    void              *result = eya_memory_range_set_pattern(&range, &pattern);

    EXPECT_EQ(result, buffer + size);
    EXPECT_EQ(buffer[0], 0x10);
    EXPECT_EQ(buffer[1], 0x20);
    EXPECT_EQ(buffer[2], 0x30);
    EXPECT_EQ(buffer[3], 0x10);
    EXPECT_EQ(buffer[4], 0x20);
    EXPECT_EQ(buffer[5], 0x30);
    EXPECT_EQ(buffer[6], 0x10);
}