
void rotation(){
    cv::Mat rot = cv::getRotationMatrix2D(cv::Point2f(0,0), 60, 1);

    std::cout << rot << std::endl;
    std::cout << rot.dims << " " << rot.cols << " " << rot.rows << std::endl;
}


void procrustes(cv::Mat X, cv::Mat Y){
    
    // X, Y
    // [2 x 3] 変換する3点の行列, rows = 3, cols = 2
    // 
    int n = X.rows;
    int m = X.cols;
    int ny = Y.rows;
    int my = Y.cols;
   
    // 列平均（それぞれの x, y 座標の平均値を算出）
    // [2 x 1]
    //
    cv::Mat muX_, muY_;
    cv::reduce(X, muX_, 0, cv::REDUCE_AVG, CV_32F);
    cv::reduce(Y, muY_, 0, cv::REDUCE_AVG, CV_32F);
    
    // [2 x 3] 
    cv::Mat muX, muY;
    for(int idx=0; idx<3; idx++){
        muX.push_back(muX_);
        muY.push_back(muY_);
    }
    std::cout << "mux = " << muX << std::endl;

    cv::Mat X0, Y0;
    X0 = X - muX;
    Y0 = X - muY;

    std::cout << "X0 = " << X0 << std::endl;

    // 要素毎の積
    cv::Mat X0_2 = X0.mul(X0); 
    cv::Mat Y0_2 = Y0.mul(Y0); 

    double ssX = cv::sum(X0_2)[0];
    double ssY = cv::sum(Y0_2)[0];

    double normX = std::sqrt(ssX);
    double normY = std::sqrt(ssY);

    std::cout << "normX = " << normX << std::endl;

    X0 /= normX;
    Y0 /= normY;

    


}
