// Copyright 2022 KUDRIAVTSEV ALEKSANDR

#include <iostream>
#include "../../../modules/task_3/kudriavtsev_a_montecarlo/montecarlo.h"

double MonteCarloSeq(double(*func)(const std::vector<double>&),
    const std::vector<double>& left, const std::vector<double>& right,
    uint64_t steps, int seed) {
    // CHECK DIMENSIONS
    if (left.size() != right.size())
        throw "Different sizes of left and right borders";
    if (left.empty())
        throw "Empty borders";

    double res = 0.0;
    size_t dimension = left.size();

    // Random
    std::mt19937 gen;
    gen.seed(seed);
    std::vector<std::uniform_real_distribution<double>> realdistr(dimension);
    for (size_t i = 0; i < dimension; i++)
        realdistr[i] = std::uniform_real_distribution<double>(left[i],
                                                              right[i]);

    // Main cycle
    std::vector<double> pnt(dimension);
    for (uint64_t i = 0; i < steps; ++i) {
        for (size_t k = 0; k < dimension; ++k) {
            pnt[k] = realdistr[k](gen);
        }
        res += func(pnt);
    }

    // Area
    double S = 1;
    for (size_t k = 0; k < dimension; ++k) {
        S *= right[k] - left[k];
    }
    res = S * res / steps;
    return res;
}

double MonteCarloTbb(double(*func)(const std::vector<double>&),
    const std::vector<double>& left, const std::vector<double>& right,
    uint64_t steps, int seed) {
    if (left.size() != right.size())
        throw "Different sizes of left and right borders";
    if (left.empty())
        throw "Empty borders";

    double res = 0.0;
    size_t dimension = left.size();

    // Random
    std::mt19937 gen;
    gen.seed(seed);
    std::vector<std::uniform_real_distribution<double>> realdistr(dimension);
    for (size_t i = 0; i < dimension; i++)
        realdistr[i] = std::uniform_real_distribution<double>(left[i],
            right[i]);

    // Main cycle
    tbb::enumerable_thread_specific<double> sum;
    tbb::parallel_for(tbb::blocked_range<uint64_t> (0, steps),
        [&](tbb::blocked_range<uint64_t> r) {
            std::vector<double> pnt(dimension);
            for (auto i = r.begin(); i != r.end(); ++i) {
                for (size_t k = 0; k < dimension; ++k) {
                    pnt[k] = realdistr[k](gen);
                }
                sum.local() += func(pnt);
            }
    });
    res = sum.combine(std::plus<double>()) / steps;

    // Area
    double S = 1;
    for (size_t k = 0; k < dimension; ++k) {
        S *= right[k] - left[k];
    }
    res = S * res;
    return res;
}
