//
//  threshold.cpp
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/2.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#include <opencv2/opencv.hpp>
#include "threshold.hpp"

#include "utils.hpp"

using namespace cv;

void meanBinaryThreshold(Mat& src, Mat& dst, int blockSize, double C) {
    Mat mean;
    boxFilter(src, mean, CV_64F, Size(blockSize, blockSize));
    subtract(src, mean, mean, noArray(), CV_64F);
    add(mean, Scalar(C), mean, noArray(), CV_64F);
    
    threshold(mean, dst, 0, 255, CV_THRESH_BINARY);
    dst.convertTo(dst, CV_8U);
}

void gaussianBinaryThreshold(Mat& src, Mat& dst, int blockSize, double C) {
    Mat mean;
    
    src.convertTo(dst, CV_64F);
    GaussianBlur(dst, mean, Size(blockSize, blockSize), 0, 0);
    subtract(src, mean, mean, noArray(), CV_64F);
    add(mean, Scalar(C), mean, noArray(), CV_64F);
    
    threshold(mean, dst, 0, 255, CV_THRESH_BINARY);
    dst.convertTo(dst, CV_8U);
}
