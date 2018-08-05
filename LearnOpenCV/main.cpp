//
//  main.cpp
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/7/27.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#include <iostream>
#include "src/L02/L02_1_Basic.h"
#include "src/L02/L02_2_Histogram.h"
#include "src/L03/L03_1_Transform.h"
#include "src/L03/L03_2_Mask.h"
#include "src/L03/L03_3_Kernel.h"
#include "src/L03/L03_4_Denoise.h"
#include "src/L03/L03_5_Thresholding.h"
#include "src/L03/L03_6_Dilation_and_Erosion.h"
#include "src/L03/L03_7_Edge_detection.h"
#include "src/L03/L03_8_Perspective_Transform.h"
#include "src/L03/Mini01_Live_sketch.h"
#include "src/L04/L04_1_Contour_Basic.h"

int main(int argc, const char * argv[]) {
    int index = 11;
    switch (index) {
        case  0: ch02_1_basic(); break;
        case  1: ch02_2_histogram(); break;
        case  2: ch03_1_transform(); break;
        case  3: ch03_2_mask(); break;
        case  4: ch03_3_kernel(); break;
        case  5: ch03_4_denoise(); break;
        case  6: ch03_5_thresholding(); break;
        case  7: ch03_6_dilation_and_erosion(); break;
        case  8: ch03_7_edge_detection(); break;
        case  9: ch03_8_perspective(); break;
        case 10: mini01_live_sketch(); break;
        case 11: ch04_1_contour_basic(); break;
        default: break;
    }

    return 0;
}
