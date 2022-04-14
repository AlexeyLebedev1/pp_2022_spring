// Copyright 2022 Mishin Ilya
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "./shell.hpp"


TEST(ShellTest, test_1) {
    std::vector<int> vec1, vec2;
    int N = 10000;
    vec1 = getRandomVector(N);
    vec2 = vec1;
    auto start = clock();
    ShellSortOMP(vec1.begin(), vec1.end(), std::less<int>());
    std::cout << "OMP time: " << static_cast<float>(clock() -
    start) / CLOCKS_PER_SEC << std::endl;

    start = clock();
    ShellSortSeq(vec2.begin(), vec2.end(), std::less<int>());
    std::cout << "Sequential time: " << static_cast<float>(clock() -
    start) / CLOCKS_PER_SEC << std::endl;

    ASSERT_EQ(vec1, vec2);
}

TEST(ShellTest, test_2) {
    std::vector<int> vec1, vec2;
    int N = 10000;
    vec1 = getRandomVector(N);
    vec2 = vec1;
    auto start = clock();
    ShellSortOMP(vec1.begin(), vec1.end(), std::less<int>());
    std::cout << "OMP time: " << static_cast<float>(clock() -
    start) / CLOCKS_PER_SEC << std::endl;

    start = clock();
    ShellSortSeq(vec2.begin(), vec2.end(), std::less<int>());
    std::cout << "Sequential time: " << static_cast<float>(clock() -
    start) / CLOCKS_PER_SEC << std::endl;

    ASSERT_EQ(vec1, vec2);
}

TEST(ShellTest, test_3) {
    std::vector<int> vec1, vec2;
    int N = 10000;
    vec1 = getRandomVector(N);
    vec2 = vec1;
    auto start = clock();
    ShellSortOMP(vec1.begin(), vec1.end(), std::greater<int>());
    std::cout << "OMP time: " << static_cast<float>(clock() -
    start) / CLOCKS_PER_SEC << std::endl;

    start = clock();
    ShellSortSeq(vec2.begin(), vec2.end(), std::greater<int>());
    std::cout << "Sequential time: " << static_cast<float>(clock() -
    start) / CLOCKS_PER_SEC << std::endl;

    ASSERT_EQ(vec1, vec2);
}

TEST(ShellTest, test_4) {
    std::vector<int> vec1, vec2;
    int N = 10000;
    vec1 = getRandomVector(N);
    vec2 = vec1;
    auto start = clock();
    ShellSortOMP(vec1.begin(), vec1.end(), [](int a, int b) {
        return a < b;
    });
    std::cout << "OMP time: " << static_cast<float>(clock() -
    start) / CLOCKS_PER_SEC << std::endl;

    start = clock();
    ShellSortSeq(vec2.begin(), vec2.end(), [](int a, int b) {
        return a < b;
    });
    std::cout << "Sequential time: " << static_cast<float>(clock() -
    start) / CLOCKS_PER_SEC << std::endl;

    ASSERT_EQ(vec1, vec2);
}

TEST(ShellTest, test_5) {
    std::vector<int> vec1, vec2;
    int N = 50000;
    vec1 = getRandomVector(N);
    vec2 = vec1;
    auto start = clock();
    ShellSortOMP(vec1.begin(), vec1.end(), [](int a, int b) {
        return a > b;
    });
    std::cout << "OMP time: " << static_cast<float>(clock() -
    start) / CLOCKS_PER_SEC << std::endl;

    start = clock();
    ShellSortSeq(vec2.begin(), vec2.end(), [](int a, int b) {
        return a > b;
    });
    std::cout << "Sequential time: " << static_cast<float>(clock() -
    start) / CLOCKS_PER_SEC << std::endl;

    ASSERT_EQ(vec1, vec2);
}
