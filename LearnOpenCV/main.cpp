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

int main(int argc, const char * argv[]) {
    int index = 4;
    switch (index) {
        case 0: ch02_1_basic(); break;
        case 1: ch02_2_histogram(); break;
        case 2: ch03_1_transform(); break;
        case 3: ch03_2_mask(); break;
        case 4: ch03_3_kernel(); break;
        default: break;
    }

    return 0;
}
