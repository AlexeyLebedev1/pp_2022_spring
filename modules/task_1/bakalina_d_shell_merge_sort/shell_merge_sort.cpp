// Copyright 2022 Bakalina Darya
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include "../../../modules/task_1/bakalina_d_shell_merge_sort/shell_merge_sort.h"

std::vector<int> create_random_vector(int size_n) {
    if (size_n <= 0) {
        throw "Wrong size";
    }
    std::vector <int> v(size_n);
    std::random_device dev;
    std::mt19937 gen(dev());
    for (int i = 0; i < size_n; ++i) {
        v[i] = gen() % 100;
    }
    return v;
}

std::vector<int> merge_two_vector(std::vector<int> vctr_1, std::vector<int> vctr_2) {
    int i = 0;
    int j = 0;
    int k = 0;
    int size_1 = vctr_1.size();
    int size_2 = vctr_2.size();
    std::vector<int> result(size_1 + size_2);
    while (size_1 && size_2) {
        if (vctr_1[i] < vctr_2[j]) {
            result[k] = vctr_1[i];
            i++;
            size_1--;
        } else {
            result[k] = vctr_2[j];
            j++;
            size_2--;
        }
        k++;
    }
    if (size_1 == 0) {
        for (int l = j; l < j + size_2; l++) {
            result[k] = vctr_2[l];
            k++;
        }
    } else if (size_2 == 0) {
        for (int m = i; m < i + size_1; m++) {
            result[k] = vctr_1[m];
            k++;
        }
    }
    return result;
}

std::vector <int> shell_sort(const std::vector <int>& v) {
    int iter = 0;
    int i = 0;
    int j = 0;
    int tmp = 0;
    int size_n = v.size();
    std::vector <int> res(v);
    for (iter = size_n / 2; iter > 0; iter /= 2) {
        for (i = iter; i < size_n; i++) {
            for (j = i - iter; j >= 0 && res[j] > res[j + iter]; j -= iter) {
                tmp = res[j];
                res[j] = res[j + iter];
                res[j + iter] = tmp;
            }
        }
    }
    return res;
}

std::vector <int> shell_sort_with_merge(std::vector<int> vctr) {
    std::vector<int> res = vctr;
    int size = vctr.size();
    if (size < 1) {
        throw "Wrong size";
    }
    if (size == 1) {
        return vctr;
    }
    std::vector<int> vctr_l;
    std::vector<int> vctr_r;
    if (size % 2 == 0) {
        vctr_l.resize(size / 2);
        vctr_r.resize(size / 2);
    } else {
        vctr_l.resize(size / 2);
        vctr_r.resize(size / 2 + 1);
    }
    std::copy(res.begin(), res.begin() + size / 2, vctr_l.begin());
    std::copy(res.begin() + size / 2, res.end(), vctr_r.begin());
    vctr_l = shell_sort(vctr_l);
    vctr_r = shell_sort(vctr_r);
    res = merge_two_vector(vctr_l, vctr_r);
    return res;
}
