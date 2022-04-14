// Copyright 2022 Bakalina Darya
#include <gtest/gtest.h>
#include <vector>
#include "./shell_merge_sort.h"

TEST(Sequential_algorithm, vector_with_one_size) {
    std::vector<int> v = { 21 };
    ASSERT_NO_THROW(v = shell_sort_with_merge(v));
}

TEST(Sequential_algorithm, sort_vector_with_shell_sort) {
    int size = 6;
    std::vector<int> v = { 8, 2, 15, 74, 6, 39 };
    std::vector<int> res = { 2, 6, 8, 15, 39, 74 };
    v = shell_sort(v);
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(v[i], res[i]);
    }
}

TEST(Sequential_algorithm, sort_vector_with_shell_merge_sort) {
    int size = 6;
    std::vector<int> v = { 8, 2, 15, 74, 6, 39 };
    std::vector<int> res = { 2, 6, 8, 15, 39, 74};
    v = shell_sort_with_merge(v);
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(v[i], res[i]);
    }
}

TEST(Sequential_algorithm, sort_vectors_with_size_5) {
    int size = 5;
    std::vector<int> v(size);
    std::vector<int> res(size);
    v = create_random_vector(size);
    res = v;
    v = shell_sort_with_merge(v);
    res = shell_sort(res);
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(res[i], v[i]);
    }
}

TEST(Sequential_algorithm, sort_vectors_with_size_10) {
    int size = 10;
    std::vector<int> v(size);
    std::vector<int> res(size);
    v = create_random_vector(size);
    res = v;
    v = shell_sort_with_merge(v);
    res = shell_sort(res);
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(res[i], v[i]);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
