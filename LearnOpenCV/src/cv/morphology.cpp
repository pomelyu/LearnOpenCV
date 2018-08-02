//
//  morphology.cpp
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/2.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#include "morphology.hpp"
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

void cy::dilate(const Mat& src, Mat& dst, const Mat& kernel) {
    Mat filter;
    threshold(kernel, filter, 0, 1, CV_8U);
    filter2D(src, dst, -1, filter);
}

void cy::erode(const Mat&src, Mat& dst, const Mat& kernel) {
    Mat filter;
    threshold(kernel, filter, 0, 1, CV_8U);
    threshold(src, dst, 0, 1, CV_8U);
    filter2D(dst, dst, -1, filter);
    double norm = sum(filter)[0];
    threshold(dst, dst, norm-0.5, 255, CV_8U);
}

void cy::opening(const Mat&src, Mat&dst, const Mat& kernel) {
    cy::erode(src, dst, kernel);
    cy::dilate(dst, dst, kernel);
}

void cy::closing(const Mat&src, Mat&dst, const Mat& kernel) {
    cy::dilate(src, dst, kernel);
    cy::erode(dst, dst, kernel);
}
