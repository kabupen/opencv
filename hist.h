
#include <opencv2/opencv.hpp>

namespace mycv {

    cv::Mat Hist(cv::Mat img){

        int hist_size = 256;
        float range[] = {0, 256}; // 上限はexclusive

        // ポインタ配列
        // 各ビンの次元において、ビンの領域を指定する
        // std::cout << hist_range; ## hist_rangeへのアドレスが表示される
        // std::cout << hist_range[0]; ## 一番目の要素（ここではrangeだけ）のポインタが表示される
        // std::cout << hist_range[0][1]; ## 要素の実際の値にアクセスできる（ここでは256）
        const float* hist_range[] = {range}; 

        cv::Mat hist;
        cv::calcHist(&img, 1, 0, cv::Mat(), hist, 1, &hist_size, hist_range, true, false);

        return hist;
    }

    void Print(cv::Mat hist, bool all = false){
        if ( all ) {
            std::cout << hist << std::endl;
        }
        // cv::Mat の型がenum で返ってくる
        std::cout << hist.type() << std::endl; 

        // 次元、行数、列数 
        std::cout << hist.dims << " " << hist.rows << " " << hist.cols << std::endl;
    }

}
