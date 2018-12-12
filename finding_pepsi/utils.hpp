//
//  utils.hpp
//  finding_pepsi
//
//  Created by Paweł Rybak on 12/12/2018.
//  Copyright © 2018 Paweł Rybak. All rights reserved.
//

#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

typedef std::pair<unsigned int, unsigned int> Point;

struct Rect {
    unsigned int y_min;
    unsigned int x_min;
    unsigned int y_max;
    unsigned int x_max;
};

unsigned char mean(cv::Vec3b v);
void forEach(cv::Mat& I, std::function<void(cv::Mat_<cv::Vec3b>&, unsigned int, unsigned int)> f, int padding = 0);
cv::Mat& drawRect(cv::Mat& I, Rect r, int grow = 0, cv::Vec3b color = { 0, 255, 0});

#endif /* utils_hpp */
