//
//  L03_5_Thresholding.h
//  
//
//  Created by Chien Chin-yu on 2018/8/2.
//

#ifndef L03_5_Thresholding_h
#define L03_5_Thresholding_h

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "cvplot.h"
#include "utils.hpp"
#include "threshold.hpp"

using namespace std;
using namespace cv;

void ch03_5_thresholding() {
    Mat gradation = Mat::zeros(256, 256, CV_8U);
    for (int i = 0; i < 256; i++) {
        gradation.row(i) = i;
    }
    
    {
        vector<int> threshold_type = {
            CV_THRESH_BINARY, CV_THRESH_BINARY_INV, CV_THRESH_TRUNC, CV_THRESH_TOZERO, CV_THRESH_TOZERO_INV,
        };
        vector<string> subtitles = { "origin", "binary", "binary inv", "trunc", "to zero", "to zero inv" };
        vector<Mat> images = { gradation };
        for (int i = 0; i < threshold_type.size(); i++) {
            Mat dst;
            threshold(gradation, dst, 127, 255, threshold_type[i]);
            images.push_back(dst);
        }
        ShowImages("Simple Threshold", subtitles, images, {2, 3}, 256);
    }
    
    Mat image = imread("res/soduku.jpg", IMREAD_GRAYSCALE);
    Mat thresBinary;
    threshold(image, thresBinary, 127, 255, CV_THRESH_BINARY);
    Mat thresOTSU;
    // OTSU algorithm is one of global thresholding,
    // which tries to find the threshold which could minize the variance among black & white part
    double otsu_value = threshold(image, thresOTSU, 127, 255, CV_THRESH_BINARY|CV_THRESH_OTSU);
    
    Mat thresMean;
    adaptiveThreshold(image, thresMean, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 11, 2);
    Mat thresGaussian;
    adaptiveThreshold(image, thresGaussian, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 11, 2);
    
    Mat dummy = Mat::zeros(100, 100, CV_8U);
    {
        vector<string> subtitles = { "origin", "", "binary", "OTSU", "ada-mean", "ada-gaussian" };
        vector<Mat> images = {image, dummy, thresBinary, thresOTSU, thresMean, thresGaussian};
        ShowImages("Adaptive thresholding", subtitles, images, {2, 3}, 300, false);
    }
    
    // Show OTSU result
    {
        Mat hist;
        int histSize = 256;
        float colorRanges[] = {0, 255};
        const float* ranges[] = { colorRanges };
        calcHist(&image, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);
        
        int FRAME_SIZE = 300;
        vector<pair<float, float>> data;
        cvplot::Window::current("OTSU threshold").offset({60, 100});
        
        {
            auto name = "image";
            cvplot::setWindowTitle(name, "image");
            cvplot::moveWindow(name, 0, 0);
            cvplot::resizeWindow(name, FRAME_SIZE, FRAME_SIZE);
            auto &view = cvplot::Window::current().view(name);
            Mat converted;
            cvtColor(image, converted, CV_GRAY2BGR);
            view.drawImage(&converted);
            view.finish();
        }
        
        {
            auto name = "gray hist";
            cvplot::setWindowTitle(name, "intensity histogram");
            cvplot::moveWindow(name, FRAME_SIZE, 0);
            cvplot::resizeWindow(name, FRAME_SIZE, FRAME_SIZE);
            auto &figure = cvplot::figure(name);
            for (int i = 0; i < 256; i++) { data.push_back({i, hist.at<float>(i)}); }
            figure.series("intensity").set(data).type(cvplot::Histogram).color(cvplot::Color(0, 0, 0, 127));
            
            double maxValue;
            minMaxLoc(hist, 0, &maxValue);
            data.clear();
            data.push_back({ otsu_value, 0 });
            data.push_back({ otsu_value, maxValue});
            figure.series("otsu threshold").set(data).type(cvplot::Line).color(cvplot::Blue);
            figure.show(true);
        }
        waitKey();
    }
    
    // Implementation result
    Mat myMean;
    meanBinaryThreshold(image, myMean, 11, 2);
    Mat myGaussian;
    gaussianBinaryThreshold(image, myGaussian, 11, 2);
    {
        vector<string> subtitles = { "ada-mean", "my-mean", "ada-gaussian", "my-gaussian" };
        vector<Mat> images = {thresMean, myMean, thresGaussian, myGaussian};
        ShowImages("Adaptive thresholding", subtitles, images, {2, 2}, 300);
    }
}

#endif /* L03_5_Thresholding_h */
