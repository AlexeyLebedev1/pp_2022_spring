// Copyright 2022 Smirnov Aleksandr

#include <cmath>
#include <ctime>
#include <iostream>
#include <algorithm>

#include "../../../modules/task_1/smirnov_a_sobel/sobel.h"

matrix randomMatrix(size_t w, size_t h) {
    if (w <= 0 || h <= 0)
        throw std::invalid_argument("Error with size matrix");

    matrix res(w, std::vector<int>(h));

    std::mt19937 gen;
    gen.seed(static_cast<int>(time(0)));

    for (size_t i = 0; i < w; i++) {
        for (size_t j = 0; j < h; j++) {
            res[i][j] = gen() % MAX_PIXEL;
        }
    }

    return res;
}

matrix SobelSeq(const matrix& src) {
    if (src.size() <= 0 || src[0].size() <= 0)
        throw std::invalid_argument("Error with size matrix");

    matrix res = src;
    size_t width = src.size() - 1;
    size_t hight = src[0].size() - 1;

    for (size_t i = 1; i < width; i++)
        for (size_t j = 1; j < hight; j++) {
            double x = 0;
            double y = 0;
            for (size_t w = 0; w < 3; w++) {
                for (size_t h = 0; h < 3; h++) {
                    x += src[i + w - 1][j + h - 1] * sobel_x[w][h];
                    y += src[i + w - 1][j + h - 1] * sobel_y[w][h];
                }
            }
            double c = sqrt(x * x + y * y);
            res[i][j] = c > MAX_PIXEL ? MAX_PIXEL : c < MIN_PIXEL ? MIN_PIXEL : c;
        }

    return res;
}

matrix createMatrixWithConstant(size_t w, size_t h, int val) {
    if (w <= 0 || h <= 0)
        throw std::invalid_argument("Error with size matrix");

    matrix res(w, std::vector<int>(h, val));

    return res;
}

void printMatrix(const matrix& m) {
    // std::cout << "Size: " << m.size() << ":" << m[0].size()<< std::endl;
    for (size_t i = 0; i < m.size(); i++) {
        for (size_t j = 0; j < m[i].size(); j++)
            std::cout << m[i][j] << " ";
        std::cout << std::endl;
    }
}
