// Copyright 2022 Chornyi Yura
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./shell_sort.h"

using std::vector;

TEST(Sequential, Shell_Sort_100) {
    vector<int> vec = getRandomVector(100);

    getShellSort(&vec);
    bool isSorted = std::is_sorted(vec.begin(), vec.end());

    ASSERT_EQ(isSorted, true);
}

TEST(Sequential, Shell_Sort_150) {
  vector<int> vec = getRandomVector(150);

  getShellSort(&vec);
  bool isSorted = std::is_sorted(vec.begin(), vec.end());

  ASSERT_EQ(isSorted, true);
}

TEST(Sequential, Shell_Sort_200) {
  vector<int> vec = getRandomVector(200);

  getShellSort(&vec);
  bool isSorted = std::is_sorted(vec.begin(), vec.end());

  ASSERT_EQ(isSorted, true);
}

TEST(Sequential, Shell_Sort_250) {
  vector<int> vec = getRandomVector(250);

  getShellSort(&vec);
  bool isSorted = std::is_sorted(vec.begin(), vec.end());

  ASSERT_EQ(isSorted, true);
}

TEST(Sequential, Shell_Sort_300) {
  vector<int> vec = getRandomVector(300);

  getShellSort(&vec);
  bool isSorted = std::is_sorted(vec.begin(), vec.end());

  ASSERT_EQ(isSorted, true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
