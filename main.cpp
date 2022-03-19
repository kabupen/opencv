#include <iostream>
#include <opencv2/opencv.hpp>

#include "src/hist.h"

int main() {
    
    cv::Mat img = cv::imread("figure.jpg", cv::IMREAD_GRAYSCALE);
//    cv::imshow("test", img);
//    cv::waitKey(0);

    cv::Mat hist = mycv::Hist(img);

    mycv::Print(hist);
    
    return 0;
}
