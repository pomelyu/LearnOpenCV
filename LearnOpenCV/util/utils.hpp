//
//  utils.hpp
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/1.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void MatType( Mat inputMat );
void ShowImages(string title, vector<string> subtitles, vector<Mat> images, pair<int, int> grid, int size=450);

#endif /* utils_hpp */
