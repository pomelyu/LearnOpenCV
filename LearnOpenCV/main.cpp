//
//  main.cpp
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/7/27.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#include <iostream>
#include "src/L02_1_Basic.cpp"
#include "src/L02_2_Histogram.cpp"
#include "src/L03_1_Transform.cpp"
#include "src/L03_2_Mask.h"

int main(int argc, const char * argv[]) {
    int index = 3;
    switch (index) {
        case 0: ch02_1_basic(); break;
        case 1: ch02_2_histogram(); break;
        case 2: ch03_1_transform(); break;
        case 3: ch03_2_mask(); break;
        default: break;
    }

    return 0;
}
