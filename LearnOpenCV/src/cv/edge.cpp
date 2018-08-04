//
//  edge.cpp
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/3.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "edge.hpp"

using namespace std;
using namespace cv;

#define TAN22_5 0.414
#define TAN67_5 2.414

void direction(const Mat& Gx, const Mat& Gy, Mat& dst);
void scaleToUChar(const Mat& src, Mat& dst, float max_rato);

void cy::Canny(const cv::Mat& src, cv::Mat& dst, const double threshold1, const double threshold2, const int ksize ) {
    // Step1. Remove noise (apply gaussian)
    Mat blurred;
    src.convertTo(blurred, CV_64F);
    GaussianBlur(blurred, blurred, Size(5, 5), 1.5);
    
    
    // Step2. Calculate gradient (apply sobel operator)
    Mat Gx, Gy, G, D;
    Sobel(blurred, Gx, -1, 1, 0, ksize);
    Sobel(blurred, Gy, -1, 0, 1, ksize);
    direction(Gx, Gy, D);
    blurred.release();
    
    Mat GxF, GyF;
    pow(Gx, 2, GxF);
    pow(Gy, 2, GyF);
    add(GxF, GyF, G);
    pow(G, 0.5, G);
    scaleToUChar(G, G, 0.2);
    Gx.release();
    Gy.release();
    GxF.release();
    GyF.release();
    
    
    // Step3. Non-maximum supression
    // For each pixel find two neighbors (in the positive and negative gradient directions,
    // supposing that each neighbor occupies the angle of π/4 , and 0i s the direction straight to the right).
    // If the magnitude of the current pixel is greater than the magnitudes of the neighbors, nothing changes,
    // otherwise, the magnitude of the current pixel is set to zero.
    
    // set the gradient direction in the border of D to be ZERO,
    // to prevent out of boundary
    D.row(0) = cy::DIRECTION::ZERO;
    D.col(0) = cy::DIRECTION::ZERO;
    D.row(D.rows-1) = cy::DIRECTION::ZERO;
    D.col(D.cols-1) = cy::DIRECTION::ZERO;
    
    G.forEach<uchar>([&D, &G](uchar &pixel, const int* position) {
        int x = position[1];
        int y = position[0];

        uchar v1, v2;
        uchar dir = D.at<uchar>(Point(x, y));
        switch (dir) {
            case cy::DIRECTION::VERTICAL:
                v1 = G.at<uchar>(Point(x, y+1));
                v2 = G.at<uchar>(Point(x, y-1));
                break;
            case cy::DIRECTION::HORIZON:
                v1 = G.at<uchar>(Point(x+1, y));
                v2 = G.at<uchar>(Point(x-1, y));
                break;
            case cy::DIRECTION::SLASH:
                v1 = G.at<uchar>(Point(x+1, y+1));
                v2 = G.at<uchar>(Point(x-1, y-1));
                break;
            case cy::DIRECTION::BACK_SLASH:
                v1 = G.at<uchar>(Point(x+1, y-1));
                v2 = G.at<uchar>(Point(x-1, y+1));
                break;
            default:
                v1 = 255;
                v2 = 255;
                break;
        }
        if (pixel <= v1 || pixel <= v2) {
            pixel = 0;
        }
    });
    

    // Step4. Double thresholding
    // threshold to two matrix
    // upper: true edge
    // lower: true edge + week edge
    Mat upper, lower;
    threshold(G, upper, threshold2, 255, THRESH_BINARY);
    threshold(G, lower, threshold1, 255, THRESH_BINARY);
    G.release();
    
    // Step5. Edge tracking by hyperesis
    // For each pixel p in upper, if is edge, check whether its neighbor p1, p2(in gradient direction) is in lower
    // if true check the neighbors of p1 and p2. record the visited pixel in visited
    Mat visited = Mat::zeros(upper.size(), CV_8U);
    for (int y = 0; y < upper.rows; y++) {
        for (int x = 0; x < upper.cols; x++) {
            // if pixel not in upper or had visited, skip
            if (upper.at<uchar>(Point(x, y)) == 0 || visited.at<uchar>(Point(x, y)) > 0) continue;
            
            queue<Point_<int>> q;
            q.push(Point(x, y));
            while(!q.empty()) {
                Point_<int> p = q.front(); q.pop();
                
                Point_<int> p1, p2;
                visited.at<uchar>(p) = 255;
                upper.at<uchar>(p) = 255;
                uchar dir = D.at<char>(p);
                switch (dir) {
                    case cy::DIRECTION::VERTICAL:
                        p1 = Point(p.x+1, p.y);
                        p2 = Point(p.x-1, p.y);
                        break;
                    case cy::DIRECTION::HORIZON:
                        p1 = Point(p.x, p.y+1);
                        p2 = Point(p.x, p.y-1);
                        break;
                    case cy::DIRECTION::SLASH:
                        p1 = Point(p.x+1, p.y-1);
                        p2 = Point(p.x-1, p.y+1);
                        break;
                    case cy::DIRECTION::BACK_SLASH:
                        p1 = Point(p.x+1, p.y+1);
                        p2 = Point(p.x-1, p.y-1);
                        break;
                    default:
                        p1 = p;
                        p2 = p;
                        break;
                }
                
                if (lower.at<uchar>(p1) > 0 && visited.at<uchar>(p1) == 0) q.push(p1);
                if (lower.at<uchar>(p2) > 0 && visited.at<uchar>(p2) == 0) q.push(p2);
            }
        }
    }
    
    // Final. assign upper to dst
    dst = upper;
}

void direction(const Mat& Gx, const Mat& Gy, Mat& dst) {
    Mat theta;
    float eta = 10e-4;
    add(Gx, eta, Gx);
    divide(Gy, Gx, theta, 1, CV_64F);
    theta.forEach<double>([](double &pixel, const int* position) {
        // tan(22.5) = 0.414, tand(67.5) = 2.414
        if (pixel < TAN67_5 && pixel >= TAN22_5) {
            pixel = cy::DIRECTION::SLASH;
        } else if (pixel < TAN22_5 && pixel >= -TAN22_5) {
            pixel = cy::DIRECTION::HORIZON;
        } else if (pixel < -TAN22_5 && pixel >= -TAN67_5) {
            pixel = cy::DIRECTION::BACK_SLASH;
        } else {
            pixel = cy::DIRECTION::VERTICAL;
        }
    });
    theta.convertTo(dst, CV_8U);
    theta.release();
}

void scaleToUChar(const Mat& src, Mat& dst, float max_rato) {
    src.convertTo(dst, CV_32F);
    double maxValue;
    minMaxLoc(dst, 0, &maxValue);
    
    int bins = 100;
    int histSize = bins;
    float range[] = { 0, float(maxValue) };
    const float* ranges[] = { range };
    Mat hist;
    calcHist(&dst, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);

    int threshold = int(sum(hist.rowRange(5, bins-1))[0] * max_rato);
    int sum = 0;
    int i = bins-1;
    while (i >= 0) {
        sum += hist.at<float>(i);
        if (sum > threshold) break;
        i--;
    }
    float scaleRatio = (255 * bins) / ( i * maxValue);
    convertScaleAbs(dst, dst, scaleRatio);
}
