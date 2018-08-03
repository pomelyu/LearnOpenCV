//
//  L02_2_Histogram.h
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/2.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#ifndef L02_2_Histogram_h
#define L02_2_Histogram_h

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "cvplot.h"

#include "utils.hpp"

using namespace std;
using namespace cv;

void ch02_2_histogram() {
    Mat image = imread("res/louvre.jpg");
    
    int bins = 256;
    int histSize = bins;
    float colorRange[] = {0, 255};
    const float* ranges[] = {colorRange};
    
    vector<Mat> hists;
    for (int channel = 0; channel < 3; channel++) {
        Mat hist;
        calcHist(&image, 1, &channel, Mat(), hist, 1, &histSize, ranges, true, false);
        hists.push_back(hist);
    }
    
    Mat gray = Mat(image.size(), CV_8U);
    cvtColor(image, gray, CV_BGR2GRAY);
    Mat grayHist;
    calcHist(&gray, 1, 0, Mat(), grayHist, 1, &histSize, ranges, true, false);
    
    
    // Visualize Histogram
    auto FRAME_SIZE = 450;
    vector<pair<float, float>> data;
    cvplot::Window::current("Color Histogram").offset({60, 100});
    
    {
        auto name = "image";
        cvplot::setWindowTitle(name, "image");
        cvplot::moveWindow(name, 0, 0);
        cvplot::resizeWindow(name, FRAME_SIZE, FRAME_SIZE);
        auto &view = cvplot::Window::current().view(name);
        view.drawImage(&image);
        view.finish();
    }
    
    {
        auto name = "gray hist";
        cvplot::setWindowTitle(name, "intensity histogram");
        cvplot::moveWindow(name, FRAME_SIZE, 0);
        cvplot::resizeWindow(name, FRAME_SIZE, FRAME_SIZE);
        auto &figure = cvplot::figure(name);
        data.clear();
        for (int i = 0; i < bins-1; i++) { data.push_back({i, grayHist.at<float>(i)}); }
        figure.series("intensity").set(data).type(cvplot::Histogram).color(cvplot::Black);
        
        figure.show(false);
    }
    
    
    {
        auto name = "color hist";
        cvplot::setWindowTitle(name, "color histogram");
        cvplot::moveWindow(name, FRAME_SIZE*2, 0);
        cvplot::resizeWindow(name, FRAME_SIZE, FRAME_SIZE);
        auto &figure = cvplot::figure(name);
        
        data.clear();
        for (int i = 0; i < bins-1; i++) { data.push_back({i, hists[0].at<float>(i)}); }
        figure.series("blue").set(data).type(cvplot::Line).color(cvplot::Blue);
        
        data.clear();
        for (int i = 0; i < bins-1; i++) { data.push_back({i, hists[1].at<float>(i)}); }
        figure.series("green").set(data).type(cvplot::Line).color(cvplot::Green);
        
        data.clear();
        for (int i = 0; i < bins-1; i++) { data.push_back({i, hists[2].at<float>(i)}); }
        figure.series("red").set(data).type(cvplot::Line).color(cvplot::Red);
        
        figure.show(true);
    }
    
    waitKey();
}

#endif /* L02_2_Histogram_h */
