// Copyright 2022 George Amberson
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <list>
#include "../../../modules/task_1/kulemin_p_discharge_double_sort/discharge_double_sort.h"

double* create_random_vector(int size_n) {
    double* v = new double[size_n];
    std::random_device dev;
    std::mt19937 gen(dev());
    for (int i = 0; i < size_n; ++i) {
        v[i] = static_cast<double>(gen())/gen();
    }
    return v;
}
void union_from_lists(std::vector<std::list<double>> *lists, double* in) {
    int j = 0;
    for (size_t i = 0; i < (*lists).size(); i++) {
        while (!(*lists)[i].empty()) {
            in[j]=((*lists)[i].front());
            (*lists)[i].pop_front();
            j++;
        }
    }
}
void discharge_sort(double* in, int size) {
    std::vector<std::list<double >> lists(256);
    for (size_t j = 0; j < sizeof(double); j++) {
        for (int i = 0; i < size; i++) {
            unsigned char* pt = (unsigned char*)(in + i);
            lists[*(pt + j)].push_back(in[i]);
        }
        union_from_lists(&lists, in);
    }
}
bool check_vectors(double* st, double* sd, int size) {
    bool res = true;
    for (int i = 0; i < size; i++) {
        if (st[i] != sd[i]) {
            res = false;
            break;
        }
    }
    return res;
}
void copy_vectors(double* st, double* sd, int size) {
    for (int i = 0; i < size; i++) {
        sd[i] = st[i];
    }
}


