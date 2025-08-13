#include <gtest/gtest.h>
#include <eya/addr_util.h>

TEST(address_util, addr_to_ptr_conversion) {
    int value = 42;
    int *ptr = &value;
    auto addr = reinterpret_cast<uintptr_t>(ptr);

    int *converted_ptr = eya_addr_to_ptr(int, addr);
    EXPECT_EQ(converted_ptr, ptr);
    EXPECT_EQ(*converted_ptr, 42);

    void *void_ptr = eya_addr_to_void(addr);
    EXPECT_EQ(void_ptr, ptr);
}

TEST(address_util, address_difference) {
    int arr[10];
    auto addr1 = reinterpret_cast<uintptr_t>(&arr[5]);
    auto addr2 = reinterpret_cast<uintptr_t>(&arr[2]);

    ptrdiff_t diff = eya_addr_diff(addr1, addr2);
    EXPECT_EQ(diff, 3 * sizeof(int));
}

TEST(address_util, alignment_offset) {
    uintptr_t addr = 0x1234;

    EXPECT_EQ(eya_addr_align_by_offset(addr, 4), 0);
    EXPECT_EQ(eya_addr_align_by_offset(addr + 1, 4), 1);
    EXPECT_EQ(eya_addr_align_by_offset(addr + 2, 4), 2);
    EXPECT_EQ(eya_addr_align_by_offset(addr + 3, 4), 3);
    EXPECT_EQ(eya_addr_align_by_offset(addr + 4, 4), 0);
}

TEST(address_util, alignment_check) {
    uintptr_t aligned_addr = 0x1000;
    uintptr_t unaligned_addr = 0x1001;

    EXPECT_TRUE(eya_addr_is_aligned(aligned_addr, 4));
    EXPECT_TRUE(eya_addr_is_aligned(aligned_addr, 16));
    EXPECT_FALSE(eya_addr_is_aligned(unaligned_addr, 4));
    EXPECT_FALSE(eya_addr_is_aligned(unaligned_addr, 16));
}

TEST(address_util, align_up_operation) {
    uintptr_t addr = 0x1003;

    EXPECT_EQ(eya_addr_align_up(addr, 4), 0x1004);
    EXPECT_EQ(eya_addr_align_up(addr, 8), 0x1008);
    EXPECT_EQ(eya_addr_align_up(addr, 16), 0x1010);
    EXPECT_EQ(eya_addr_align_up(0x1000, 4), 0x1000);
}

TEST(address_util, align_down_operation) {
    uintptr_t addr = 0x1003;

    EXPECT_EQ(eya_addr_align_down(addr, 4), 0x1000);
    EXPECT_EQ(eya_addr_align_down(addr, 8), 0x1000);
    EXPECT_EQ(eya_addr_align_down(addr, 16), 0x1000);
    EXPECT_EQ(eya_addr_align_down(0x1000, 4), 0x1000);
}
