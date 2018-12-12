//
//  window_operations.hpp
//  finding_pepsi
//
//  Created by Paweł Rybak on 12/12/2018.
//  Copyright © 2018 Paweł Rybak. All rights reserved.
//

#ifndef window_operations_hpp
#define window_operations_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "utils.hpp"

cv::Mat& blur(cv::Mat& I);
cv::Mat& edgeFilter(cv::Mat& I);
cv::Mat& open(cv::Mat& I, unsigned int rank = 1);
cv::Mat& close(cv::Mat& I, unsigned int rank = 1);
cv::Mat& medianFilter(cv::Mat& I);


#endif /* window_operations_hpp */
