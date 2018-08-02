//
//  threshold.hpp
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/2.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#ifndef threshold_hpp
#define threshold_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

void meanBinaryThreshold(Mat& src, Mat& dst, int blockSize, double C);
void gaussianBinaryThreshold(Mat& src, Mat& dst, int blockSize, double C);

#endif /* threshold_hpp */
