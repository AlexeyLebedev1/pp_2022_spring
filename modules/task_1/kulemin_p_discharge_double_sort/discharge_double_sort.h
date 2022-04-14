// Copyright 2022 George Amberson
#ifndef MODULES_TASK_1_KULEMIN_P_DISCHARGE_DOUBLE_SORT_DISCHARGE_DOUBLE_SORT_H_
#define MODULES_TASK_1_KULEMIN_P_DISCHARGE_DOUBLE_SORT_DISCHARGE_DOUBLE_SORT_H_
#include <vector>
#include <list>
double* create_random_vector(int size_n);
void union_from_lists(const std::vector<std::list<double>>* lists, double* in);
void discharge_sort(double* in, int size);
bool check_vectors(double* st, double* sd, int size);
void copy_vectors(double* st, double* sd, int size);
#endif  // MODULES_TASK_1_KULEMIN_P_DISCHARGE_DOUBLE_SORT_DISCHARGE_DOUBLE_SORT_H_
