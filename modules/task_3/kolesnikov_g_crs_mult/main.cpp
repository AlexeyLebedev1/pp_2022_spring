// Copyright 2022 Kolesnikov Gleb
#include <gtest/gtest.h>
//  #include <tbb/task_arena.h>
#include "tbb/tbb.h"
#include "./crs_mult.h"





TEST(MatrixCRS_tbb, create_zero_matrix) {
    EXPECT_NO_THROW(zerpMatrix(13, 13));
}

TEST(MatrixCRS_tbb, create_random_matrix) {
    EXPECT_NO_THROW(generateMatrix(13, 13, 0.5));
}

TEST(MatrixCRS_tbb, create_random_matrix_density_not_correct_1) {
    EXPECT_ANY_THROW(generateMatrix(13, 13, 2));
}

TEST(MatrixCRS_tbb, create_random_matrix_density_not_correct_2) {
    EXPECT_ANY_THROW(generateMatrix(13, 13, -1));
}

TEST(MatrixCRS_tbb, matrix_mult_1) {
    std::vector<std::vector<double>> v1 = { {0, 3}, {0, 7} };
    std::vector<std::vector<double>> v2 = { {1, 0}, {0, 1} };
    EXPECT_EQ(multMatrix(v1, v2), v1);
}

TEST(MatrixCRS_tbb, matrix_mult_2) {
    std::vector<std::vector<double>> v1 = { {0, 3}, {0, 7} };
    std::vector<std::vector<double>> v2 = { {1, 1}, {0, 1} };
    std::vector<std::vector<double>> v3 = { {0, 3}, {0, 7} };
    EXPECT_EQ(multMatrix(v1, v2), v3);
}

TEST(MatrixCRS_tbb, create_crs_matrix) {
    std::vector<std::vector<double>> v1 = { {0, 3}, {0, 7} };
    EXPECT_NO_THROW(MatrixCRS crs(v1));
}

TEST(MatrixCRS_tbb, transpose_crs) {
    std::vector<double> v1 = { 0, 10, 0, 10, 0 };
    std::vector<double> v2 = { 0, 0, 21, 0, 1 };
    std::vector<double> v3 = { 0, 0, 0, 0, 0 };
    std::vector<double> v4 = { 3, 0, 0, 0, 25 };
    std::vector<double> v1T = { 0, 0, 0, 3 };
    std::vector<double> v2T = { 10, 0, 0, 0 };
    std::vector<double> v3T = { 0, 21, 0, 0 };
    std::vector<double> v4T = { 10, 0, 0, 0 };
    std::vector<double> v5T = { 0, 1, 0, 25 };
    std::vector<std::vector<double>> v = { v1, v2, v3, v4 };
    std::vector<std::vector<double>> vT = { v1T, v2T, v3T, v4T, v5T };
    EXPECT_EQ(MatrixCRS(v), MatrixCRS(vT).T());
}

TEST(MatrixCRS_tbb, mult_crs) {
    std::vector<std::vector<double>> v1 = generateMatrix(3, 3, 0.5);
    std::vector<std::vector<double>> v2 = generateMatrix(3, 3, 0.5);
    MatrixCRS crs1(v1);
    MatrixCRS crs2(v2);
    //  crs1.dot(crs2.T()).printArrays();
    //  MatrixCRS(multMatrix(v1, v2)).printArrays();
    EXPECT_EQ(crs1.dot(crs2.T()), MatrixCRS(multMatrix(v1, v2)));
}

TEST(MatrixCRS_tbb, mult_crs_tbb) {
    std::vector<std::vector<double>> v1 = generateMatrix(3, 3, 0.5);
    std::vector<std::vector<double>> v2 = generateMatrix(3, 3, 0.5);
    MatrixCRS crs1(v1);
    MatrixCRS crs2(v2);
  //  crs1.dot(crs2.T()).printArrays();
  //  MatrixCRS(multMatrix(v1, v2)).printArrays();
  //  crs1.dot_tbb(crs2.T()).printArrays();
    EXPECT_EQ(crs1.dot_tbb(crs2.T()), MatrixCRS(multMatrix(v1, v2)));
    /*
    v1 = generateMatrix(2313, 813, 0.05);
    v2 = generateMatrix(813, 2313, 0.05);

    tbb::tick_count start = tbb::tick_count::now();
    tbb::task_arena arena(1);
    arena.execute([&] {crs1 = MatrixCRS(v1).dot_tbb(MatrixCRS(v2).T()); });
    std::cout << "Time 1 thread:  " << (tbb::tick_count::now() - start).seconds() << "\n";
  //  std::cout << "Is equal: " << (crs2 == crs1) << "\n";
  //  crs1.printArrays();
    
    start = tbb::tick_count::now();
    arena = tbb::task_arena(2);
    arena.execute([&] {crs2 = MatrixCRS(v1).dot_tbb(MatrixCRS(v2).T()); });
    std::cout << "Time 2 threads: " <<  (tbb::tick_count::now() - start).seconds()<< "\n";
   // std::cout << "Is equal: " << (crs2 == crs1) << "\n";
   // crs2.printArrays();



    start = tbb::tick_count::now();
    arena = tbb::task_arena(3);
    arena.execute([&] {crs2 = MatrixCRS(v1).dot_tbb(MatrixCRS(v2).T()); });
    std::cout << "Time 3 threads: " <<  (tbb::tick_count::now() - start).seconds() << "\n";
  //  std::cout << "Is equal: " << (crs2 == crs1) << "\n";
  //  crs2.printArrays();


    start = tbb::tick_count::now();
    arena = tbb::task_arena(4);
    arena.execute([&] {crs2 = MatrixCRS(v1).dot_tbb(MatrixCRS(v2).T()); });
    std::cout << "Time 4 threads: " << (tbb::tick_count::now() - start).seconds() << "\n";
  //  std::cout << "Is equal: " << (crs2 == crs1) << "\n";
  //  crs2.printArrays();
  */
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
