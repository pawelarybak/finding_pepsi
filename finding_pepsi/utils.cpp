//
//  utils.cpp
//  finding_pepsi
//
//  Created by Paweł Rybak on 12/12/2018.
//  Copyright © 2018 Paweł Rybak. All rights reserved.
//

#include "utils.hpp"


unsigned char mean(cv::Vec3b v)
{
    return (v[0] + v[1] + v[2]) / 3;
}

void forEach(cv::Mat& I, std::function<void(cv::Mat_<cv::Vec3b>&, unsigned int, unsigned int)> f, int padding)
{
    cv::Mat_<cv::Vec3b> _I = I;
    for (int i = (0 + padding); i < (I.rows - padding); ++i) {
        for (int j = (0 + padding); j < (I.cols - padding); ++j) {
            f(_I, i, j);
        }
    }
    I = _I;
}

cv::Mat& drawRect(cv::Mat& I, Rect r, cv::Vec3b color)
{
    cv::Mat_<cv::Vec3b> _I = I;
    for (int i = r.y_min; i < r.y_max; ++i) {
        _I(i, r.x_min) = color;
        _I(i, r.x_max) = color;
    }
    for (int j = r.x_min; j < r.x_max; ++j) {
        _I(r.y_min, j) = color;
        _I(r.y_max, j) = color;
    }
    return I;
}
