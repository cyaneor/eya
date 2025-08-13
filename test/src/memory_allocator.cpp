#include <eya/memory_allocator.h>
#include <gtest/gtest.h>

TEST(eya_memory_allocator_get_alloc_fn, returns_correct_pointer)
{
    eya_memory_allocator_t         allocator = {malloc, free};
    eya_memory_allocator_alloc_fn *result    = eya_memory_allocator_get_alloc_fn(&allocator);
    EXPECT_EQ(result, malloc);
}

TEST(eya_memory_allocator_get_alloc_fn, handles_gracefully)
{
    // Assuming eya_runtime_check_ref handles NULL by asserting or crashing
    EXPECT_DEATH(eya_memory_allocator_get_alloc_fn(nullptr), ".*");
}

TEST(eya_memory_allocator_get_dealloc_fn, returns_correct_pointer)
{
    eya_memory_allocator_t           allocator = {malloc, free};
    eya_memory_allocator_dealloc_fn *result    = eya_memory_allocator_get_dealloc_fn(&allocator);
    EXPECT_EQ(result, free);
}

TEST(eya_memory_allocator_get_dealloc_fn, handles_null_pointer_gracefully)
{
    EXPECT_DEATH(eya_memory_allocator_get_dealloc_fn(nullptr), ".*");
}

TEST(eya_memory_allocator_alloc, returns_valid_pointer_for_valid_size)
{
    eya_memory_allocator_t allocator = {malloc, free};
    eya_usize_t            size      = 16;
    void                  *ptr       = eya_memory_allocator_alloc(&allocator, size);
    EXPECT_NE(ptr, nullptr) << "Allocation should return a non-null pointer";
    eya_memory_allocator_free(&allocator, ptr);
}

TEST(eya_memory_allocator_alloc, handles_zero_size)
{
    eya_memory_allocator_t allocator = {malloc, free};
    EXPECT_DEATH(eya_memory_allocator_alloc(&allocator, 0), ".*")
        << "Should fail on zero size allocation";
}

TEST(eya_memory_allocator_alloc, handles_null_allocator)
{
    EXPECT_DEATH(eya_memory_allocator_alloc(nullptr, 16), ".*")
        << "Should fail when allocator is NULL";
}

TEST(eya_memory_allocator_alloc, handles_uninitialized_alloc_fn)
{
    eya_memory_allocator_t allocator = {nullptr, free};
    EXPECT_DEATH(eya_memory_allocator_alloc(&allocator, 16), ".*")
        << "Should fail when alloc_fn is not initialized";
}

TEST(eya_memory_allocator_free, handles_valid_pointer)
{
    eya_memory_allocator_t allocator = {malloc, free};
    eya_usize_t            size      = 16;

    void *ptr = eya_memory_allocator_alloc(&allocator, size);
    ASSERT_NE(ptr, nullptr) << "Allocation failed";

    // No crash expected on valid free
    EXPECT_NO_FATAL_FAILURE(eya_memory_allocator_free(&allocator, ptr))
        << "Freeing valid pointer should not throw";
}

TEST(eya_memory_allocator_free, handles_null_pointer)
{
    eya_memory_allocator_t allocator = {malloc, free};
    // eya_runtime_return_ifn should cause early return for NULL pointer
    EXPECT_NO_FATAL_FAILURE(eya_memory_allocator_free(&allocator, nullptr))
        << "Freeing NULL pointer should not throw";
}

TEST(eya_memory_allocator_free, handles_null_allocator)
{
    eya_memory_allocator_t allocator = {malloc, free};
    eya_usize_t            size      = 16;
    void                  *ptr       = eya_memory_allocator_alloc(&allocator, size);
    ASSERT_NE(ptr, nullptr) << "Allocation failed";

    EXPECT_DEATH(eya_memory_allocator_free(nullptr, ptr), ".*")
        << "Should fail when allocator is NULL";

    // Clean up to avoid memory leak
    eya_memory_allocator_free(&allocator, ptr);
}

