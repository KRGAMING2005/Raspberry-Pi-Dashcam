#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

int main() {
    cv::Mat img = cv::imread("test.jpg");
    cv::imshow("test", img);
    cv::setWindowProperty("test", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
    cv::waitKey(0);
    return 0;
}