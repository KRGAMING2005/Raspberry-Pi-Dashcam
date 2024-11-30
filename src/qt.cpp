#include <iostream>
#include <string>
#include <opencv4/opencv2/opencv.hpp>
#include <qt6/QtWidgets/QtWidgets>

int main(int argc, char** argv) {
    // cv::Mat img = cv::imread("test.jpg");

    // cv::imshow("test", img);
    
    // cv::setWindowProperty("test", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

    // cv::waitKey(0);

    QApplication app{argc, argv};
    QWindow widget{};
    widget.show();

    return app.exec();
}