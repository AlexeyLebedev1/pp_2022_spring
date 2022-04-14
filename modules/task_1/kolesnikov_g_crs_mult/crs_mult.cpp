// Copyright 2022 Kolesnikov Gleb
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include "../../../modules/task_1/kolesnikov_g_crs_mult/crs_mult.h"


MatrixCRS::MatrixCRS(int nC, int nR, const std::vector<double>& v,
    const std::vector<int>& c, const std::vector<int>& p): nColumns(nC),
    nRows(nR), values(v), columns(c), pointers(p) {}

MatrixCRS::MatrixCRS(std::vector<std::vector<double>> mtx) {
    nColumns = mtx[0].size();
    nRows = mtx.size();

    int elemCounter = 0;
    pointers.push_back(elemCounter);
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            if (mtx[i][j] != 0) {
                elemCounter = elemCounter + 1;
                values.push_back(mtx[i][j]);

                columns.push_back(j);
            }
        }
        pointers.push_back(elemCounter);
    }
}

MatrixCRS::MatrixCRS(int nC, int nR) {
    nColumns = nC;
    nRows = nR;
}

MatrixCRS MatrixCRS::T() {
    std::vector<std::vector<int>> intVectors(nColumns);
    std::vector<std::vector<double>> valueVectors(nColumns);
    MatrixCRS mtxT;

    mtxT.nRows = nColumns;
    mtxT.nColumns = nRows;
    int elemCounter = 0;
    for (int i = 0; i < nRows; i++) {
        for (int k = pointers[i]; k < pointers[i + 1]; k++) {
            int colInd = columns[k];
            intVectors[colInd].push_back(i);
            valueVectors[colInd].push_back(values[k]);
        }
    }
    mtxT.pointers.push_back(elemCounter);
    for (int i = 0; i < nColumns; i++) {
        for (size_t k = 0; k < intVectors[i].size(); k++) {
            mtxT.columns.push_back(intVectors[i][k]);
            mtxT.values.push_back(valueVectors[i][k]);
        }
        elemCounter = elemCounter + intVectors[i].size();
        mtxT.pointers.push_back(elemCounter);
    }
    return mtxT;
}

MatrixCRS MatrixCRS::dot(MatrixCRS mtx) {
    std::vector<int> resCol;
    std::vector<double> resValue;
    std::vector<int> resPointer;
    int nZRow = 0;
    int resRows = nRows;
    int resCols = mtx.nColumns;
    if (nColumns != mtx.nColumns) {
        throw std::runtime_error("Error! Incorrect numbers of rows!\n");
    }
    nZRow = 0;
    resRows = nRows;
    resCols = mtx.nColumns;
    resPointer.push_back(nZRow);
    for (int i = 0; i < nRows; i++) {
        // i - number of the processed row of the left matrix
        nZRow = 0;
        for (int j = 0; j < mtx.nRows; j++) {
            // j - number of the processed column of the right matrix
            double summ = 0;
            int ls = mtx.pointers[j];
            int lf = mtx.pointers[j + 1] - 1;
            int ks = pointers[i];
            int kf = pointers[i + 1] - 1;
            while ((lf >= ls) && (kf >= ks)) {
                if (columns[ks] > mtx.columns[ls]) {
                    ls = ls + 1;
                } else {
                    if (columns[ks] < mtx.columns[ls]) {
                        ks = ks + 1;
                    } else {
                        summ = summ + values[ks] * mtx.values[ls];
                        ls = ls + 1;
                        ks = ks + 1;
                    }
                }
            }


            if (summ != 0) {
                nZRow = nZRow + 1;
                resValue.push_back(summ);
                resCol.push_back(j);
            }
        }
        resPointer.push_back(nZRow + resPointer[i]);
    }

    MatrixCRS res(resCols, resRows, resValue, resCol, resPointer);
    return res;
}

void MatrixCRS::printArrays() {
    std::cout << "values:\n";
    for (size_t i = 0; i < values.size(); i++) {
        std::cout << values[i] << " ";
    }
    std::cout << "\ncolumns:\n";
    for (size_t i = 0; i < columns.size(); i++) {
        std::cout << columns[i] << " ";
    }
    std::cout << "\npointer:\n";
    for (size_t i = 0; i < pointers.size(); i++) {
        std::cout << pointers[i] << " ";
    }
    std::cout << "\n";
}
std::vector<std::vector<double>> zerpMatrix(int cols, int rows) {
    std::vector<std::vector<double>> res(rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res[i].push_back(0);
        }
    }
    return res;
}
bool MatrixCRS::operator==(const MatrixCRS& mtx) const {
    bool check = false;
    if ((nColumns == mtx.nColumns) && (nRows == mtx.nRows)
        && (values == mtx.values)
        && (columns == mtx.columns)
        && (pointers == mtx.pointers))
        check = true;
    return check;
}

std::vector<std::vector<double>> generateMatrix(int cols, int rows,
    double density) {
    if (density > 1 || density < 0) {
        throw std::runtime_error("Error! Incorrect percentage!\n");
    }
    std::vector<std::vector<double>> res = zerpMatrix(cols, rows);
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_real_distribution<double> prob{ 0.0, 1.0 };
    std::uniform_real_distribution<double> value{ 0.0, 13.0 };
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (prob(gen) <= density) {
                res[i][j] = value(gen);
            }
        }
    }
    return res;
}
std::vector<std::vector<double>> multMatrix(std::vector<std::vector<double>> A,
    std::vector<std::vector<double>> B) {
    int rows = A.size();
    int cols = B[0].size();
    std::vector<std::vector<double>> C = zerpMatrix(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            C[i][j] = 0;
            for (size_t k = 0; k < A[0].size(); k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}
