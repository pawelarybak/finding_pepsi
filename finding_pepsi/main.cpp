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
    close(O, 3);
//    open(O);
//    medianFilter(O);
    return O;
}

void redSegment(cv::Mat& mask, std::vector<cv::Mat>& dst)
{
    std::vector<cv::Mat> shapes;
    getSegments(mask, shapes);
//    int ctr = 0;
    for (cv::Mat& shape : shapes) {
        const double _malinowska = malinowska(shape);
        const double _M7 = M7(shape);
        const double _M3 = M3(shape);
//        cv::imshow(std::to_string(ctr), shape);
//        std::cout << ctr << ": " << _malinowska << " " << M3(shape) << " " << M7(shape) << std::endl;
//        ctr += 1;
        if (_malinowska > -0.08 && _malinowska < -0.022 && _M7 < 1.0 && _M3 > 5e+14) {
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
//    close(O);
//    medianFilter(O);
    return O;
}

void blueSegment(cv::Mat& mask, std::vector<cv::Mat>& dst)
{
    std::vector<cv::Mat> shapes;
    getSegments(mask, shapes);
//    int ctr = 0;
    for (cv::Mat& shape : shapes) {
        const double _malinowska = malinowska(shape);
        const double _M7 = M7(shape);
        close(shape);
//        cv::imshow(std::to_string(ctr), shape);
//        std::cout << ctr << ": " << _malinowska << " " << M3(shape) << " " << M7(shape) << std::endl;
//        ctr += 1;
        if (_malinowska > 0.2 && _malinowska < 0.4 && _M7 < 3.0) {
            dst.push_back(shape);
        }
    }
}

void mergeSegments(std::vector<cv::Mat>& redSegments, std::vector<cv::Mat>& blueSegments, std::vector<cv::Mat>& dst)
{
    for (cv::Mat& redShape : redSegments) {
        for (cv::Mat& blueShape : blueSegments) {
            const double dist = rDist(redShape, blueShape);
//            std::cout << dist << std::endl;
            if (dist < 0.7 && dist > 0.5) {
                dst.push_back(redShape + blueShape);
            }
        }
    }
}

int main(int argc, char* argv [])
{
    cv::Mat originalImg = cv::imread("/Users/p.rybak/Projects/finding_pepsi/test_data/pepsi3_xsmall.jpeg");
    
    std::vector<cv::Mat> redElements;
    cv::Mat rMsk = redMask(originalImg);
//    cv::imshow("sadf", rMsk);
    redSegment(rMsk, redElements);

//    int ctr = 0;
//    std::cout << redElements.size() << std::endl;
//    for (cv::Mat& sh : redElements) {
//        cv::imshow(std::to_string(ctr), sh);
//        ctr += 1;
//    }
//
    std::vector<cv::Mat> blueElements;
    cv::Mat bMsk = blueMask(originalImg);
//    cv::imshow("asd", bMsk);
    blueSegment(bMsk, blueElements);

//    int ctr = 0;
//    std::cout << blueElements.size() << std::endl;
//    for (cv::Mat& sh : blueElements) {
//        cv::imshow(std::to_string(ctr), sh);
//        ctr += 1;
//    }

    std::vector<cv::Mat> foundLogos;
    mergeSegments(redElements, blueElements, foundLogos);

    int ctr = 0;
    for (cv::Mat& logo : foundLogos) {
        drawRect(originalImg, mbb(logo), 1);
        cv::imshow(std::to_string(ctr), logo);
        ctr += 1;
    }

    cv::imshow("result", originalImg);
    
    cv::waitKey(-1);
    return 0;
}
