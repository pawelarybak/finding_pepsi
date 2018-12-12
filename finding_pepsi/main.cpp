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

int main(int argc, char* argv [])
{
    cv::Mat i = cv::imread("/Users/p.rybak/Projects/finding_pepsi/test_data/pepsi2w_xsmall.jpeg");
    tresh(i, 250);
    medianFilter(i);
    cv::imshow("asdf", i);
    
    std::vector<cv::Mat> shapes;
    int ctr = 0;
    getSegments(i, shapes);
    
    for (cv::Mat& sh : shapes) {
        cv::imshow(std::to_string(ctr), sh);
        ctr += 1;
    }
    
    cv::waitKey(-1);
    return 0;
}
