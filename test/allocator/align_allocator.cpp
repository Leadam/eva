//
// Created by lengyel on 2022. 03. 10..
//

#include <memory/allocator/AlignedAllocator.hpp>
#include <gtest/gtest.h>

TEST(AlignAllocator, construct) {
    eva::AlignedAllocator<int, std::align_val_t(64)> allocator;
}

TEST(AlignAllocator, allocate) {
    eva::AlignedAllocator<int, std::align_val_t(64)> allocator;
    int *ptr = allocator.allocate(10);
    EXPECT_NE(nullptr, ptr);
    allocator.deallocate(ptr, 10);
}

TEST(AlignAllocator, null_allocate) {
    eva::AlignedAllocator<int, std::align_val_t(64)> allocator;
    int *ptr = allocator.allocate(0);
    EXPECT_EQ(nullptr, ptr);
}

TEST(AlignAllocator, max_allocate) {
    eva::AlignedAllocator<int, std::align_val_t(64)> allocator;
    EXPECT_THROW(
            int *ptr = allocator.allocate(std::numeric_limits<uint64_t>::max()),
            std::length_error
    );
}