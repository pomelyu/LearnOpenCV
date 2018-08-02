//
//  L03_1_Transform.h
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/2.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#ifndef L03_1_Transform_h
#define L03_1_Transform_h

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "utils.hpp"
#include "cvplot.h"

using namespace std;
using namespace cv;

void ch03_1_transform() {
    Mat image = imread("res/lenna.png");
    Size s = image.size();
    int w = s.width;
    int h = s.height;
    Mat scaleM = getRotationMatrix2D(Point2f(w/2, h/2), 0, 0.5);
    Mat rotateM = getRotationMatrix2D(Point2f(0, 0), 25, 1);
    Mat scaled, rotated;
    warpAffine(image, scaled, scaleM, s);
    warpAffine(scaled, rotated, rotateM, s);
    
    {
        vector<string> subtitles = { "origin", "scaled(center, 0.5)", "rotated((0, 0), 20)", };
        vector<Mat> images = { image, scaled, rotated };
        ShowImages("Rotate & Scale", subtitles, images, {1, 3});
    }
    
    // Get affine transform matrix from src and dst triangle
    Point2f srcTri[3];
    srcTri[0] = Point2f(0, 0);
    srcTri[1] = Point2f(w, 0);
    srcTri[2] = Point2f(0, h);
    
    Point2f dstTri[3];
    dstTri[0] = Point2f(w/4, h/4);
    dstTri[1] = Point2f(w/2, 0);
    dstTri[2] = Point2f(w/4, h);
    
    Mat transM = getAffineTransform(srcTri, dstTri);
    Mat transed;
    warpAffine(image, transed, transM, s);
    
    vector<Point2f> pts;
    Point2f pt1(w/4, h/4); pts.push_back(pt1);
    Point2f pt2(w/4, h*3/4); pts.push_back(pt2);
    Point2f pt3(w*3/4, h/4); pts.push_back(pt3);
    Point2f pt4(w*3/4, h*3/4); pts.push_back(pt4);
    
    Mat ori(s, CV_8UC3);
    image.copyTo(ori);
    circle(ori, pts[0], 5, Scalar(255, 0, 0), CV_FILLED);
    circle(ori, pts[1], 5, Scalar(0, 255, 0), CV_FILLED);
    circle(ori, pts[2], 5, Scalar(0, 0, 255), CV_FILLED);
    circle(ori, pts[3], 5, Scalar(0, 255, 255), CV_FILLED);
    
    transform(pts, pts, transM);
    
    circle(transed, pts[0], 5, Scalar(255, 0, 0), CV_FILLED);
    circle(transed, pts[1], 5, Scalar(0, 255, 0), CV_FILLED);
    circle(transed, pts[2], 5, Scalar(0, 0, 255), CV_FILLED);
    circle(transed, pts[3], 5, Scalar(0, 255, 255), CV_FILLED);
    
    {
        vector<string> subtitles = { "origin", "transed", };
        vector<Mat> images = { ori, transed };
        ShowImages("Affine Transform", subtitles, images, {1, 2});
    }
    
    // Resize and Pyramid
    Mat resized;
    resize(image, resized, Size(400, 400), CV_INTER_LINEAR);
    
    cvplot::Window::current("Resize and Pyramid").offset({60, 100});
    {
        int width = 400;
        int offset = 0;
        for (int i = 0; i < 4; i++) {
            auto name = "image" + to_string(i);
            cvplot::setWindowTitle(name, "");
            cvplot::moveWindow(name, offset, 0);
            cvplot::resizeWindow(name, width, width);
            auto &view = cvplot::Window::current().view(name);
            view.drawImage(&resized);
            view.finish();
            
            pyrDown(resized, resized);
            offset += width;
            width /= 2;
        }
        
        cvplot::Window::current().view("").flush();
        waitKey();
    }
}

#endif /* L03_1_Transform_h */
