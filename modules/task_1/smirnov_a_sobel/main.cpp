// Copyright 2022 Smirnov Aleksandr

#include <gtest/gtest.h>
#include <vector>

#include "./sobel.h"


TEST(Sequential, Sobel_one_element) {
    matrix expected(createMatrixWithConstant(1, 1, 1));

    matrix actual = SobelSeq(expected);

    ASSERT_EQ(expected, expected);
}

TEST(Sequential, Sobel_zero_matrix) {
    matrix expected(createMatrixWithConstant(3, 3, 0));

    matrix actual = SobelSeq(expected);

    ASSERT_EQ(expected, actual);
}

TEST(Sequential, Sobel_matrix_5_5_const) {
    matrix expected = { {1, 1, 1, 1, 1},
                        {1, 0, 0, 0, 1},
                        {1, 0, 0, 0, 1},
                        {1, 0, 0, 0, 1},
                        {1, 1, 1, 1, 1} };

    matrix actual = SobelSeq(createMatrixWithConstant(5, 5, 1));

    ASSERT_EQ(expected, actual);
}

TEST(Sequential, Sobel__matrix_5_5) {
    matrix expected = { {100, 100, 100, 100, 100},
                        {100, 140, 198, 140, 100},
                        {100, 198,   0, 198, 100},
                        {100, 140, 198, 140, 100},
                        {100, 100, 100, 100, 100} };

    matrix mat = createMatrixWithConstant(5, 5, 100.0);
    mat[2][2] = 1;
    matrix actual = SobelSeq(mat);

    ASSERT_EQ(expected, actual);
}

TEST(Sequential, Sobel_random_5_5) {
    std::cout << "Expected matrix:" << std::endl;
    matrix expected(randomMatrix(5, 5));
    printMatrix(expected);

    std::cout << "Actual matrix:" << std::endl;
    matrix actual(SobelSeq(expected));
    printMatrix(actual);

    ASSERT_TRUE(true);
}
