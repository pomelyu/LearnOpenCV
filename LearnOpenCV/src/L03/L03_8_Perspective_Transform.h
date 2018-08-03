//
//  L03_8_Perspective_Transform.h
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/3.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#ifndef L03_8_Perspective_Transform_h
#define L03_8_Perspective_Transform_h

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "utils.hpp"

using namespace std;
using namespace cv;

void ch03_8_perspective() {
    Mat scanned = imread("res/scan.jpg");
    
    Point2f src1(320, 15);
    Point2f src2(700, 215);
    Point2f src3(85, 610);
    Point2f src4(530, 780);
    Point2f src[] = { src1, src2, src3, src4 };
    Point2f dst1(0, 0);
    Point2f dst2(420, 0);
    Point2f dst3(0, 594);
    Point2f dst4(420, 594);
    Point2f dst[] = { dst1, dst2, dst3, dst4 };
    Mat m = getPerspectiveTransform(src, dst);
    
    Mat transed;
    warpPerspective(scanned, transed, m, Size(420, 594));
    
    circle(scanned, Point(320, 15), 10, Scalar(0, 255, 0), -1);
    circle(scanned, Point(700, 215), 10, Scalar(0, 255, 0), -1);
    circle(scanned, Point(85, 610), 10, Scalar(0, 255, 0), -1);
    circle(scanned, Point(530, 780), 10, Scalar(0, 255, 0), -1);
    {
        vector<string> subtitles = { "origin", "perpective" };
        vector<Mat> images = { scanned, transed };
        ShowImages("Perspective Transform", subtitles, images, {1, 2});
    }
}

#endif /* L03_8_Perspective_Transform_h */
