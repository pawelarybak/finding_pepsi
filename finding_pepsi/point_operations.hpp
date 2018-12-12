//
//  point_operations.hpp
//  finding_pepsi
//
//  Created by Paweł Rybak on 12/12/2018.
//  Copyright © 2018 Paweł Rybak. All rights reserved.
//

#ifndef point_operations_hpp
#define point_operations_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "utils.hpp"

enum class ColorChannel { BLUE = 0, GREEN = 1, RED = 2 };

void tresh(cv::Mat& I, unsigned char min_t = 0, unsigned char max_t = 255);

#endif /* point_operations_hpp */
