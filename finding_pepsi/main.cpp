//
//  main.cpp
//  finding_pepsi
//
//  Created by Paweł Rybak on 12/12/2018.
//  Copyright © 2018 Paweł Rybak. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#include "point_operations.hpp"
#include "window_operations.hpp"
#include "segmentation.hpp"
#include "shape_analyze.hpp"

cv::Mat redMask(cv::Mat& I)
{
    cv::Mat O = I.clone();
    filterColor(O, ColorChannel::RED);
    tresh(O, 40);
    open(O, 4);
    return O;
}

void redSegment(cv::Mat& mask, std::vector<cv::Mat>& dst)
{
    std::vector<cv::Mat> shapes;
    getSegments(mask, shapes);
    for (cv::Mat& shape : shapes) {
        close(shape, 3);
        const double _malinowska = malinowska(shape);
        const double _M7 = M7(shape);
        if (_malinowska > -0.08 && _malinowska < 0 && _M7 < 25.0) {
            dst.push_back(shape);
        }
    }
}

cv::Mat blueMask(cv::Mat& I)
{
    cv::Mat O = I.clone();
    filterColor(O, ColorChannel::BLUE);
    tresh(O, 10);
    open(O);
    return O;
}

void blueSegment(cv::Mat& mask, std::vector<cv::Mat>& dst)
{
    std::vector<cv::Mat> shapes;
    getSegments(mask, shapes);
    for (cv::Mat& shape : shapes) {
        close(shape);
        const double _malinowska = malinowska(shape);
        if (_malinowska > 0.2 && _malinowska < 0.6) {
            dst.push_back(shape);
        }
    }
}

void mergeSegments(std::vector<cv::Mat>& redSegments, std::vector<cv::Mat>& blueSegments, std::vector<cv::Mat>& dst)
{
    for (cv::Mat& redShape : redSegments) {
        for (cv::Mat& blueShape : blueSegments) {
            const double dist = rDist(redShape, blueShape);
            if (dist < 0.8 && dist > 0.5) {
                dst.push_back(redShape + blueShape);
            }
        }
    }
}

int main(int argc, char* argv [])
{
    std::string filePath = "";
    // In code override file path
//    filePath = "/Users/p.rybak/Projects/finding_pepsi/test_data/pepsi2.jpeg";
    if (filePath.length() == 0) {
        if (argc < 2) {
            std::cerr << "File path is required" << std::endl;
            return -1;
        }
        filePath = argv[1];
    }
    cv::Mat originalImg = cv::imread(filePath);
    
    std::vector<cv::Mat> redElements;
    cv::Mat rMsk = redMask(originalImg);
    redSegment(rMsk, redElements);

    std::vector<cv::Mat> blueElements;
    cv::Mat bMsk = blueMask(originalImg);
    blueSegment(bMsk, blueElements);

    std::vector<cv::Mat> foundLogos;
    mergeSegments(redElements, blueElements, foundLogos);

    for (cv::Mat& logo : foundLogos) {
        drawRect(originalImg, mbb(logo), 1);
    }

    cv::imshow("result", originalImg);
    
    cv::waitKey(-1);
    return 0;
}
