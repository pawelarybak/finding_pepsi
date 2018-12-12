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

cv::Mat& drawRect(cv::Mat& I, Rect r, int grow, cv::Vec3b color)
{
    cv::Mat_<cv::Vec3b> _I = I;
    for (int i = std::max(r.x_min - grow, 0U); i < std::min(r.x_max + grow, (unsigned int)I.cols); ++i) {
        _I(i, std::max(r.y_min - grow, 0U)) = color;
        _I(i, std::min(r.y_max + grow, (unsigned int)I.rows)) = color;
    }
    for (int j = std::max(r.y_min - grow, 0U); j < std::min(r.y_max + grow, (unsigned int)I.rows); ++j) {
        _I(std::max(r.x_min - grow, 0U), j) = color;
        _I(std::min(r.x_max + grow, (unsigned int)I.cols), j) = color;
    }
    return I;
}
