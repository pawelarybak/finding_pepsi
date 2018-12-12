//
//  window_operations.hpp
//  finding_pepsi
//
//  Created by Paweł Rybak on 12/12/2018.
//  Copyright © 2018 Paweł Rybak. All rights reserved.
//

#ifndef window_operations_hpp
#define window_operations_hpp

#include <stdio.h>

#include "utils.hpp"

void blur(cv::Mat& I);
void open(cv::Mat& I, unsigned int rank = 1);
void close(cv::Mat& I, unsigned int rank = 1);
void medianFilter(cv::Mat& I);


#endif /* window_operations_hpp */
