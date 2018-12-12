#include <iostream>
#include <opencv2/opencv.hpp>

#include "point_operations.hpp"


int main(int argc, char* argv [])
{
    cv::Mat i = cv::imread("/Users/p.rybak/Projects/finding_pepsi/test_data/pepsi1_xsmall.jpeg");
    tresh(i, 100, 200);
    cv::imshow("asdf", i);
    cv::waitKey(-1);
    return 0;
}
