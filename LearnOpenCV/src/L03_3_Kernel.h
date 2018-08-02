//
//  L03_3_Kernel.h
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/2.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#ifndef L03_3_Kernel_h
#define L03_3_Kernel_h

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "utils.hpp"

using namespace std;
using namespace cv;

vector<Mat> applyKernel(vector<Mat> inputs, Mat kernel);

void ch03_3_kernel() {
    Mat image = imread("res/lenna.png");
    Size s = image.size();

    Mat peak = Mat(s, CV_8U, Scalar(0));
    circle(peak, Point(s.height/2, s.width/2), 15, Scalar(255, 255, 255), -1);
    
    vector<Mat> images = { peak, image };
    
    // Kernels
    Mat avg_kernel(10, 10, CV_32F, Scalar(1.0f/100));
    vector<Mat> filteredAvg = applyKernel(images, avg_kernel);
    
    float sharp_data[] = {
        -1.0f, -1.0f, -1.0f,
        -1.0f,  9.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
    };
    Mat sharp_kernel(3, 3, CV_32F, sharp_data);
    vector<Mat> filteredSharp = applyKernel(images, sharp_kernel);
    
    float sobel_x_data[] = {
        1.0f, 0.0f, -1.0f,
        2.0f, 0.0f, -2.0f,
        1.0f, 0.0f, -1.0f,
    };
    Mat sobel_x_kernel(3, 3, CV_32F, sobel_x_data);
    vector<Mat> filteredSobelX = applyKernel(images, sobel_x_kernel);
    
    float sobel_y_data[] = {
         1.0f,  2.0f,  1.0f,
         0.0f,  0.0f,  0.0f,
        -1.0f, -2.0f, -1.0f,
    };
    Mat sobel_y_kernel(3, 3, CV_32F, sobel_y_data);
    vector<Mat> filteredSobelY = applyKernel(images, sobel_y_kernel);
    
    {
        vector<string> subtitles = {
            "peak", "image",
            "avg_kernel", "avg",
            "sharp_kernel", "sharp",
            "sobel_x_kernel", "sobel_x",
            "sobel_y_kernel", "sobel_y",
        };
        vector<Mat> images = {
            peak, image,
            filteredAvg[0], filteredAvg[1],
            filteredSharp[0], filteredSharp[1],
            filteredSobelX[0], filteredSobelX[1],
            filteredSobelY[0], filteredSobelY[1],
        };
        ShowImages("Kernels", subtitles, images, {2, 5}, 250, false);
    }
    
    
    // Kernels: Blur
    Mat filteredPeakGaussian;
    Mat filteredGaussian;
    GaussianBlur(peak, filteredPeakGaussian, Size(9, 9), 1, 20);
    GaussianBlur(image, filteredGaussian, Size(9, 9), 1, 20);
    
    // Bilateral blur would perse edge
    Mat filteredPeakBilateral;
    Mat filteredBilateral;
    bilateralFilter(peak, filteredPeakBilateral, 9, 30, 30);
    bilateralFilter(image, filteredBilateral, 9, 30, 30);
    
    {
        vector<string> subtitles = {
            "peak", "image",
            "gaussian", "gaussian",
            "bilateral", "bilateral",
        };
        vector<Mat> images = {
            peak, image,
            filteredPeakGaussian, filteredGaussian,
            filteredPeakBilateral, filteredBilateral,
        };
        ShowImages("Kernels Blur", subtitles, images, {2, 3}, 300, false);
    }
}

vector<Mat> applyKernel(vector<Mat> inputs, Mat kernel) {
    vector<Mat> result;
    for (int i = 0; i < inputs.size(); i++) {
        Mat image = inputs[i];
        Mat filtered = Mat::zeros(image.size(), image.type());
        filter2D(image, filtered, -1, kernel);
        result.push_back(filtered);
    }
    return result;
}

#endif /* L03_3_Kernel_h */
