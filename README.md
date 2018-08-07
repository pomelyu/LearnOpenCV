### Description

### OpenCV functions
- 02.1 Basic
    - `cv::imread`, `cv::imwrite`
    - `cv::Mat::channels`, `cv::Mat::size`, `cv::Mat::type`
    - `cv::cvtColor`
    - `cv::split`, `cv::merge`
- 02.2 Histogram
    - `cv::calcHist`
- 03.1 Transform
    - `cv::warpAffine`, `cv::transform`, `cv::resize`, `cv::pyrDown`, `cv::pyrUp`
    - `cv::getRotationMatrix2D`, `cv::getAffineTransform`
- 03.2 Mask
    - `cv::Mat::rowRange`, `cv::Mat::colRange`
    - `cv::bitwise_and`, `cv::bitwise_or`, `cv::bitwise_xor`,  `cv::bitwise_not`
- 03.3 Kernel
    - `cv::filter2D`
    - `cv::GaussianBlur`, `cv::bilateralFilter`, `cv::boxFilter`, `cv::blur`
- 03.4 Denoise
    - `cv::medianBlur()`, `cv::fastNlMeansDenoisingColored`, `cv::fastNlMeansDenoising`
    - `cv::RNG::unifrom`, `cv::randn`
- 03.5 Thresholding
    - `cv::threshold`, `cv::adaptiveThreshold`
- 03.6 Dilation & Erosion
    - `cv::dilate`, `cv::erode`, `cv::morphologyEx`
- 03.7 Edge detection
    - `cv::Sobel`, `cv::Laplacian`, `cv::Canny`
- 03.8 Perspective Transform
    - `cv::getPerspectiveTransform`, `cv::warpPerspective`
- 04.1 Contours Basic
    - `cv::findContours`, `cv::drawContours`



### Dependences
- opencv@3.4.2
- cvplot

### Todos

- [x] 03.5 Thresholding
    - [x] try simple thresholding
    - [x] try adaptive thresholding by mean kernel, gaussion weights
    - [x] implement thresholding by mean kernel, gaussion weights
    - [x] try and study threshold_otsu method
- [x] 03.6 Dilation & Erosion
    - [x] try built-in dilation, erosion, opening and closing function
    - [x] implement simple dilation, erosion, opening and closing
- [x] 03.7 Edge detection
    - [x] try built-in Sobel, Laplacian, Canny Edge detection
    - [x] implement Canny Edge detector
- [x] 03.8 Perspective Transform
- [x] mini1 Live sketch
- [x] 04.1 Contours Basic
    - [x] try built-in findContours, drawContours
    - [x] implement findContours algorithm
