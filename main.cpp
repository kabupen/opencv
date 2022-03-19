#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
std::cout << __FILE__ << " " << __LINE__ << std::endl;
    cv::Mat img = cv::imread("figure.jpg");
std::cout << __FILE__ << " " << __LINE__ << std::endl;

    cv::imshow("test", img);
std::cout << __FILE__ << " " << __LINE__ << std::endl;
    cv::waitKey(0);
std::cout << __FILE__ << " " << __LINE__ << std::endl;
    return 0;
std::cout << __FILE__ << " " << __LINE__ << std::endl;
}
