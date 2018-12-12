//
//  segmentation.hpp
//  finding_pepsi
//
//  Created by Paweł Rybak on 12/12/2018.
//  Copyright © 2018 Paweł Rybak. All rights reserved.
//

#ifndef segmentation_hpp
#define segmentation_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <deque>

#include "utils.hpp"
#include "point_operations.hpp"

void getSegments(cv::Mat& I, std::vector<cv::Mat>& dst);

#endif /* segmentation_hpp */
