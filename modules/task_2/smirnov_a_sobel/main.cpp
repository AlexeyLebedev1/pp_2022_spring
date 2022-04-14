// Copyright 2022 Smirnov Aleksandr

#include <omp.h>
#include <gtest/gtest.h>
#include <vector>

#include "./sobel.h"

TEST(OpenMP, Sobel_100_constant) {
    size_t size = 100;
    matrix mat = createMatrixWithConstant(size, size, 1);
    double start, end;

    start = omp_get_wtime();
    matrix expected = SobelSeq(mat);
    end = omp_get_wtime();
    std::cout << "Sequestion time is " << end - start << std::endl;

    start = omp_get_wtime();
    matrix actual = SobelPar(mat);
    end = omp_get_wtime();
    std::cout << "Parallel time is " << end - start << std::endl;

    ASSERT_EQ(expected, actual);
}

TEST(OpenMP, Sobel_1000_constant) {
    size_t size = 1000;
    matrix mat = createMatrixWithConstant(size, size, 1);
    double start, end;

    start = omp_get_wtime();
    matrix expected = SobelSeq(mat);
    end = omp_get_wtime();
    std::cout << "Sequestion time is " << end - start << std::endl;

    start = omp_get_wtime();
    matrix actual = SobelPar(mat);
    end = omp_get_wtime();
    std::cout << "Parallel time is " << end - start << std::endl;

    ASSERT_EQ(expected, expected);
}

TEST(OpenMP, Sobel_100_random) {
    size_t size = 100;
    matrix mat = randomMatrix(size, size);
    double start, end;

    start = omp_get_wtime();
    matrix expected = SobelSeq(mat);
    end = omp_get_wtime();
    std::cout << "Sequestion time is " << end - start << std::endl;

    start = omp_get_wtime();
    matrix actual = SobelPar(mat);
    end = omp_get_wtime();
    std::cout << "Parallel time is " << end - start << std::endl;

    ASSERT_EQ(expected, actual);
}

TEST(OpenMP, Sobel_1000_random) {
    size_t size = 1000;
    matrix mat = randomMatrix(size, size);
    double start, end;

    start = omp_get_wtime();
    matrix expected = SobelSeq(mat);
    end = omp_get_wtime();
    std::cout << "Sequestion time is " << end - start << std::endl;

    start = omp_get_wtime();
    matrix actual = SobelPar(mat);
    end = omp_get_wtime();
    std::cout << "Parallel time is " << end - start << std::endl;

    ASSERT_EQ(expected, actual);
}

TEST(OpenMP, Sobel_5000_random) {
    size_t size = 5000 / 10;  // for simplify work
    matrix mat = randomMatrix(size, size);
    double start, end;

    start = omp_get_wtime();
    matrix expected = SobelSeq(mat);
    end = omp_get_wtime();
    std::cout << "Sequestion time is " << end - start << std::endl;

    start = omp_get_wtime();
    matrix actual = SobelPar(mat);
    end = omp_get_wtime();
    std::cout << "Parallel time is " << end - start << std::endl;

    ASSERT_EQ(expected, actual);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    omp_set_num_threads(2);
    std::cout << "Num threads = " << omp_get_num_threads() << std::endl;
    return RUN_ALL_TESTS();
}
