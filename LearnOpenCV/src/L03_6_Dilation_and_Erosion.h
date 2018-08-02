//
//  L03_6_Dilation_and_Erosion.h
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/2.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#ifndef L03_6_Dilation_and_Erosion_h
#define L03_6_Dilation_and_Erosion_h

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "utils.hpp"
#include "morphology.hpp"

using namespace std;
using namespace cv;

void ch03_6_dilation_and_erosion() {
    Mat image = imread("res/fingerprint.png", IMREAD_GRAYSCALE);
    threshold(image, image, 127, 255, CV_8U);
    Mat dilated, eroded, opened, closed;
    
    Mat kernel = Mat::ones(7, 7, CV_8U);
    
    dilate(image, dilated, kernel);
    erode(image, eroded, kernel);
    morphologyEx(image, opened, MORPH_OPEN, kernel);
    morphologyEx(image, closed, MORPH_CLOSE, kernel);
    
    {
        vector<string> subtitles = { "origin", "dilate", "erode", "opening", "closing" };
        vector<Mat> images = { image, dilated, eroded, opened, closed };
        ShowImages("Dilation and Erosion", subtitles, images, {1, 5}, 200);
    }
    
    Mat myDilated, myEroded, myOpened, myClosed;
    cy::dilate(image, myDilated, kernel);
    cy::erode(image, myEroded, kernel);
    cy::opening(image, myOpened, kernel);
    cy::closing(image, myClosed, kernel);
    
    {
        vector<string> subtitles = {
            "dilate", "my-dilate",
            "erode", "my-erode",
            "opening", "my-opening",
            "closing", "my-closing"
        };
        vector<Mat> images = {
            dilated, myDilated,
            eroded, myEroded,
            opened, myOpened,
            closed, myClosed
        };
        ShowImages("Implement Dilation and Erosion", subtitles, images, {2, 4}, 200, false);
    }
}

#endif /* L03_6_Dilation_and_Erosion_h */
