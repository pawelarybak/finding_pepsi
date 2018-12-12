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


int main(int argc, char* argv [])
{
    cv::Mat i = cv::imread("/Users/p.rybak/Projects/finding_pepsi/test_data/pepsi1_xsmall.jpeg");
    tresh(i, 100, 200);
    cv::imshow("asdf", i);
    close(i, 2);
    cv::imshow("asdf2", i);
    cv::waitKey(-1);
    return 0;
}
