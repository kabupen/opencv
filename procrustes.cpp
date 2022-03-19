
void rotation(){
    cv::Mat rot = cv::getRotationMatrix2D(cv::Point2f(0,0), 60, 1);

    std::cout << rot << std::endl;
    std::cout << rot.dims << " " << rot.cols << " " << rot.rows << std::endl;

    return rot;
}


void procrustes(){

    std::vector<cv::Point2f> p_src = {};
    std::vector<cv::Point2f> p_dst = {};
}
