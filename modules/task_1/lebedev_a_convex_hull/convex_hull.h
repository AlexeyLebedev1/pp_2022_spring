// Copyright 2022 Lebedev Alexey
#ifndef MODULES_TASK_1_LEBEDEV_A_CONVEX_HULL_CONVEX_HULL_H_
#define MODULES_TASK_1_LEBEDEV_A_CONVEX_HULL_CONVEX_HULL_H_

#include "opencv2/opencv.hpp"
#include <vector>

namespace lab1 {
	void convex_hull(const cv::Mat& c1_image, std::vector<cv::Point2d>& output);
};  // namespace lab1


#endif  // MODULES_TASK_1_LEBEDEV_A_CONVEX_HULL_CONVEX_HULL_H_
