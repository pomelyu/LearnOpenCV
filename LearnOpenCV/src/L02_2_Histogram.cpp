//
//  L02_2_Histogram.cpp
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/7/31.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "../util/utils.hpp"

using namespace std;
using namespace cv;

void drawHistImg(const Mat &src, Mat &dst){
    int histSize = 256;
    float histMaxValue = 0;
    for(int i=0; i<histSize; i++){
        float tempValue = src.at<float>(i);
        if(histMaxValue < tempValue){
            histMaxValue = tempValue;
        }
    }
    
    float scale = (0.9*256)/histMaxValue;
    for(int i=0; i<histSize; i++){
        int intensity = static_cast<int>(src.at<float>(i)*scale);
        line(dst,Point(i,255),Point(i,255-intensity),Scalar(0));
    }
}

void ch02_2_histogram() {
    Mat image = imread("res/lenna.png");
    
    int bins = 256;
    int histSize = bins;
    float colorRange[] = {0, 255};
    const float* ranges[] = {colorRange};
    
    vector<Mat> hists;
    double maxHistValue = 0;
    for (int channel = 0; channel < 3; channel++) {
        Mat hist;
        calcHist(&image, 1, &channel, Mat(), hist, 1, &histSize, ranges, true, false);
        double maxValue;
        minMaxLoc(hist, 0, &maxValue, 0, 0);
        
        hists.push_back(hist);
        maxHistValue = max(maxHistValue, maxValue);
    }
    
    int scale = 20;
    Mat histImage = Mat(maxHistValue, bins*scale, CV_8UC3, Scalar(255, 255, 255));
    Scalar colors[] = {Scalar(0, 0, 255), Scalar(0, 255, 0), Scalar(255, 0, 0)};
    for(int i = 0; i < 3; i++) {
        Mat hist = hists[i];
        Scalar color = colors[i];
        for(int j = 0; j < bins - 1; j++) {
            Point p1(scale*j, maxHistValue - hist.at<float>(j));
            Point p2(scale*(j+1), maxHistValue - hist.at<float>(j+1));
            line(histImage, p1, p2, color, scale);
        }
    }
    
    vector<Mat> images = { image, histImage };
    ShowManyImages("Histogram", images);
}
