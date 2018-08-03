//
//  main.cpp
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/7/27.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#include <iostream>
#include "src/L02_1_Basic.h"
#include "src/L02_2_Histogram.h"
#include "src/L03_1_Transform.h"
#include "src/L03_2_Mask.h"
#include "src/L03_3_Kernel.h"
#include "src/L03_4_Denoise.h"
#include "src/L03_5_Thresholding.h"
#include "src/L03_6_Dilation_and_Erosion.h"
#include "src/L03_7_Edge_detection.h"
#include "src/L03_8_Perspective_Transform.h"
#include "src/Mini01_Live_sketch.h"

int main(int argc, const char * argv[]) {
    int index = 9;
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
        default: break;
    }

    return 0;
}
