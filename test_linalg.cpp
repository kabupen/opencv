#include <iostream>
#include <opencv2/opencv.hpp>

int main() {

    // -----------------------------------
    //  Point の使い方
    // -----------------------------------
    std::cout << "*****************************" << std::endl;

    cv::Point2f p1(1,2);
    std::cout << p1 << std::endl;

    // 演算
    // std::cout << p1 + 10 << std::endl; /* Bad */
    std::cout << p1.x + 10 << " " << p1.y + 10 << std::endl; /* OK */
    std::cout << p1 * 10 << std::endl; /* OK */
    std::cout << p1 / 10 << std::endl; /* OK */

    // 要素へのアクセス
    // std::cout << p1[0] << std::endl; /* Bad */
    // std::cout << p1(0) << std::endl; /* Bad */
    // std::cout << p1.at<float>(0) << std::endl; /* Bad */
    std::cout << p1.x << " " << p1.y << std::endl; /* OK */


    // -----------------------------------
    //  Mat への変換
    // -----------------------------------
    std::cout << "*****************************" << std::endl;

    std::vector<cv::Point2f> p2 = {cv::Point2f(1,2)};
    cv::Mat mat2(p2);

    std::cout << mat2 << std::endl; /* [100, 100] */
    // std::cout << mat2.x << std::endl; /* Bad */
    // std::cout << mat2[0] << std::endl; /* Bad */
    std::cout << mat2.at<float>(0) << " " << mat2.at<float>(1) << std::endl;  /* 1 2 */
    // std::cout << mat2.at<int>(0) << std::endl;  /* Bad : アクセスできるが意味のある数字ではない */
    // std::cout << mat2.at<double>(0) << std::endl;  /* Bad : 2 */


    std::cout << "*****************************" << std::endl;

    std::vector<cv::Point2f> p3 = {cv::Point2f(1,2), cv::Point2f(3,4)};
    cv::Mat mat3(p3);

    /* [1 2;
       3 4] */
    std::cout << mat3 << std::endl; 

    // at関数では保存されているデータを何バイトごとに読み出すかを指定する
    // 指定がおかしければ実行時エラーになるし、正しく指定すれば
    // 細やかなアクセスの方法が可能
    std::cout << mat3.at<float>(0) << " " << mat3.at<float>(1) << std::endl; /* 1 2 */
    std::cout << mat3.at<float>(2) << " " << mat3.at<float>(3) << std::endl; /* 3 4 */

    std::cout << mat3.at<cv::Point2f>(0) << std::endl; /* [1 2] */
    std::cout << mat3.at<cv::Point2f>(1) << std::endl; /* [3 4] */


    std::cout << "*****************************" << std::endl;
    std::vector<cv::Point2f> p4 = {cv::Point2f(1,2), cv::Point2f(3,4), cv::Point2f(5,6)};
    cv::Mat mat4(p4);

    /* [1 2;
       3 4;
       5 6] */
    std::cout << mat4 << std::endl;
    std::cout << mat4.dims << " " << mat4.rows << " " << mat4.cols << std::endl; /* 2 3 1 */
    std::cout << mat4.size() << std::endl; /* [1 x 3] */


    std::cout << "*****************************" << std::endl;
    cv::Mat mat5 = (cv::Mat_<double>(3,3) << 1,2,3,4,5,6,7,8,9);
    std::cout << mat5 << std::endl;
    std::cout << mat5.dims << " " << mat5.size() << std::endl;




    // -----------------------------------
    //  Mat の初期化
    // -----------------------------------

    /* 3x3行列：初期化されていない値が表示される */
    cv::Mat mat6(3,3, CV_32F);
    std::cout << mat6 << std::endl;

    /* 3x3行列：全ての要素が1で初期化されている
        [1, 1, 1;
         1, 1, 1;
         1, 1, 1]
    */
    cv::Mat mat7(3,3, CV_32F, cv::Scalar(1));
    std::cout << mat7 << std::endl; 
   
    /* 3チャンネルの2x2行列：
        [1, 0, 0, 1, 0, 0;
         1, 0, 0, 1, 0, 0]
    */
    cv::Mat mat8(2,2, CV_32FC3, cv::Scalar(1));
    std::cout << mat8 << std::endl;
    
    /* 3チャンネルの2x2行列：
        [1, 2, 3, 1, 2, 3;
         1, 2, 3, 1, 2, 3]
    */
    cv::Mat mat9(2,2, CV_32FC3, cv::Scalar(1,2,3));
    std::cout << mat9 << std::endl;





    // -----------------------------------
    //  Mat の要素へアクセス
    // -----------------------------------
    
    /*
          [1, 2, 3, 1, 2, 3;
           1, 2, 3, 1, 2, 3;
           1, 2, 3, 1, 2, 3]
         
         cv::Mat は以下の考え方らしい
         3 x 2 の行列の、各要素がチャンネルを持っている

          [1, 2, 3, | 1, 2, 3;
           ---------| -------
           1, 2, 3, | 1, 2, 3;
           ---------| -------
           1, 2, 3, | 1, 2, 3]

         dims = 2
         size = [2 x 3]
         rows = 3
         cols = 2
         channels = 3
    */
    cv::Mat mat10(3, 2, CV_32FC3, cv::Scalar(1,2,3));
    std::cout << mat10 << std::endl;
    std::cout << mat10.dims << " "<< mat10.size() << " " << mat10.rows << " " << mat10.cols << " " << mat10.channels() << std::endl;
    
    // std::cout << mat10.at<float> << std::endl; /* Bad : コンパイルエラー */

    /*
        インデックスを適切に調節することで、うまく全てを表示することができる。
        1 2 3 1 2 3
        1 2 3 1 2 3
        1 2 3 1 2 3
    */
    for(int idx=0; idx<mat10.rows; idx++){
        for(int jdx=0; jdx<mat10.cols; jdx++){
            std::cout 
                << mat10.at<float>( mat10.channels() * mat10.cols * idx + 3*jdx) << " " 
                << mat10.at<float>( mat10.channels() * mat10.cols * idx + 1 + 3*jdx) << " " 
                << mat10.at<float>( mat10.channels() * mat10.cols * idx + 2 + 3*jdx) << " ";
           }
            std::cout << std::endl; /* Bad : コンパイルエラー */
    }


    // -----------------------------------
    //  行列計算のためのMatの性質
    //  線形演算するためには Eigen とかを使えばいいのだが、
    //  簡単にOpenCVだけで完結させるための技術をまとめる
    // -----------------------------------
    
    std::cout << "*****************************" << std::endl;
   
    /* 2 x 2 行列を配列から初期化する 
        [1, 2;
         3, 4]
    */
    float data[] = {1,2,3,4};
    cv::Mat mat(2,2,CV_32F,data); // CV_32F はデフォルトで CV_32FC1 と同じ
    std::cout << mat << std::endl;
    for (int idx=0; idx < mat.rows * mat.cols; idx++)
        std::cout << mat.at<float>(idx) << " ";
    std::cout << std::endl;

    std::cout << mat.dot(mat) << std::endl; // 30 : 要素同士の積をとって、総和を返している

    /* 行列積
       [1, 4;
        9, 16]
    */
    std::cout << mat.mul(mat) << std::endl;  // mat に変更は加わらない
    
    /*
        チャンネル毎の総和
        なぜか4チャンネル出されている
        [10, 0, 0, 0]
    */
    std::cout << cv::sum(mat) << std::endl; 

    /* 転置
        [1, 3;
         2, 4]
    */
    std::cout << mat.t() << std::endl;

    cv::Mat rot = cv::getRotationMatrix2D(cv::Point2f(0,0), 60, 1);
    std::cout << rot << std::endl;
    std::cout << rot.dims << " " << rot.rows << " " << rot.cols << std::endl;



    return 0;
}
