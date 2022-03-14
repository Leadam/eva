//
// Created by lengyel on 2022. 03. 14..
//
#include <image/Image.hpp>
#include <gtest/gtest.h>

TEST(Cursor, type_check_RGB24){
    eva::Image<eva::RGB24> image(640, 480);

    EXPECT_EQ(0, image.getPixel(0,0)->red);
    EXPECT_EQ(0, image.getPixel(0,0)->green);
    EXPECT_EQ(0, image.getPixel(0,0)->blue);
}

TEST(Cursor, type_check_RGBA){
    eva::Image<eva::RGBA> image(640, 480);

    EXPECT_EQ(0, image.getPixel(0,0)->red);
    EXPECT_EQ(0, image.getPixel(0,0)->green);
    EXPECT_EQ(0, image.getPixel(0,0)->blue);
    EXPECT_EQ(0, image.getPixel(0,0)->alpha);
}

TEST(Cursor, type_check_RGBX){
    eva::Image<eva::RGBX> image(640, 480);

    EXPECT_EQ(0, image.getPixel(0,0)->red);
    EXPECT_EQ(0, image.getPixel(0,0)->green);
    EXPECT_EQ(0, image.getPixel(0,0)->blue);
}

TEST(Cursor, type_check_GRAY8){
    eva::Image<eva::GRAY8> image(640, 480);

    EXPECT_EQ(0u, *image.getPixel(0,0));
}

TEST(Cursor, type_check_GRAY16){
    eva::Image<eva::GRAY16> image(640, 480);

    EXPECT_EQ(0u, *image.getPixel(0,0));
}