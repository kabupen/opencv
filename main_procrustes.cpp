#include <iostream>
#include <opencv2/opencv.hpp>

#include "hist.h"
#include "procrustes.cpp"

int main() {
   
    // 3 channel で背景の定義
    // C3を指定しないとデフォルトではグレースケールで初期化される
    int WIDTH = 500;
    int HEIGHT = 500;
    cv::Mat img(cv::Size(WIDTH, HEIGHT), CV_32FC3, cv::Scalar(255,255,255));

    cv::line(img, cv::Point2f(0, HEIGHT/2), cv::Point2f(WIDTH, HEIGHT/2), cv::Scalar(0,0,0));
    cv::line(img, cv::Point2f(WIDTH/2, 0), cv::Point2f(WIDTH/2, HEIGHT), cv::Scalar(0,0,0));

   

    // 変換元
    std::cout << "\nPoint2fの元の情報： " << std::endl;
    std::vector<cv::Point2d> p_src = {
        cv::Point2d(50, 50),
        cv::Point2d(200, 50),
        cv::Point2d(125, 200)
    };
    for(auto& e: p_src)
        std::cout << e << std::endl;

    cv::Mat dummy(1,3, CV_64F,cv::Scalar(1));

    // 回転行列
    cv::Mat rot = cv::getRotationMatrix2D(cv::Point2f(0,0), 60, 1);
    std::cout << "\n回転行列： " << std::endl;
    std::cout << rot << std::endl;
    std::cout << rot.dims << " " << rot.rows << " " << rot.cols  << std::endl;


    std::cout << "\n対象とする点群： " << std::endl;
    cv::Mat mat_src(p_src.size(), 2, CV_64F, p_src.data());
    mat_src = mat_src.t();
    mat_src.push_back(dummy);

    std::cout << mat_src << std::endl;

    // 回転操作を加える
    std::cout << "\n回転させる： " << std::endl;
    std::cout << rot.size() << " " << mat_src.size() << std::endl;
    std::cout << rot.type() << " " << mat_src.type() << std::endl;
    cv::Mat mat_src_rot = rot * mat_src;
    std::cout << mat_src_rot << std::endl;


    // cv::warpAffine(mat_src, mat_src_rot, rot, )
    

    std::vector<cv::Point2f> points = {
        cv::Point2f(1,1), 
        cv::Point2f(3,1), 
        cv::Point2f(2,-1)
    };
    cv::Mat X(points.size(), 2, CV_32F, points.data());
    std::vector<cv::Point2f> pointsY = {
        cv::Point2f(1.89820457, 2.62936427), 
        cv::Point2f(2.28639948, 3.59230849), 
        cv::Point2f(2.90660411, 2.50094847)
    };
    cv::Mat Y(points.size(), 2, CV_32F, points.data());
    procrustes(X, Y);


    //
    //    std::vector<cv::Point2f> p_dst;
    //    for(auto&e : p_src){
//        p_dst.push_back(rot.mul(e));
//    };
   
    // 描画
    for(auto& p : p_src){
        cv::circle(img, p, 1, cv::Scalar(255,0,255), 2);
    }

//    for(auto& p : p_dst){
//        cv::circle(img, p, 1, cv::Scalar(0,255,255), 2);
//    }

    cv::imshow("test", img);
    cv::waitKey(0);

    
    return 0;
}
