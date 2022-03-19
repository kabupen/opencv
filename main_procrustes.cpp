#include <iostream>
#include <opencv2/opencv.hpp>

#include "hist.h"

int main() {
   
    int width = 500;
    int height = 500;
    
    cv::Mat img(cv::Size(width, height), CV_32F, cv::Scalar(255));

    cv::line(img, cv::Point2f(0, height/2), cv::Point2f(width, height/2), cv::Scalar(0,0,0));
    cv::line(img, cv::Point2f(width/2, 0), cv::Point2f(width/2, height), cv::Scalar(0,0,0));

    
    // 変換元
    std::vector<cv::Point2f> p_src = {
        cv::Point2f(50, 50),
        cv::Point2f(200, 50),
        cv::Point2f(125, 100)
    };

    // 変換先
    // 回転
    cv::Mat rot = cv::getRotationMatrix2D(cv::Point2f(0,0), 60, 1);
    std::cout << rot << std::endl;
    std::cout << rot.dims << " " << rot.rows << " " << rot.cols  << std::endl;

    //
//    std::vector<cv::Point2f> p_dst;
//    for(auto&e : p_src){
//        p_dst.push_back(rot.mul(e));
//    };
   
    // 描画
    for(auto& p : p_src){
        cv::circle(img, p, 1, cv::Scalar(0,255,255), 2);
    }
//    for(auto& p : p_dst){
//        cv::circle(img, p, 1, cv::Scalar(0,255,255), 2);
//    }

    cv::imshow("test", img);
    cv::waitKey(0);

    
    return 0;
}
