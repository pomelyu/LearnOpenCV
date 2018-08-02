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
    -  `cv::medianBlur()`, `cv::fastNlMeansDenoisingColored`, `cv::fastNlMeansDenoising`
    - `cv::RNG::unifrom`, `cv::randn`
- 03.5 Thresholding
- 03.6 Dilation & Erosion
- 03.7 Edge detection
- 03.8 Perspective Transform


### Dependences
- opencv@3.4.2
- cvplot

### Todos

- [ ] 03.5 Thresholding
    - [ ] try simple thresholding
    - [ ] try adaptive thresholding by mean kernel, gaussion weights, threshold_otsu
    - [ ] implement  thresholding by mean kernel, gaussion weights
    - [ ] study threshold_otsu method
- [ ] 03.6 Dilation & Erosion
    - [ ] try built-in dilation, erosion, opening and closing function
    - [ ] implement simple dilation, erosion, opening and closing
- [ ] 03.7 Edge detection
    - [ ] try built-in Sobel, Laplacian, Canny Edge detection
    - [ ] implement Canny Edge detection
- [ ] 03.8 Perspective Transform
- [ ] mini1 Live sketch
