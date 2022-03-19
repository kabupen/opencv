#include <iostream>
#include <opencv2/opencv.hpp>

int main(){

    float range[] = {0, 256};
    const float* hist_range[] = {range};

    std::cout << range << std::endl;
    std::cout << range[0] << std::endl;
    std::cout << range[1] << std::endl;
    std::cout << hist_range << std::endl;
    std::cout << hist_range[0][0] << std::endl;
    std::cout << hist_range[0][1] << std::endl;

}
