#include <vector>
#include "movement.hpp"
#include <opencv4/opencv2/opencv.hpp>

class BoundingBox{

    std::vector<Vector> getBoundingBox(const cv::Mat& image);
};
