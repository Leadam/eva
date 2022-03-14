//
// Created by lengyel on 2022. 03. 13..
//
#include <image/Image.hpp>
#include <gtest/gtest.h>

TEST(Image, construct) {
    const eva::Image<eva::RGB24> image(640, 480);

    EXPECT_EQ(640, image.width());
    EXPECT_EQ(480, image.height());
}