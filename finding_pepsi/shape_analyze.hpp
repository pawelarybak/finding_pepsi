//
//  shape_analyze.hpp
//  finding_pepsi
//
//  Created by Paweł Rybak on 12/12/2018.
//  Copyright © 2018 Paweł Rybak. All rights reserved.
//

#ifndef shape_analyze_hpp
#define shape_analyze_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "utils.hpp"
#include "window_operations.hpp"

int field(cv::Mat& I);
int circ(cv::Mat& I);
double malinowska(cv::Mat& I);
Rect mbb(cv::Mat& I);
double dist(Point lhs, Point rhs);
double rDist(cv::Mat& I, cv::Mat& O);

#endif /* shape_analyze_hpp */
