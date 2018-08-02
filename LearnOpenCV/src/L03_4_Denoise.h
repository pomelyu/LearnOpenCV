//
//  L03_4_Denoise.h
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/2.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#ifndef L03_4_Denoise_h
#define L03_4_Denoise_h

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "utils.hpp"

using namespace std;
using namespace cv;

void ch03_4_denoise() {
    Mat image = imread("res/lenna.png");
    Size s = image.size();
    int w = s.width;
    int h = s.height;
    
    Mat pepperNoisy = Mat::zeros(s, image.type());
    image.copyTo(pepperNoisy);
    RNG rng(cvGetTickCount());
    for (int i = 0; i < 10000; i++) {
        int x = rng.uniform(0, w);
        int y = rng.uniform(0, h);
        pepperNoisy.at<Vec3b>(Point(x, y)) = 0;
    }
    
    Mat pepperMedian = Mat::zeros(s, image.type());
    medianBlur(pepperNoisy, pepperMedian, 5);
    
    // NIMean(None Local Mean): replace the window by averaging the similar windows in the image
    Mat pepperNIMean = Mat::zeros(s, image.type());
    fastNlMeansDenoisingColored(pepperNoisy, pepperNIMean, 10, 10);
    
    Mat gaussianNoisy = Mat::zeros(s, image.type());
    randn(gaussianNoisy, 0, 50);
    gaussianNoisy = image + gaussianNoisy;
    
    Mat gaussianMedian = Mat::zeros(s, image.type());
    medianBlur(gaussianNoisy, gaussianMedian, 5);
    
    Mat gaussianNIMean = Mat::zeros(s, image.type());
    fastNlMeansDenoisingColored(gaussianNoisy, gaussianNIMean, 10, 10);
    
    {
        vector<string> subtitles = {
            "image", "pepper noisy", "gaussian noisy",
            "", "pepper by median", "gaussian by median",
            "", "pepper by NIMean", "gaussian by NIMean",
        };
        vector<Mat> images = {
            image, pepperNoisy, gaussianNoisy,
            Mat::zeros(s, image.type()), pepperMedian, gaussianMedian,
            Mat::zeros(s, image.type()), pepperNIMean, gaussianNIMean,
        };
        ShowImages("Denoise", subtitles, images, {3, 3}, 250);
    }
}

#endif /* L03_4_Denoise_h */
