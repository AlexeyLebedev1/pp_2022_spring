// Copyright 2022 Mishin Ilya

#include <iostream>
#include "../../../modules/task_2/mishin_i_shell_easy/shell.hpp"


std::vector<int> getRandomVector(int size) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<int> vec(size);
    for (int i = 0; i < size; i++) { vec[i] = gen() % 100; }
    return vec;
}
