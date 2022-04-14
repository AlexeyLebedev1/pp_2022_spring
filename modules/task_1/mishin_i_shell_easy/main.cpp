// Copyright 2022 Mishin Ilya
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "./shell.hpp"


TEST(ShellTest, test_1) {
    std::vector<int> vec1, vec2;
    int N = 1;
    vec1 = getRandomVector(N);
    vec2 = vec1;

    ShellSort(vec1.begin(), vec1.end(), std::less<int>());
    std::sort(vec2.begin(), vec2.end());

    ASSERT_EQ(vec1, vec2);
}

TEST(ShellTest, test_2) {
    std::vector<int> vec1, vec2;
    int N = 1000;
    vec1 = getRandomVector(N);
    vec2 = vec1;

    ShellSort(vec1.begin(), vec1.end(), std::less<int>());
    std::sort(vec2.begin(), vec2.end());

    ASSERT_EQ(vec1, vec2);
}

TEST(ShellTest, test_3) {
    std::vector<int> vec1, vec2;
    int N = 1000;
    vec1 = getRandomVector(N);
    vec2 = vec1;

    ShellSort(vec1.begin(), vec1.end(), std::greater<int>());
    std::sort(vec2.begin(), vec2.end(), std::greater<int>());

    ASSERT_EQ(vec1, vec2);
}

TEST(ShellTest, test_4) {
    std::vector<int> vec1, vec2;
    int N = 1000;
    vec1 = getRandomVector(N);
    vec2 = vec1;

    ShellSort(vec1.begin(), vec1.end(), [](int a, int b) {
        return a < b;
    });
    std::sort(vec2.begin(), vec2.end(), [](int a, int b) {
        return a < b;
    });

    ASSERT_EQ(vec1, vec2);
}

TEST(ShellTest, test_5) {
    std::vector<int> vec1, vec2;
    int N = 50000;
    vec1 = getRandomVector(N);
    vec2 = vec1;

    ShellSort(vec1.begin(), vec1.end(), std::less<int>());
    std::sort(vec2.begin(), vec2.end());

    ASSERT_EQ(vec1, vec2);
}
