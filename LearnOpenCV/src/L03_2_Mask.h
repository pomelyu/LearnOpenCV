//
//  L03_2_Mask.h
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/2.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#ifndef L03_2_Mask_h
#define L03_2_Mask_h

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "utils.hpp"

#define all_zero Mat::zeros(s, type)

using namespace std;
using namespace cv;

void ch03_2_mask() {
    Mat image = imread("res/lenna.png");
    Size s = image.size();
    int type = image.type();
    int h = s.height;
    int w = s.width;
    
    Mat cropped = image.rowRange(h/4, h*3/4).colRange(w/4, w*3/4);
    
    Mat circleMask = all_zero;
    Mat rectMask = all_zero;
    Mat andMask = all_zero;
    Mat xorMask = all_zero;
    Mat invMask = all_zero;
    circle(circleMask, Point(w/2, h/2), w/4, Scalar(255, 255, 255), -1);
    rectangle(rectMask, Point(0, 0), Point(w/2, h/2), Scalar(255, 255, 255), -1);
    bitwise_and(circleMask, rectMask, andMask);
    bitwise_xor(circleMask, rectMask, xorMask);
    bitwise_not(circleMask, invMask);
    
    Mat maskedCircle = all_zero;
    Mat maskedRect = all_zero;
    Mat maskedAnd = all_zero;
    Mat maskedXor = all_zero;
    Mat maskedInv = all_zero;
    bitwise_and(image, circleMask, maskedCircle);
    bitwise_and(image, rectMask, maskedRect);
    bitwise_and(image, andMask, maskedAnd);
    bitwise_and(image, xorMask, maskedXor);
    bitwise_and(image, invMask, maskedInv);
    
    {
        vector<string> subtitles = {
            "image", "cropped",
            "circle mask", "masked",
            "rect mask", "masked",
            "and mask", "masked",
            "xor mask", "masked",
            "inv mask", "masked",
        };
        vector<Mat> images = {
            image, cropped,
            circleMask, maskedCircle,
            rectMask, maskedRect,
            andMask, maskedAnd,
            xorMask, maskedXor,
            invMask, maskedInv,
        };
        ShowImages("Crop and Mask", subtitles, images, {3, 4}, 200);
    }
    
}

#endif /* L03_2_Mask_h */
