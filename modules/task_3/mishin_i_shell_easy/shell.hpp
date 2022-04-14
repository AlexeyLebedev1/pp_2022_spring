// Copyright 2022 Mishin Ilya
#ifndef MODULES_TASK_3_MISHIN_I_SHELL_EASY_SHELL_HPP_
#define MODULES_TASK_3_MISHIN_I_SHELL_EASY_SHELL_HPP_
#include <tbb/tbb.h>
#include <random>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

template< typename RandomAccessIterator, typename Comparator>
void ShellSortSeq(RandomAccessIterator first,
               RandomAccessIterator last, Comparator comp) {
    for (auto d = (last - first) / 2; d != 0; d /= 2)
        for (auto i = first + d; i != last; ++i)
            for (auto j = i; j - first >= d && comp(*j, *(j - d)); j -= d)
                std::swap(*j, *(j - d));
}

template< typename RandomAccessIterator, typename Comparator>
void ShellSortTBB(RandomAccessIterator first,
                  RandomAccessIterator last, Comparator comp) {
    using my_range = std::pair<std::size_t, std::size_t>;
    tbb::parallel_deterministic_reduce(
        tbb::blocked_range<int>(0, last - first, 500), my_range(),
        [&](const tbb::blocked_range<int>& r, my_range v) -> my_range {
            v = std::make_pair(r.begin(), r.end());
            ShellSortSeq(first + v.first, first + v.second, comp);
            return v;
    },
        [&](my_range v1, my_range v2) -> my_range {
            assert(v1.second == v2.first);
            std::inplace_merge(first + v1.first,
                        first + v1.second, first + v2.second, comp);
            return {v1.first, v2.second};
        });
}

std::vector<int> getRandomVector(int size);
#endif  // MODULES_TASK_3_MISHIN_I_SHELL_EASY_SHELL_HPP_
