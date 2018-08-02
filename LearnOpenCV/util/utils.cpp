//
//  utils.cpp
//  LearnOpenCV
//
//  Created by Chien Chin-yu on 2018/7/29.
//  Copyright © 2018 Chien Chin-yu. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <opencv2/opencv.hpp>
#include "cvplot.h"

#include "utils.hpp"

using namespace std;
using namespace cv;

// From https://stackoverflow.com/a/43215654
void MatType( Mat inputMat )
{
    int inttype = inputMat.type();
    
    string r, a;
    uchar depth = inttype & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (inttype >> CV_CN_SHIFT);
    switch ( depth ) {
        case CV_8U:  r = "8U";   a = "Mat.at<uchar>(y,x)"; break;
        case CV_8S:  r = "8S";   a = "Mat.at<schar>(y,x)"; break;
        case CV_16U: r = "16U";  a = "Mat.at<ushort>(y,x)"; break;
        case CV_16S: r = "16S";  a = "Mat.at<short>(y,x)"; break;
        case CV_32S: r = "32S";  a = "Mat.at<int>(y,x)"; break;
        case CV_32F: r = "32F";  a = "Mat.at<float>(y,x)"; break;
        case CV_64F: r = "64F";  a = "Mat.at<double>(y,x)"; break;
        default:     r = "User"; a = "Mat.at<UKNOWN>(y,x)"; break;
    }
    r += "C";
    r += (chans+'0');
    cout << "Mat is of type " << r << " and should be accessed with " << a << endl;
    
}


void ShowImages(string title, vector<string> subtitles, vector<Mat> images, pair<int, int> grid, int size, bool rowFirst){
    cvplot::Window::current(title).offset({60, 100});
    
    assert(subtitles.size() == images.size());
    assert(subtitles.size() <= grid.first * grid.second);
    
    int index = 0;
    int i_max = rowFirst ? grid.first : grid.second;
    int j_max = rowFirst ? grid.second : grid.first;
    for (int i = 0; i < i_max; i++) {
        for (int j = 0; j < j_max & index < subtitles.size(); j++) {
            auto name = "image" + to_string(index);
            cvplot::setWindowTitle(name, subtitles[index]);
            if (rowFirst) {
                cvplot::moveWindow(name, j * size, i * size);
            } else {
                cvplot::moveWindow(name, i * size, j * size);
            }
            cvplot::resizeWindow(name, size, size);
            auto &view = cvplot::Window::current().view(name);
            
            Mat image = images[index];
            if (image.channels() == 1) {
                Mat c = Mat(image.size(), CV_8U);
                cvtColor(image, c, CV_GRAY2BGR);
                image = c;
            }
            view.drawImage(&image);
            view.finish();
            index++;
        }
    }
    cvplot::Window::current().view("").flush();
    waitKey();
}
