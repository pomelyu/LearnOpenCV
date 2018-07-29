//
//  L02_Basic.cpp
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/7/29.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "../util/utils.cpp"

using namespace std;
using namespace cv;

void ch02_basic() {
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
    
    namedWindow("Origin", WINDOW_AUTOSIZE);
    imshow("Origin", image);
    waitKey(0);
    
    // $$ Convert to gray scale
    Mat gray(s, CV_8U);
    cvtColor(image, gray, CV_RGB2GRAY);
    
    // $$ Show gray image information
    cout << "Gray scale image with height: " << gray.size().height
         << ", width: " << gray.size().width
         << ", channels: " << gray.channels()
         << endl;
    MatType(gray);
    
    namedWindow("Gray", WINDOW_AUTOSIZE);
    imshow("Gray", gray);
    waitKey(0);
    
    // $$ Save gray image
    imwrite("out/lenna_gray.png", gray);
    
    destroyAllWindows();
}
