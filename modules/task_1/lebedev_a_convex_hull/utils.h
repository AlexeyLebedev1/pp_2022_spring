// Copyright 2022 Lebedev Alexey
#ifndef MODULES_TASK_1_LEBEDEV_A_CONVEX_HULL_CONVEX_UTILS_H_
#define MODULES_TASK_1_LEBEDEV_A_CONVEX_HULL_CONVEX_UTILS_H_


#include <vector>
#include <memory>
#include <stdexcept>


#define CV_8UC1 0

namespace lab1 {
    namespace image_utils {
        struct Point2d {
            double x, y;
            Point2d() = default;
            Point2d(double _x, double _y) : x(_x), y(_y) {}
            bool operator == (const Point2d& p) const {
                return x == p.x && y == p.y;
            }
        };

        struct Size2d {
            size_t width, height;
            Size2d() = default;
            Size2d(size_t _width, size_t _height) : width(_width), height(_height) {}
        };

        struct Scalar {
            uint8_t value;
            Scalar() = default;
            Scalar(uint8_t _value) : value(_value) {}
        };

        class Mat {
         private:
             std::shared_ptr<std::vector<uint8_t>> _data;
             Size2d _size;
         public:
             Mat() {}
             Mat(const Size2d& size, int type, const Scalar& s) : _size(size) {
                 _data = std::make_shared<std::vector<uint8_t>>(size.height * size.width, s.value);
             }

             Mat& operator=(const Mat& other) {
                 if (this == &other) {
                     return *this;
                 }
                 this->_data = other._data;
                 this->_size = other._size;
                 return *this;
             }

             template<typename T>
             uint8_t& at(const Point2d& p) {
                 if (p.y >= _size.height || p.x >= _size.width) {
                     throw std::out_of_range("Incorrect coorinates!");
                 }
                 return _data->at(_size.width * p.y + p.x);
             }

             template<typename T>
             const uint8_t& at(const Point2d& p) const {
                 if (p.y >= _size.height || p.x >= _size.width) {
                     throw std::out_of_range("Incorrect coorinates!");
                 }
                 return _data->at(_size.width * p.y + p.x);
             }

             Size2d size() const {
                 return _size;
             }

             Mat clone() const {
                 Mat cloned(_size, 0, 0);
                 std::copy(_data->begin(), _data->end(), cloned._data->begin());
                 return cloned;
             }
        };

        inline void findNonZero(const Mat& mat, std::vector<Point2d>& output) {
            output.clear();
            for (size_t i = 0; i < mat.size().width; i++) {
                for (size_t j = 0; j < mat.size().height; j++) {
                    Point2d p(i, j);
                    if (mat.at<uint8_t>(p)) {
                        output.push_back(p);
                    }
                }
            }
        }

        inline void circle(const Mat& mat, const Point2d& p, size_t rad, const Scalar& color, int thickness = 1) {
            // not imlemented
        }

        inline void line(const Mat& mat, const Point2d& begin, const Point2d& end, const Scalar& color) {
            // not imlemented
        }

        inline void hconcat(const std::vector<Mat>& src, Mat& output) {
            // not imlemented
        }

        inline void imwrite(std::string file_name, const Mat& mat) {
            // not imlemented
        }

    }  // namespace image_utils
};  // namespace lab1


#endif  // MODULES_TASK_1_LEBEDEV_A_CONVEX_HULL_CONVEX_UTILS_H_