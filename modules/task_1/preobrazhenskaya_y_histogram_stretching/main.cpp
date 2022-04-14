// Copyright 2022 Preobrazhenskaya Yuliya
#include <gtest/gtest.h>
#include "./histogram_stretching.h"

TEST(Sequential_Histogram_Stretching, Image_is_empty) {
    int height = 0;
    int width = 0;
    ASSERT_ANY_THROW(getRandomImage(height, width));
}

TEST(Sequential_Histogram_Stretching, Image_5x5) {
    int height = 5;
    int width = 5;
    int* image = getRandomImage(height, width);
    int y_max = getYmax(image, height, width);
    int y_min = getYmin(image, height, width);
    int* result_image = nullptr;
    ASSERT_NO_THROW(result_image = getSequentialOperations(image, height, width,
        y_max, y_min));
    delete[] image;
    delete[] result_image;
}

TEST(Sequential_Histogram_Stretching, Image_7x10) {
    int height = 7;
    int width = 10;
    int* image = getRandomImage(height, width);
    int y_max = getYmax(image, height, width);
    int y_min = getYmin(image, height, width);
    int* result_image = nullptr;
    ASSERT_NO_THROW(result_image = getSequentialOperations(image, height, width,
        y_max, y_min));
    delete[] image;
    delete[] result_image;
}

TEST(Sequential_Histogram_Stretching, Image_10x15) {
    int height = 10;
    int width = 15;
    int* image = getRandomImage(height, width);
    int y_max = getYmax(image, height, width);
    int y_min = getYmin(image, height, width);
    int* result_image = nullptr;
    ASSERT_NO_THROW(result_image = getSequentialOperations(image, height, width,
        y_max, y_min));
    delete[] image;
    delete[] result_image;
}

TEST(Sequential_Histogram_Stretching, Image_40x20) {
    int height = 40;
    int width = 20;
    int* image = getRandomImage(height, width);
    int y_max = getYmax(image, height, width);
    int y_min = getYmin(image, height, width);
    int* result_image = nullptr;
    ASSERT_NO_THROW(result_image = getSequentialOperations(image, height, width,
        y_max, y_min));
    delete[] image;
    delete[] result_image;
}

TEST(Sequential_Histogram_Stretching, Image_50x50) {
    int height = 50;
    int width = 50;
    int* image = getRandomImage(height, width);
    int y_max = getYmax(image, height, width);
    int y_min = getYmin(image, height, width);
    int* result_image = nullptr;
    ASSERT_NO_THROW(result_image = getSequentialOperations(image, height, width,
        y_max, y_min));
    delete[] image;
    delete[] result_image;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
