//
//  L03_7_Edge_detection.h
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/3.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#ifndef L03_7_Edge_detection_h
#define L03_7_Edge_detection_h

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "utils.hpp"

using namespace std;
using namespace cv;

void ch03_7_edge_detection() {
    Mat image = imread("res/lenna.png", IMREAD_GRAYSCALE);
    
    // ** Sobel Operator
    // void Sobel( InputArray src, OutputArray dst, int ddepth, int dx, int dy,
    //             int ksize=3, double scale=1, double delta=0, int borderType=BORDER_DEFAULT)
    // calculate sqrt(Gx^2 + Gy^2), Gx, Gy is the dx-th, dy-th derivatives seperately
    Mat sobelX, sobelY, sobelXY;
    Sobel(image, sobelX, -1, 1, 0, 3);
    Sobel(image, sobelY, -1, 0, 1, 3);
    Sobel(image, sobelXY, -1, 1, 1, 3);
    
    // ** Laplacian Operator
    // void Laplacian( InputArray src, OutputArray dst, int ddepth,
    //                 int ksize=1, double scale=1, double delta=0, int borderType=BORDER_DEFAULT )
    // calculate sum of 2nd derivatives of x, y. i.e. d^2(x) + d^2(y)
    Mat laplacian;
    Laplacian(image, laplacian, -1, 3);
    
    // ** Canny edge detector
    // void Canny( InputArray image, OutputArray edges,
    //             double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false )
    // apertureSize: ksize of sobel operator
    Mat canny;
    Canny(image, canny, 70, 180, 3);
    
    {
        vector<string> subtitles = { "origin", "Sobel x", "Sobel y", "Sobel xy", "Laplacian", "Canny(70, 180)" };
        vector<Mat> images = { image, sobelX, sobelY, sobelXY, laplacian, canny };
        ShowImages("edge", subtitles, images, {2, 3}, 250);
    }
}

#endif /* L03_7_Edge_detection_h */
