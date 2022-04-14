// Copyright 2022 Smirnov Aleksandr
#ifndef MODULES_TASK_3_SMIRNOV_A_SOBEL_SOBEL_H_
#define MODULES_TASK_3_SMIRNOV_A_SOBEL_SOBEL_H_

#include <vector>
#include <string>

using matrix = std::vector<std::vector<int>>;

static const int MAX_PIXEL = 255;
static const int MIN_PIXEL = 0;

static const matrix sobel_x = {{-1, -2, -1}, { 0,  0,  0}, { 1,  2,  1}};
static const matrix sobel_y = {{-1,  0,  1}, {-2,  0,  2}, {-1,  0,  1}};

matrix SobelSeq(const matrix& src);
matrix SobelPar(const matrix& src);
matrix randomMatrix(size_t w, size_t h);
matrix createMatrixWithConstant(size_t w, size_t h, int val);
void printMatrix(const matrix& m);

#endif  // MODULES_TASK_3_SMIRNOV_A_SOBEL_SOBEL_H_
