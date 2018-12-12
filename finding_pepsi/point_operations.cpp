//
//  point_operations.cpp
//  finding_pepsi
//
//  Created by Paweł Rybak on 12/12/2018.
//  Copyright © 2018 Paweł Rybak. All rights reserved.
//

#include "point_operations.hpp"

void tresh(cv::Mat& I, unsigned char min_t, unsigned char max_t)
{
    forEach(I, [&](cv::Mat_<cv::Vec3b>& _I, unsigned int i, unsigned int j) {
        unsigned char m = mean(_I(i, j));
        if (m >= min_t && m <= max_t) {
            _I(i, j) = { 255, 255, 255 };
        } else {
            _I(i, j) = { 0, 0, 0 };
        }
    });
}


void filterColor(cv::Mat& I, ColorChannel ch)
{
    forEach(I, [&](cv::Mat_<cv::Vec3b>& _I, unsigned int i, unsigned int j) {
        unsigned char newVal = std::max(_I(i, j)[int(ch)] - mean(_I(i, j)), 0);
        _I(i, j) = { newVal, newVal, newVal };
    });
}

void treshHLS(cv::Mat& I, cv::Vec3b min_hls, cv::Vec3b max_hls)
{
    cv::Mat hls;
    cv::cvtColor(I, hls, CV_BGR2HLS);
    
    
    forEach(I, [&](cv::Mat_<cv::Vec3b>& _I, unsigned int i, unsigned int j) {
        if (_I(i, j)[0] >= min_hls[0] && _I(i, j)[0] <= max_hls[0]
            && _I(i, j)[1] >= min_hls[1] && _I(i, j)[1] <= max_hls[1]
            && _I(i, j)[2] >= min_hls[2] && _I(i, j)[2] <= max_hls[2]) {
            _I(i, j) = { 255, 255, 255 };
        } else {
            _I(i, j) = { 0, 0, 0 };
        }
    });
}
