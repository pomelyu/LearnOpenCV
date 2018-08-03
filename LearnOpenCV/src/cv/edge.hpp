//
//  edge.hpp
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/3.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#ifndef edge_hpp
#define edge_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

namespace cy {
    enum DIRECTION {
        VERTICAL   = 0,
        HORIZON    = 1,
        SLASH      = 2,
        BACK_SLASH = 3,
        ZERO = 4,
    };
    
    void Canny(const cv::Mat& src, cv::Mat& dst, const double threshold1, const double threshold2, const int ksize );
}

#endif /* edge_hpp */
