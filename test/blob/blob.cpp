//
// Created by lengyel on 2022. 03. 10..
//


#include <memory/allocator/AlignedAllocator.hpp>
#include <gtest/gtest.h>
#include "memory/blob/Blob.hpp"

TEST(Blob, construct) {
    eva::Blob obj(10);

    EXPECT_EQ(10, obj.size());
}