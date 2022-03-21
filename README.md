
# Mat

- 次元（mat.dims）：配列の次元で、2次元以上
- チャンネル

## 回転行列

通常の回転行列と角度の符号が反転している（$cos(-\theta)=cos\theta$なので sin だけ変わっているように見える。
これは通常の座標軸と異なり、y軸の正方向が下を向いているので反転しているだけ。


# calcHist 

## 	

```cpp
cv::calcHist (
    const Mat *images,     // 画像
    int nimages,           // 処理する画像数 
    const int *channels,   // チャンネル数（グレースケールなら1, RGBなら3）
    InputArray mask,       // ヒストグラム処理を行わない箇所の指定
    OutputArray hist,      // 出力するヒストグラム 
    int dims,              // hist の次元数 
    const int *histSize,   // 各次元のヒストグラムのサイズ 
    const float **ranges,  // ビンのサイズ
    bool uniform=true,     // 均等なビンかどうか
    bool accumulate=false  // 積み上げるかどうか
)
```
