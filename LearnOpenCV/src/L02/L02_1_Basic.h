//
//  L02_1_Basic.h
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/2.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#ifndef L02_1_Basic_h
#define L02_1_Basic_h

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "utils.hpp"

using namespace std;
using namespace cv;

void ch02_1_basic() {
    // $$ Load image
    Mat image = imread("res/lenna.png");
    
    // $$ Show image information
    // $ Mat.depth() - data type of each channels
    //   CV_8U=0, CV_8S=1, CV_16U=2, CV_16S=3, CV_32S=4, CV_32F=5, CV_64F=6
    // $ Mat.channels() - # of channels (3 for color, 1 for gray)
    Size s = image.size();
    cout << "Load image with height: " << s.height
    << ", width: " << s.width
    << ", channels: " << image.channels()
    << endl;
    MatType(image);
    
    // $$ Convert to gray scale
    Mat gray(s, CV_8U);
    cvtColor(image, gray, CV_BGR2GRAY);
    
    // $$ Show gray image information
    cout << "Gray scale image with height: " << gray.size().height
    << ", width: " << gray.size().width
    << ", channels: " << gray.channels()
    << endl;
    MatType(gray);
    
    {
        vector<string> subtitles = {"image", "gray"};
        vector<Mat> images = {image, gray};
        ShowImages("Gray image", subtitles, images, {1, 2});
    }
    
    // $$ Save gray image
    imwrite("out/lenna_gray.png", gray);
    
    // $$ Split image into three color channels
    Mat black = Mat::zeros(s, CV_8U);
    vector<Mat> rgb_channels;
    split(image, rgb_channels);
    Mat B, G, R;
    vector<Mat> b_channels = { rgb_channels[0], black, black };
    vector<Mat> g_channels = { black, rgb_channels[1], black };
    vector<Mat> r_channels = { black, black, rgb_channels[2] };
    merge(b_channels, B);
    merge(g_channels, G);
    merge(r_channels, R);
    
    {
        vector<string> subtitles = {"image", "Blue", "Green", "Red"};
        vector<Mat> images = {image, B, G, R};
        ShowImages("RGB Channels", subtitles, images, {1, 4}, 300);
    }
    
    
    // $$ Split image into HSV channels
    Mat hsv = Mat(s, CV_8UC3);
    cvtColor(image, hsv, CV_BGR2HSV);
    
    vector<Mat> hsv_channels;
    split(hsv, hsv_channels);
    
    double h_min, h_max, s_min, s_max, v_min, v_max;
    minMaxLoc(hsv_channels[0], &h_min, &h_max); // In openCV, this range of Hue is 0 ~ 179 (8bit)
    minMaxLoc(hsv_channels[1], &s_min, &s_max);
    minMaxLoc(hsv_channels[2], &v_min, &v_max);
    cout << "Hue: [" << h_min << ", " << h_max << "], "
    << "Saturation: [" << s_min << ", " << s_max << "], "
    << "Value: [" << v_min << ", " << v_max << "]" << endl;
    
    {
        vector<string> subtitles = {"image", "Hue", "Saturation", "Value"};
        vector<Mat> images = {image, hsv_channels[0], hsv_channels[1], hsv_channels[2]};
        ShowImages("HSV Channels", subtitles, images, {1, 4}, 300);
    }
}

#endif /* L02_1_Basic_h */
