//
//  L04_1_Contour_Basic.h
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/5.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#ifndef L04_1_Contour_Basic_h
#define L04_1_Contour_Basic_h

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "utils.hpp"
#include "contour.hpp"

using namespace std;
using namespace cv;

void ch04_1_contour_basic() {
    Mat image = imread("res/shapes_inv.png");
    Mat edges;
    cvtColor(image, edges, CV_BGR2GRAY);
    Canny(edges, edges, 60, 120);
    Mat kernel = Mat::ones(3, 3, CV_8U);
    dilate(edges, edges, kernel);
    
    vector<string> subtitles = { "image" };
    vector<Mat> images = { image };
    
    // Contour Retrival Mode
    // - CV_RETR_EXTERNAL: Extract only outer contours
    // - CV_RETR_LIST
    // - CV_RETR_CCOMP
    // - CV_RETR_TREE
    // * hierarchy structure: [Next, Previous, FirstChild, Parent] *
    //
    // Contour Approximation Method
    // - CV_CHAIN_APPROX_NONE
    // - CV_CHAIN_APPROX_SIMPLE
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    {
        Mat edges_copy, image_copy;
        edges.copyTo(edges_copy);
        image.copyTo(image_copy);
        contours.clear(); hierarchy.clear();
        findContours(edges_copy, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        drawContours(image_copy, contours, -1, Scalar(0, 255, 0), 3);
        subtitles.push_back("outer contours");
        images.push_back(image_copy);
    }

    {
        Mat edges_copy, image_copy;
        edges.copyTo(edges_copy);
        image.copyTo(image_copy);
        contours.clear(); hierarchy.clear();
        findContours(edges_copy, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
        drawContours(image_copy, contours, -1, Scalar(0, 255, 0), 3);
        subtitles.push_back("all contours");
        images.push_back(image_copy);
    }

    {
        Mat edges_copy, image_copy;
        edges.copyTo(edges_copy);
        image.copyTo(image_copy);
        contours.clear(); hierarchy.clear();
        findContours(edges_copy, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
        drawContours(image_copy, contours, 0, Scalar(255, 0, 0), 3, 8, hierarchy, 0);
        drawContours(image_copy, contours, 4, Scalar(0, 255, 0), 3, 8, hierarchy, 0);
        drawContours(image_copy, contours, 6, Scalar(0, 0, 255), 3, 8, hierarchy, 0);
        drawContours(image_copy, contours, 12, Scalar(0, 0, 0), 3, 8, hierarchy, 0);
        subtitles.push_back("contours hierrac");
        images.push_back(image_copy);
    }

    ShowImages("Extract Contours", subtitles, images, {2, 2}, 400);

    {
        Mat image_copy;
        cvtColor(image, image_copy, CV_BGR2GRAY);
        contours.clear(); hierarchy.clear();
        cy::findContours(edges, contours, hierarchy);
        
        for (int i = 1; i < contours.size(); i ++) {
            cy::drawContours(image_copy, contours, i);
            cout << "index: " << i << " " << hierarchy[i] << endl;
        }
        subtitles = {"my contours" };
        images = {image_copy};
    }
    
    ShowImages("My Contours", subtitles, images, {1, 1}, 800);
}

#endif /* L04_1_Contour_Basic_h */
