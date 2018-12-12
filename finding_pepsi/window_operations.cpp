//
//  window_operations.cpp
//  finding_pepsi
//
//  Created by Paweł Rybak on 12/12/2018.
//  Copyright © 2018 Paweł Rybak. All rights reserved.
//

#include "window_operations.hpp"

cv::Vec3b applyConv(cv::Mat_<cv::Vec3b>& I, unsigned int i, unsigned int j, const float* const op)
{
    const cv::Vec3b window[] = {
        I(i - 1, j - 1),
        I(i - 1, j),
        I(i - 1, j + 1),
        I(i, j - 1),
        I(i, j),
        I(i, j + 1),
        I(i + 1, j -1),
        I(i + 1, j),
        I(i + 1, j + 1),
    };
    float res[] = { 0, 0, 0 };
    for (int k = 0; k < 9; ++k) {
        res[0] += op[k] * window[k][0];
        res[1] += op[k] * window[k][1];
        res[2] += op[k] * window[k][2];
    }
    return {
        uchar(std::min(std::max(int(res[0]), 0), 255)),
        uchar(std::min(std::max(int(res[1]), 0), 255)),
        uchar(std::min(std::max(int(res[2]), 0), 255))
    };
}

cv::Mat& conv(cv::Mat& I, const float* const op)
{
    cv::Mat O = I.clone();
    cv::Mat_<cv::Vec3b> _I = I;
    forEach(O, [&](cv::Mat_<cv::Vec3b>& _O, unsigned int i, unsigned int j) {
        _O(i, j) = applyConv(_I, i, j, op);
    }, 1);
    I = O;
    return I;
}

cv::Mat& blur(cv::Mat& I)
{
    const float op[] = { 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0 };
    return conv(I, op);
}

cv::Mat& edgeFilter(cv::Mat& I)
{
    const float op[] = { 0, -1, 0, -1, 4, -1, 0, -1, 0 };
    return conv(I, op);
}


cv::Vec3b applyRank(cv::Mat_<cv::Vec3b>& I, unsigned int i, unsigned int j, std::function<unsigned char* (unsigned char *, unsigned char *)> func)
{
    unsigned char res[] = { 0, 0, 0 };
    unsigned char window1[] = {
        I(i - 1, j - 1)[0],
        I(i - 1, j)[0],
        I(i - 1, j + 1)[0],
        I(i, j - 1)[0],
        I(i, j)[0],
        I(i, j + 1)[0],
        I(i + 1, j - 1)[0],
        I(i + 1, j)[0],
        I(i + 1, j + 1)[0],
    };
    res[0] = *func(window1, window1 + 9);
    unsigned char window2[] = {
        I(i - 1, j - 1)[1],
        I(i - 1, j)[1],
        I(i - 1, j + 1)[1],
        I(i, j - 1)[1],
        I(i, j)[1],
        I(i, j + 1)[1],
        I(i + 1, j - 1)[1],
        I(i + 1, j)[1],
        I(i + 1, j + 1)[1],
    };
    res[1] = *func(window2, window2 + 9);
    unsigned char window3[] = {
        I(i - 1, j - 1)[2],
        I(i - 1, j)[2],
        I(i - 1, j + 1)[2],
        I(i, j - 1)[2],
        I(i, j)[2],
        I(i, j + 1)[2],
        I(i + 1, j - 1)[2],
        I(i + 1, j)[2],
        I(i + 1, j + 1)[2],
    };
    res[2] = *func(window3, window3 + 9);
    return {
        res[0],
        res[1],
        res[2],
    };
}

void rankFilt(cv::Mat& I, std::function<unsigned char* (unsigned char *, unsigned char *)> func)
{
    cv::Mat O = I.clone();
    cv::Mat_<cv::Vec3b> _I = I;
    forEach(O, [&](cv::Mat_<cv::Vec3b>& _O, unsigned int i, unsigned int j) {
        _O(i, j) = applyRank(_I, i, j, func);
    }, 1);
    I = O;
}


void erosion(cv::Mat& I)
{
    rankFilt(I, std::min_element<unsigned char *>);
}

void dilation(cv::Mat& I)
{
    rankFilt(I, std::max_element<unsigned char *>);
}

cv::Mat& open(cv::Mat& I, unsigned int rank)
{
    for (int i = 0; i < rank; ++i) {
        erosion(I);
    }
    for (int i = 0; i < rank; ++i) {
        dilation(I);
    }
    return I;
}

cv::Mat& close(cv::Mat& I, unsigned int rank)
{
    for (int i = 0; i < rank; ++i) {
        dilation(I);
    }
    for (int i = 0; i < rank; ++i) {
        erosion(I);
    }
    return I;
}

cv::Mat& medianFilter(cv::Mat& I)
{
    rankFilt(I, [](unsigned char* first, unsigned char* last) -> unsigned char* {
        std::sort(first, last);
        return (first + 5);
    });
    return I;
}
