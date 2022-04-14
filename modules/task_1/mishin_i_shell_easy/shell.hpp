// Copyright 2022 Mishin Ilya
#ifndef MODULES_TASK_1_MISHIN_I_SHELL_EASY_SHELL_HPP_
#define MODULES_TASK_1_MISHIN_I_SHELL_EASY_SHELL_HPP_
#include <random>
#include <vector>
#include <utility>

template< typename RandomAccessIterator, typename Comparator>
void ShellSort(RandomAccessIterator first,
               RandomAccessIterator last, Comparator comp) {
    for (auto d = (last - first) / 2; d != 0; d /= 2)
        for (auto i = first + d; i != last; ++i)
            for (auto j = i; j - first >= d && comp(*j, *(j - d)); j -= d)
                std::swap(*j, *(j - d));
}

std::vector<int> getRandomVector(int size);
#endif  // MODULES_TASK_1_MISHIN_I_SHELL_EASY_SHELL_HPP_
