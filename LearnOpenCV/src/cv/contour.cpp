//
//  contour.cpp
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/7.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#include "contour.hpp"
#include "utils.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void followContour(Mat& src, Point startPt, int NBD, cy::ContourType type, vector<Point>& contour);
void assignContourHierarchy(int NBD, cy::ContourType newType, int RNBD, cy::ContourType RType, vector<Vec4i>& hierarchy);
void nextPoint(Point& pt, bool isOne, cy::ARROW& direction);

void cy::findContours(const Mat& src, vector<vector<Point> >& contours, vector<Vec4i>& hierarchy) {
    assert(src.type() == CV_8U);
    
    Mat padded = Mat::zeros(src.rows + 2, src.cols + 2, CV_8U);
    src.copyTo(padded.colRange(1, padded.cols-1).rowRange(1, padded.rows-1));
    threshold(padded, padded, 127, 1, THRESH_BINARY);
    padded.convertTo(padded, CV_8S);
    
    vector<cy::ContourType> contoursType;
    // Frame is the outline of the image
    vector<Point> frameContour;
    frameContour.push_back(Point(1, 1));
    frameContour.push_back(Point(padded.cols-2, 1));
    frameContour.push_back(Point(padded.cols-2, padded.rows-2));
    frameContour.push_back(Point(1, padded.rows-2));

    // [NEXT, PREV, FIRST_CHILD, PARENT]
    hierarchy.push_back(Vec4i(-1, -1, -1, -1));
    contours.push_back(frameContour);
    contoursType.push_back(cy::ContourType::HOLE);
    
    int NBD = 2;
    int LNBD = 1;
    for (int y = 1; y < padded.rows - 1; y++) {
        for (int x = 1; x < padded.cols - 1; x++) {
            if (NBD > numeric_limits<schar>::max()) {
                cerr << "Error: too many contour" << endl;
                return;
            }
            if (abs(padded.at<schar>(Point(x, y))) > 1) {
                LNBD = abs(padded.at<schar>(Point(x, y)));
            }
            
            cy::ContourType type;
            if ((padded.at<schar>(Point(x-1, y)) == 0 && padded.at<schar>(Point(x, y)) == 1)) {
                type = cy::ContourType::OUTER;
            } else if ((padded.at<schar>(Point(x, y)) >= 1 && padded.at<schar>(Point(x+1, y)) == 0)) {
                type = cy::ContourType::HOLE;
            } else {
                continue;
            }
            
            vector<Point> contour;
            followContour(padded, Point(x, y), NBD, type, contour);
//          cout << "NBD: " << NBD << ", LNBD: " << LNBD << ", type: "<< newContourType << endl;
            contours.push_back(contour);
            contoursType.push_back(type);
            
            assignContourHierarchy(NBD, type, LNBD, contoursType[LNBD-1], hierarchy);
            
            LNBD = NBD;
            NBD++;
        }
    }
}

void cy::drawContours(Mat& src, vector<vector<Point> > contours, int index) {
    assert(index >= 0);
    assert(index < contours.size());
    // FIXME
    assert(src.type() == CV_8U);
    
    vector<Point> contour = contours[index];
    for (int i = 0; i < contour.size(); i++) {
        // FIXME
        src.at<uchar>(contour[i] - Point(1, 1)) = 127;
    }
}

void followContour(Mat& src, Point startPt, int NBD, cy::ContourType type, vector<Point>& contour) {
    Point pt(startPt);
    cy::ARROW direction;
    if (type == cy::ContourType::OUTER) {
        direction = cy::ARROW::POSITIVE_Y;
    } else {
        direction = cy::ARROW::NEGATIVE_X;
    }
    
    do {
        bool isOne = (src.at<schar>(pt) != 0);
        if (isOne) {
            if ((direction == cy::ARROW::POSITIVE_Y && src.at<schar>(pt + Point(1, 0)) == 0) ||
                (direction == cy::ARROW::NEGATIVE_X && src.at<schar>(pt + Point(1, 0)) == 0)) {
                src.at<schar>(pt) = -NBD;
            } else if (src.at<schar>(pt) == 1) {
                src.at<schar>(pt) = NBD;
            }
            contour.push_back(pt);
        }

        nextPoint(pt, isOne, direction);
        
    } while (pt != startPt);
}

void assignContourHierarchy(int NBD, cy::ContourType newType, int LNBD, cy::ContourType LType, vector<Vec4i>& hierarchy) {
    Vec4i hierarchyNode(-1, -1, -1, -1);
    Vec4i LHierarchyNode = hierarchy[LNBD-1];
    
    int LIndex = LNBD - 1;
    int index = NBD - 1;
    // Same type => NBD, LNBD has same parent
    if ((LType == cy::ContourType::OUTER && newType == cy::ContourType::OUTER) ||
        (LType == cy::ContourType::HOLE && newType == cy::ContourType::HOLE)) {
        hierarchyNode[3] = LHierarchyNode[3];
        
        int nodeIdx = LIndex;
        while(hierarchy[nodeIdx][0] != -1) {
            nodeIdx = hierarchy[nodeIdx][0];
        }
        hierarchy[nodeIdx][0] = index;
        hierarchyNode[1] = nodeIdx;
        
    }
    // Different type => LNBD is parent
    else {
        hierarchyNode[3] = LIndex;
        if (LHierarchyNode[2] == -1) {
            LHierarchyNode[2] = index;
        } else {
            int nodeIdx = LHierarchyNode[2];
            while(hierarchy[nodeIdx][0] != -1) {
                nodeIdx = hierarchy[nodeIdx][0];
            }
            hierarchy[nodeIdx][0] = index;
            hierarchyNode[1] = nodeIdx;
        }
    }
    hierarchy.push_back(hierarchyNode);
}

void nextPoint(Point& pt, bool isOne, cy::ARROW& direction) {
    Point d;
    direction = (isOne) ? direction : (cy::ARROW)-direction;
    switch(direction) {
        case cy::ARROW::POSITIVE_X: d = Point( 0, -1); direction = cy::ARROW::NEGATIVE_Y; break;
        case cy::ARROW::NEGATIVE_X: d = Point( 0,  1); direction = cy::ARROW::POSITIVE_Y; break;
        case cy::ARROW::POSITIVE_Y: d = Point( 1,  0); direction = cy::ARROW::POSITIVE_X; break;
        case cy::ARROW::NEGATIVE_Y: d = Point(-1,  0); direction = cy::ARROW::NEGATIVE_X; break;
        default: break;
    }
    pt += d;
}
