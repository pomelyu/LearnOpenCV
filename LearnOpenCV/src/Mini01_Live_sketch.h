//
//  Mini01_Live_sketch.h
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/8/3.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#ifndef Mini01_Live_sketch_h
#define Mini01_Live_sketch_h

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "edge.hpp"

using namespace std;
using namespace cv;

void sketch(const Mat& src, Mat& dst, bool builtin);

void mini01_live_sketch() {
    VideoCapture cap(0);
    
    if (!cap.isOpened()) {
        cout << "Error: Can not open webcam" << endl;
        return;
    }
    int w = cap.get(CAP_PROP_FRAME_WIDTH);
    int h = cap.get(CAP_PROP_FRAME_HEIGHT);
    int fps = cap.get(CAP_PROP_FPS);
    
    cout << "w: " << w << ", h: " << h << ", fps: " << fps << endl;
    
    string cameraWindow = "WebCamera";
    namedWindow(cameraWindow, CV_WINDOW_AUTOSIZE);
    Mat frame;
    Mat sketched;
    while (true) {
        int key = waitKey(1);
        if (key == 13) break;
        
        cap >> frame;
        resize(frame, frame, Size(400, 300));
        cvtColor(frame, frame, CV_BGR2GRAY);
        
        sketch(frame, sketched, true);
        hconcat(frame, sketched, frame);
        imshow(cameraWindow, frame);
    }
}

void sketch(const Mat& src, Mat& dst, bool builtin) {
    GaussianBlur(src, dst, Size(5, 5), 1.2);
    
    if (builtin) {
        Canny(dst, dst, 70, 180, 5);
    } else {
        cy::Canny(dst, dst, 70, 180, 5);
    }
    threshold(dst, dst, 127, 255, THRESH_BINARY_INV);
}

#endif /* Mini01_Live_sketch_h */
