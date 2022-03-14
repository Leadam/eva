//
// Created by lengyel on 2022. 03. 14..
//
#include <image/Image.hpp>
#include <gtest/gtest.h>

#define PIXEL_FORMAT_TEST(FMT) \
TEST(PixelFormats, FMT##_format) {\
    const eva::Image<eva::FMT> image(640, 480);\
    EXPECT_EQ(640, image.width());\
    EXPECT_EQ(480, image.height());\
}

PIXEL_FORMAT_TEST(RGB24);
PIXEL_FORMAT_TEST(RGBA);
PIXEL_FORMAT_TEST(RGBX);
PIXEL_FORMAT_TEST(GRAY8);
PIXEL_FORMAT_TEST(GRAY16);


