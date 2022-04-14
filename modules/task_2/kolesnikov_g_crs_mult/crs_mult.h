// Copyright 2022 Kolesnikov Gleb
#ifndef MODULES_TASK_2_KOLESNIKOV_G_CRS_MULT_CRS_MULT_H_
#define MODULES_TASK_2_KOLESNIKOV_G_CRS_MULT_CRS_MULT_H_

#include <vector>
#include <string>

class MatrixCRS {
 public:
    int nColumns;
    int nRows;

    std::vector<double> values;
    std::vector<int> columns;
    std::vector<int> pointers;

    MatrixCRS(int nC, int nR, const std::vector<double>& v,
        const std::vector<int>& c, const std::vector<int>& p);
    explicit MatrixCRS(std::vector<std::vector<double>> mtx);
    explicit MatrixCRS(int nC = 0, int nR = 0);
    MatrixCRS T();
    MatrixCRS dot(MatrixCRS mtx);
    MatrixCRS dot_omp(MatrixCRS mtx);
    bool operator==(const MatrixCRS& mtx) const;
    void printArrays();
};

std::vector<std::vector<double>> multMatrix(std::vector<std::vector<double>> A,
    std::vector<std::vector<double>> B);

std::vector<std::vector<double>> zerpMatrix(int cols, int rows);

std::vector<std::vector<double>> generateMatrix(int cols, int rows,
    double density);
#endif  // MODULES_TASK_2_KOLESNIKOV_G_CRS_MULT_CRS_MULT_H_
