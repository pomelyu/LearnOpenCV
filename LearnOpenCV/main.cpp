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

int main(int argc, const char * argv[]) {
    int index = 1;
    switch (index) {
        case 0: ch02_1_basic(); break;
        case 1: ch02_2_histogram(); break;
        default: break;
    }

    return 0;
}
