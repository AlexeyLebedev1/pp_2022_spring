// Copyright 2022 Kurnikova Anastasia
#include <gtest/gtest.h>
#include <omp.h>
#include "./sparse_ccs_mult.h"

TEST(sparse_ccs_mult, test1) {
    ASSERT_NO_THROW(mymat a(2, 2, 2));
}

TEST(sparse_ccs_mult, test2) {
    mymat a(1, 1, 0);
    mymat b(1, 1, 0);
    EXPECT_EQ(a, b);
}

TEST(sparse_ccs_mult, test3) {
    mymat a(5, 1, 2);
    ASSERT_NO_THROW(t(&a));
}

TEST(sparse_ccs_mult, test4) {
    mymat a(1, 1, 0);
    mymat b(5, 4, 1);
    bool q = true;
    if (a == b)
        q = true;
    else
        q = false;
    EXPECT_EQ(false, q);
}

TEST(sparse_ccs_mult, test5) {
    ASSERT_NO_THROW(randmat(100, 100));
}

TEST(sparse_ccs_mult, test6) {
    mymat a(2, 2, 0);
    mymat b(2, 2, 1);
    mymat ab(2, 2, 0);
    EXPECT_EQ(ab, result(&a, &b));
}

TEST(sparse_ccs_mult, test7_100_4) {
    double start, stop;
    mymat a = randmat(100, 100);
    mymat b = randmat(100, 100);
    omp_set_num_threads(4);
    start = omp_get_wtime();
    result(&a, &b);
    stop = omp_get_wtime();
    double omp = stop - start;
    start = omp_get_wtime();
    seqresult(&a, &b);
    stop = omp_get_wtime();
    double seq = stop - start;
    std::cout << "\n         OpenMP: " << omp << "\n";
    std::cout << "         Sequen: " << seq << "\n" << std::endl;
    ASSERT_NO_THROW();
}

TEST(sparse_ccs_mult, test8_1000_4) {
    double start, stop;
    mymat a = randmat(1000, 1000);
    mymat b = randmat(1000, 1000);
    omp_set_num_threads(4);
    start = omp_get_wtime();
    result(&a, &b);
    stop = omp_get_wtime();
    double omp = stop - start;
    start = omp_get_wtime();
    seqresult(&a, &b);
    stop = omp_get_wtime();
    double seq = stop - start;
    std::cout << "\n         OpenMP: " << omp << "\n";
    std::cout << "         Sequen: " << seq << "\n" << std::endl;
    ASSERT_NO_THROW();
}

TEST(sparse_ccs_mult, test9_5000_4) {
    double start, stop;
    mymat a = randmat(5000, 5000);
    mymat b = randmat(5000, 5000);
    omp_set_num_threads(4);
    start = omp_get_wtime();
    result(&a, &b);
    stop = omp_get_wtime();
    double omp = stop - start;
    start = omp_get_wtime();
    seqresult(&a, &b);
    stop = omp_get_wtime();
    double seq = stop - start;
    std::cout << "\n         OpenMP: " << omp << "\n";
    std::cout << "         Sequen: " << seq << "\n" << std::endl;
    ASSERT_NO_THROW();
}

TEST(sparse_ccs_mult, test10_5000_2) {
    double start, stop;
    mymat a = randmat(5000, 5000);
    mymat b = randmat(5000, 5000);
    omp_set_num_threads(2);
    start = omp_get_wtime();
    result(&a, &b);
    stop = omp_get_wtime();
    double omp = stop - start;
    start = omp_get_wtime();
    seqresult(&a, &b);
    stop = omp_get_wtime();
    double seq = stop - start;
    std::cout << "\n         OpenMP: " << omp << "\n";
    std::cout << "         Sequen: " << seq << "\n" << std::endl;
    ASSERT_NO_THROW();
}

TEST(sparse_ccs_mult, test11_5000_8) {
    double start, stop;
    mymat a = randmat(5000, 5000);
    mymat b = randmat(5000, 5000);
    omp_set_num_threads(8);
    start = omp_get_wtime();
    result(&a, &b);
    stop = omp_get_wtime();
    double omp = stop - start;
    start = omp_get_wtime();
    seqresult(&a, &b);
    stop = omp_get_wtime();
    double seq = stop - start;
    std::cout << "\n         OpenMP: " << omp << "\n";
    std::cout << "         Sequen: " << seq << "\n" << std::endl;
    ASSERT_NO_THROW();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