TEST(eya_memory_allocator_free, handles_uninitialized_dealloc_fn)
{
    eya_memory_allocator_t allocator = {malloc, free};
    eya_usize_t            size      = 16;

    void *ptr = eya_memory_allocator_alloc(&allocator, size);
    ASSERT_NE(ptr, nullptr) << "Allocation failed";

    eya_memory_allocator_t invalid_allocator = {malloc, nullptr};
    EXPECT_DEATH(eya_memory_allocator_free(&invalid_allocator, ptr), ".*")
        << "Should fail when dealloc_fn is not initialized";

    // Clean up to avoid memory leak
    eya_memory_allocator_free(&allocator, ptr);
}

TEST(eya_memory_allocator_realloc, returns_same_pointer_for_same_size)
{
    eya_memory_allocator_t allocator = {malloc, free};
    eya_usize_t            size      = 16;
    void                  *ptr       = eya_memory_allocator_alloc(&allocator, size);
    ASSERT_NE(ptr, nullptr) << "Allocation failed";

    void *new_ptr = eya_memory_allocator_realloc(&allocator, ptr, size, size);
    EXPECT_EQ(new_ptr, ptr) << "Should return same pointer when old_size equals new_size";

    eya_memory_allocator_free(&allocator, ptr);
}

TEST(eya_memory_allocator_realloc, handles_null_old_pointer)
{
    eya_memory_allocator_t allocator = {malloc, free};
    eya_usize_t            new_size  = 16;
    void                  *new_ptr = eya_memory_allocator_realloc(&allocator, nullptr, 0, new_size);

    EXPECT_NE(new_ptr, nullptr) << "Should allocate new memory for NULL old_ptr";
    eya_memory_allocator_free(&allocator, new_ptr);
}

TEST(eya_memory_allocator_realloc, handles_zero_new_size)
{
    eya_memory_allocator_t allocator = {malloc, free};
    eya_usize_t            old_size  = 16;

    void *ptr = eya_memory_allocator_alloc(&allocator, old_size);
    ASSERT_NE(ptr, nullptr) << "Allocation failed";

    void *new_ptr = eya_memory_allocator_realloc(&allocator, ptr, old_size, 0);
    EXPECT_EQ(new_ptr, nullptr) << "Should return nullptr for zero new_size";
    // Memory is freed internally by realloc when new_size is 0
}

TEST(eya_memory_allocator_realloc, handles_null_allocator)
{
    eya_memory_allocator_t allocator = {malloc, free};
    eya_usize_t            old_size  = 16;

    void *ptr = eya_memory_allocator_alloc(&allocator, old_size);
    ASSERT_NE(ptr, nullptr) << "Allocation failed";

    EXPECT_DEATH(eya_memory_allocator_realloc(nullptr, ptr, old_size, 32), ".*")
        << "Should fail when allocator is NULL";

    eya_memory_allocator_free(&allocator, ptr);
}

TEST(eya_memory_allocator_realloc, copies_data_correctly)
{
    eya_memory_allocator_t allocator = {malloc, free};

    eya_usize_t old_size = 8;
    eya_usize_t new_size = 16;

    void *ptr = eya_memory_allocator_alloc(&allocator, old_size);
    ASSERT_NE(ptr, nullptr) << "Allocation failed";

    // Initialize old memory with known data
    char *old_data = static_cast<char *>(ptr);
    for (eya_usize_t i = 0; i < old_size; ++i)
    {
        old_data[i] = static_cast<char>(i + 1);
    }

    void *new_ptr = eya_memory_allocator_realloc(&allocator, ptr, old_size, new_size);
    ASSERT_NE(new_ptr, nullptr) << "Reallocation failed";

    // Check if data was copied correctly
    char *new_data = static_cast<char *>(new_ptr);
    for (eya_usize_t i = 0; i < old_size; ++i)
    {
        EXPECT_EQ(new_data[i], static_cast<char>(i + 1))
            << "Data at index " << i << " was not copied correctly";
    }

    eya_memory_allocator_free(&allocator, new_ptr);
}