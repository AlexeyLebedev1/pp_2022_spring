// Copyright 2022 Mishin Ilya
#ifndef MODULES_TASK_2_MISHIN_I_SHELL_EASY_SHELL_HPP_
#define MODULES_TASK_2_MISHIN_I_SHELL_EASY_SHELL_HPP_
#include <omp.h>
#include <random>
#include <vector>
#include <utility>
#include <algorithm>

template< typename RandomAccessIterator, typename Comparator>
void ShellSortSeq(RandomAccessIterator first,
               RandomAccessIterator last, Comparator comp) {
    for (auto d = (last - first) / 2; d != 0; d /= 2)
        for (auto i = first + d; i != last; ++i)
            for (auto j = i; j - first >= d && comp(*j, *(j - d)); j -= d)
                std::swap(*j, *(j - d));
}

template< typename RandomAccessIterator, typename Comparator>
void ShellSortOMP(RandomAccessIterator first,
               RandomAccessIterator last, Comparator comp) {
    std::size_t input_size = last - first;
    size_t N;
    #pragma omp parallel
    {
        N = omp_get_num_threads();
    }
    std::vector<std::size_t> block_sizes(N);
    for (std::size_t i = 0; i < N; ++i) {
        std::size_t size = input_size / N;
        std::size_t additional_element = 0;
        if (i < input_size % N) {
            additional_element = 1;
        }
        block_sizes[i] = size + additional_element;
    }
    auto get_block_borders =
        [&block_sizes](std::size_t block, std::size_t n) {
            std::size_t start = 0;
            for (std::size_t i = 0; i < block; ++i) {
                start += block_sizes[i];
            }
            return std::make_pair(start, start + block_sizes[block]);
        };
    std::size_t blocks;
    #pragma omp parallel
    {
        blocks = omp_get_num_threads();
        std::size_t block = omp_get_thread_num();
        auto borders = get_block_borders(block, blocks);
        ShellSortSeq(first + borders.first, first + borders.second, comp);
    }

    for (std::size_t merge_step = 1; merge_step < blocks; merge_step *= 2) {
        int stop = static_cast<int>(blocks - merge_step);
        #pragma omp parallel for
        for (int i = 0; i < stop; i+= merge_step * 2) {
            auto borders1 = get_block_borders(i, blocks);
            auto borders2 = get_block_borders(i + merge_step , blocks);
            assert(borders1.second == borders2.first);
            std::size_t start = borders1.first;
            std::size_t mid = borders1.second;
            std::size_t finish = borders2.second;
            finish = std::min(finish, input_size);
            std::inplace_merge(first+start, first+mid, first+finish, comp);
        }

        for (int i = 0; i < stop; i+= merge_step * 2) {
            block_sizes[i] = block_sizes[i] + block_sizes[i+merge_step];
            block_sizes[i+merge_step] = 0;
        }
    }
}

std::vector<int> getRandomVector(int size);
#endif  // MODULES_TASK_2_MISHIN_I_SHELL_EASY_SHELL_HPP_
