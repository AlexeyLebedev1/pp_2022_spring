// Copyright 2022 Bakalina Darya
#ifndef MODULES_TASK_1_BAKALINA_D_SHELL_MERGE_SORT_SHELL_MERGE_SORT_H_
#define MODULES_TASK_1_BAKALINA_D_SHELL_MERGE_SORT_SHELL_MERGE_SORT_H_
#include <vector>

std::vector<int> create_random_vector(int size_n);
std::vector<int> merge_two_vector(std::vector<int> vctr_1, std::vector<int> vctr_2);
std::vector <int> shell_sort(const std::vector <int>& v);
std::vector <int> shell_sort_with_merge(std::vector<int> vctr);

#endif  // MODULES_TASK_1_BAKALINA_D_SHELL_MERGE_SORT_SHELL_MERGE_SORT_H_
