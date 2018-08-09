//
//  L04_2_Contour_Features.h
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/9.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#ifndef L04_2_Contour_Features_h
#define L04_2_Contour_Features_h

#include <iostream>
#include <string>
#include <algorithm>            // std::sort
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


// Reference:
// https://docs.opencv.org/3.1.0/dd/d49/tutorial_py_contour_features.html
void ch04_2_contour_features() {
    Mat image = imread("res/shapes.png", IMREAD_GRAYSCALE);
    Canny(image, image, 60, 120);
    threshold(image, image, 127, 255, THRESH_BINARY);
    
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(image, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    
    // ContourArea
    vector<pair<double, int> > areas;
    for (int i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[0]);
        areas.push_back({ area, i });
    }

    sort(areas.begin(), areas.end(), [](pair<double, int> p1, pair<double, int> p2) {
        return p1.first < p2.first;
    });
    
    Mat imageArea;
    image.copyTo(imageArea);
    namedWindow("Contours");
    for (int i = 0; i < areas.size(); i++) {
        drawContours(imageArea, contours, areas[i].second, Scalar(127), 5);
        imshow("Contours", imageArea);
        waitKey();
    }
    
    // Contour Moment
    for (int i = 0; i < areas.size(); i++) {
        int contourIdx = areas[i].second;
        Moments mu = moments(contours[contourIdx]);
        int cx = (int)(mu.m10 / mu.m00);
        int cy = (int)(mu.m01 / mu.m00);
        circle(imageArea, Point(cx, cy), 5, Scalar(127), -1);
        imshow("Contours", imageArea);
        waitKey();
    }
}

#endif /* L04_2_Contour_Features_h */
