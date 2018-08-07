//
//  contour.hpp
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/7.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#ifndef contour_hpp
#define contour_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace cy {
    const int MIN_CONTOUR_POINT = 10;
    
    enum ContourType {
        OUTER = 0,
        HOLE  = 1,
    };
    
    enum ARROW: int {
        POSITIVE_X =  1,
        NEGATIVE_X = -1,
        POSITIVE_Y =  2,
        NEGATIVE_Y = -2,
    };
    
    void findContours(const Mat& src, vector<vector<Point> >& contours, vector<Vec4i>& hierarchy);
    void drawContours(Mat& src, vector<vector<Point> > contours, int index);
}

#endif /* contour_hpp */
