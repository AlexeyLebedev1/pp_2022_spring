// Copyright 2022 KUDRIAVTSEV ALEKSANDR
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./montecarlo.h"


double test_func1(const std::vector<double>& x) {
    return 1;
}

double test_func2(const std::vector<double>& x) {
    return x[0];
}

double test_func3(const std::vector<double>& x) {
    return x[0] + x[1];
}

double test_func4(const std::vector<double>& x) {
    double res = 0;
    res += cos(x[0] * x[1]) + sin(x[0] + x[1]) * 5 + x[0] - sqrt(abs(x[1]));
    return res;
}

TEST(MonteCarlo_test, test_different_sized_borders) {
    std::vector<double> left;
    std::vector<double> right;

    ASSERT_ANY_THROW(MonteCarloTbb(test_func3, left, right, 1000));
}

TEST(MonteCarlo_test, test_empty_borders) {
    std::vector<double> left;
    std::vector<double> right;

    ASSERT_ANY_THROW(MonteCarloTbb(test_func3, left, right, 1000));
}


TEST(MonteCarlo_test, test_1) {
    std::vector<double> left = { 0.0 };
    std::vector<double> right = { 5.0 };
    const uint64_t steps = 10000;
    double res_tbb = 0.0;
    ASSERT_NO_THROW(res_tbb = MonteCarloTbb(test_func1, left, right, steps));
    double res_seq = 0.0;
    ASSERT_NO_THROW(res_seq = MonteCarloSeq(test_func1, left, right, steps));

    std::cout << res_tbb << " " << res_seq << "\n";
}

TEST(MonteCarlo_test, test_2) {
    std::vector<double> left = { 0.0 };
    std::vector<double> right = { 2.0 };
    const uint64_t steps = 1000;

    double res_tbb = 0.0;
    ASSERT_NO_THROW(res_tbb = MonteCarloTbb(test_func2, left, right, steps));
    double res_seq = 0.0;
    ASSERT_NO_THROW(res_seq = MonteCarloSeq(test_func2, left, right, steps));

    std::cout << res_tbb << " " << res_seq << "\n";
}

TEST(MonteCarlo_test, test_3) {
    std::vector<double> left = { 0.0, 0.0 };
    std::vector<double> right = { 2.0, 2.0 };
    const uint64_t steps = 10000;

    double res_tbb = 0.0;
    ASSERT_NO_THROW(res_tbb = MonteCarloTbb(test_func3, left, right, steps));
    double res_seq = 0.0;
    ASSERT_NO_THROW(res_seq = MonteCarloSeq(test_func3, left, right, steps));

    std::cout << res_tbb << " " << res_seq << "\n";
}


/*TEST(MonteCarlo_test, test_4) {
    std::vector<double> left = { 0.0, 0.0 };
    std::vector<double> right = { 2.0, 2.0 };
    const uint64_t steps = 100000000;

    double t1 = omp_get_wtime();
    MonteCarloTbb(test_func4, left, right, steps);
    double t2 = omp_get_wtime();
    MonteCarloSeq(test_func4, left, right, steps);
    double t3 = omp_get_wtime();
    std::cout << "TBB TIME: " << t2 - t1 << "\nSequential TIME: " << t3 - t2
        << "\nSpeedUp: " << (t3 - t2) / (t2 - t1) << "\n";
}*/
