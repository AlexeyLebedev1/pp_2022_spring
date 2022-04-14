// Copyright 2022 Chornyi Yura
#include <vector>
#include <random>
#include "../../../modules/task_1/chornyi_y_shell_sort_with_bather/shell_sort.h"

using std::vector;
typedef vector<int>::size_type vec_size_t;

vector<int> getRandomVector(const vec_size_t size) {
    std::random_device dev;
    std::mt19937 gen(dev());
    vector<int> resultVector(size);

    for (vec_size_t i = 0; i < size; ++i) {
        resultVector[i] = gen() % 10000;
    }

    return resultVector;
}

vector<int> sedgwickOrder(const vec_size_t sizeOfVector) {
  vector<int> result;
  int firstCommonMultiple = 1, secondEvenMultiple = 1, secondOddMultiple = 1;
  int counter = 0;

  do {
    if (counter++ % 2 == 0) {
      result.push_back(9 * firstCommonMultiple - 9 * secondEvenMultiple + 1);
      secondEvenMultiple *= 2;
    } else {
      secondOddMultiple *= 2;
      result.push_back(8 * firstCommonMultiple - 6 * secondOddMultiple + 1);
    }
    firstCommonMultiple *= 2;
  } while (static_cast<vec_size_t>(3 * result[result.size() - 1]) <
           sizeOfVector);

  return result;
}

void getShellSort(vector<int>* commonVector) {
  vector<int> vectorOfGap = sedgwickOrder(commonVector->size());

  for (int counter = vectorOfGap.size() - 1; counter >= 0; --counter) {
    size_t currentGap = vectorOfGap[counter];

    for (vec_size_t i = currentGap; i < commonVector->size(); ++i) {
      for (int j = i - currentGap;
           (j >= 0) && (commonVector->at(j) > commonVector->at(j + currentGap));
           j -= currentGap) {
        std::swap(commonVector->at(j), commonVector->at(j + currentGap));
      }
    }
  }
}
