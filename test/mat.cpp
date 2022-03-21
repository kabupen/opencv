#include <iostream>
#include <opencv2/opencv.hpp>

void print_title(std::string title){
    std::cout << "\n---- " << title << std::endl;
}

void print_mat(cv::Mat mat){
    std::cout << mat << std::endl; 
}

void check_size(cv::Mat mat){
    print_mat(mat);
    std::cout << "dims =" << mat.dims << ", size = " << mat.size() << std::endl; 
}

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


    ///////////////////////////////////////////////////////////////////////
    
    
    std::cout << "--------------------------------" << std::endl;
    std::cout << " Mat への変換 " << std::endl;
    std::cout << "--------------------------------" << std::endl;

    std::vector<cv::Point2f> p2 = {cv::Point2f(1,2)};
    cv::Mat mat2(p2);
    
    /* [1 2] */
    std::cout << mat2 << std::endl;
    // std::cout << mat2.x << std::endl; /* Bad */
    // std::cout << mat2[0] << std::endl; /* Bad */
    std::cout << mat2.at<float>(0) << " " << mat2.at<float>(1) << std::endl;  /* 1 2 */
    // std::cout << mat2.at<int>(0) << std::endl;  /* Bad : アクセスできるが意味のある数字ではない */
    // std::cout << mat2.at<double>(0) << std::endl;  /* Bad : 2 */


    std::cout << "*****************************" << std::endl;



    std::cout << "*****************************" << std::endl;
    std::vector<cv::Point2f> p4 = {cv::Point2f(1,2), cv::Point2f(3,4), cv::Point2f(5,6)};
    cv::Mat mat4(p4);

    /* [1 2;
       3 4;
       5 6] */
    std::cout << mat4 << std::endl;
    std::cout << mat4.dims << " " << mat4.rows << " " << mat4.cols << std::endl; /* 2 3 1 */
    std::cout << mat4.size() << std::endl; /* [1 x 3] */

    

    {
        cv::Mat mat = (cv::Mat_<double>(3,3) << 1,2,3,4,5,6,7,8,9);
        std::cout << mat << std::endl;
        std::cout << mat.dims << " " << mat.size() << std::endl;
    }
   


    {
        std::cout << "\n---- ループを回して初期化 " << std::endl;
        cv::Mat mat(3,3, CV_32FC1, cv::Scalar(0));
        /*
            [0, 0, 0;
             0, 0, 0;
             0, 0, 0]

             size [3 x 3]
        */
        check_size(mat);
        
        // 単位行列を作ってみる
        for(int idx=0; idx<mat.rows; idx++){
            for(int jdx=0; jdx<mat.cols; jdx++){
                if (idx==jdx)
                    mat.at<float>(idx, jdx) = 1;
            }
        }
        
        /*
            [1, 0, 0;
             0, 1, 0;
             0, 0, 1]
             
             size [3 x 3]
        */
        print_mat(mat);
    }



    {
        std::cout << "\n---- Point2f から初期化 " << std::endl;

        std::vector<cv::Point2f> points = {cv::Point2f(1,2), cv::Point2f(3,4)};
        cv::Mat mat(points);

        /* 
           [1 2;
           3 4] 

           dims = 2
           size() : [1 x 2] * 注意 *

           Point2f で初期化しているので、cv::Mat のサイズが想定と違っていることに注意
           [(1 2);
           (3 4)]
           こういうイメージで、2行1列に見えてしまっている
         */
         check_size(mat);

         std::cout << mat.reshape(1).size() << std::endl;


        // at関数では保存されているデータを何バイトごとに読み出すかを指定する
        // 指定がおかしければ実行時エラーになるし、正しく指定すれば
        // 細やかなアクセスの方法が可能
        std::cout << mat.at<float>(0) << " " << mat.at<float>(1) << std::endl; /* 1 2 */
        std::cout << mat.at<float>(2) << " " << mat.at<float>(3) << std::endl; /* 3 4 */

        std::cout << mat.at<cv::Point2f>(0) << std::endl; /* [1 2] */
        std::cout << mat.at<cv::Point2f>(1) << std::endl; /* [3 4] */
    }



    {
        std::cout << "\n---- Point2f から初期化 " << std::endl;

        std::vector<cv::Point2f> points = {cv::Point2f(1,2), cv::Point2f(3,4), cv::Point2f(5,6)};

        /* 
            std::vector の size() --> 要素数
                           data() --> 配列への先頭ポインタ
        */
        std::cout << points.size() << " "  << points.data() << std::endl;

        // 型と既存データを指定した場合のコンストラクタが呼ばれる
        cv::Mat mat(points.size(), 2, CV_32F, points.data());

        /* 
           [1 2;
           3 4] 

           dims = 2
           size() : [2 x 2]
         */
         check_size(mat);
    }



    // -----------------------------------
    //  Mat の初期化
    // -----------------------------------

    {
        std::cout << "\n---- Mat の初期化（初期値指定なし）" << std::endl;
        /* 3x3行列：初期化されていない値が表示される */
        cv::Mat mat(3,3, CV_32F);
        print_mat(mat);
    }

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


    
    {
        std::cout << "\n---- Mat から Point2f " << std::endl;

        std::vector<cv::Point2f> points = {cv::Point2f(1,2), cv::Point2f(3,4), cv::Point2f(5,6)};

        /* 
            std::vector の size() --> 要素数
                           data() --> 配列への先頭ポインタ
        */
        std::cout << points.size() << " "  << points.data() << std::endl;

        // 型と既存データを指定した場合のコンストラクタが呼ばれる
        cv::Mat mat(points.size(), 2, CV_32F, points.data());

        /* 
           [1 2;
           3 4] 

           dims = 2
           size() : [2 x 2]
         */
         check_size(mat);
    }



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
    

    {
        print_title("Mat 各要素の計算");

        float data[] = {1,2,3,4,5,6};
        cv::Mat mat(3,2,CV_32F,data); // CV_32F はデフォルトで CV_32FC1 と同じ
        check_size(mat);

        
        cv::Mat row_sum, col_sum;
        cv::reduce(mat, col_sum, 0, cv::REDUCE_SUM, CV_32F);
        cv::reduce(mat, row_sum, 1, cv::REDUCE_SUM, CV_32F);

        std::cout << "総和：" << cv::sum(mat) << std::endl;
        std::cout << "総和（列）：" << col_sum << std::endl;
        std::cout << "総和（行）：" << row_sum << std::endl;
        
        cv::Mat row_mean, col_mean;
        cv::reduce(mat, col_mean, 0, cv::REDUCE_AVG, CV_32F);
        cv::reduce(mat, row_mean, 1, cv::REDUCE_AVG, CV_32F);

        std::cout << "平均：" << cv::mean(mat) << std::endl;
        std::cout << "平均（列）：" << col_mean << std::endl;
        std::cout << "平均（行）：" << row_mean << std::endl;
    }


    // -----------------------------------
    //  行列計算のためのMatの性質
    //  線形演算するためには Eigen とかを使えばいいのだが、
    //  簡単にOpenCVだけで完結させるための技術をまとめる
    // -----------------------------------
    {
        print_title("行列積");

        float data[] = {1,2,3,4,5,6};
        cv::Mat mat(3,2,CV_32F,data); // CV_32F はデフォルトで CV_32FC1 と同じ
        cv::Mat mat2(2,3,CV_32F,data); // CV_32F はデフォルトで CV_32FC1 と同じ
        /*
           [1, 2;
            3, 4;
            5, 6]

            size = [2 x 3]
        */
        check_size(mat);
        /*
            [1, 2, 3;
             4, 5, 6]
         */
        check_size(mat2);

        /* 
            [1, 4;
             9, 16;
             25, 36]

             mul 要素積 
         */
        std::cout << mat.mul(mat) << std::endl;     /* OK : mat に変更は加わらない */
        // std::cout << mat.mul(mat2) << std::endl; /* Bad: Opencvでは mul は行列積ではなく要素積 */

        // std::cout << mat * mat << std::endl; /* Bad : 通常の行列積のように、形状が違う同士の行列は積を取れない */
        std::cout << mat * mat2 << std::endl;   /* OK : 行列積 */
    }
    


    {
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


    }


    return 0;
}
