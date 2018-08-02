//
//  morphology.hpp
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/2.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#ifndef morphology_hpp
#define morphology_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

namespace cy {
    void dilate(const Mat& src, Mat& dst, const Mat& kernel);
    void erode(const Mat&src, Mat& dst, const Mat& kernel);
    void opening(const Mat&src, Mat&dst, const Mat& kernel);
    void closing(const Mat&src, Mat&dst, const Mat& kernel);
}

#endif /* morphology_hpp */
