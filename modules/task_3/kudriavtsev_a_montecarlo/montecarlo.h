// Copyright 2022 KUDRIAVTSEV ALEKSANDR
#ifndef MODULES_TASK_3_KUDRIAVTSEV_A_MONTECARLO_MONTECARLO_H_
#define MODULES_TASK_3_KUDRIAVTSEV_A_MONTECARLO_MONTECARLO_H_

#include <omp.h>

#include <tbb/tbb.h>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>

#include <random>
#include <vector>

double MonteCarloSeq(double(*func)(const std::vector<double>&),
    const std::vector<double>& left, const std::vector<double>& right,
    uint64_t steps, int seed = 0);

double MonteCarloTbb(double(*func)(const std::vector<double>&),
    const std::vector<double>& left, const std::vector<double>& right,
    uint64_t steps, int seed = 0);
#endif  // MODULES_TASK_3_KUDRIAVTSEV_A_MONTECARLO_MONTECARLO_H_
