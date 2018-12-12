//
//  segmentation.cpp
//  finding_pepsi
//
//  Created by Paweł Rybak on 12/12/2018.
//  Copyright © 2018 Paweł Rybak. All rights reserved.
//

#include "segmentation.hpp"


cv::Mat getShape(cv::Mat& I, unsigned int i, unsigned int j)
{
    cv::Mat O = I.clone();
    std::deque<Point> deque;
    
    deque.push_back({i, j});
    
    cv::Mat_<cv::Vec3b> _I = I;
    cv::Mat_<cv::Vec3b> _O = O;
    while (!deque.empty()) {
        Point cur = deque.front();
        deque.pop_front();
        
        if (mean(std::apply(_I, cur)) == 0) {
            continue;
        }
        
        std::apply(_I, cur) = { 0, 0, 0 };
        std::apply(_O, cur) = { 127, 127, 127 };
        
        if (cur.first > 0 && mean(_O(cur.first - 1, cur.second)) == 255) {
            deque.push_back({cur.first - 1, cur.second});
        }
        if (cur.first < I.rows - 1 && mean(_O(cur.first + 1, cur.second)) == 255) {
            deque.push_back({cur.first + 1, cur.second});
        }
        if (cur.second > 0 && mean(_O(cur.first, cur.second - 1)) == 255) {
            deque.push_back({cur.first, cur.second - 1});
        }
        if (cur.second < I.cols - 1 && mean(_O(cur.first, cur.second + 1)) == 255) {
            deque.push_back({cur.first, cur.second + 1});
        }
    }
    
    tresh(O, 127, 127);
    return O;
}


void getSegments(cv::Mat& I, std::vector<cv::Mat>& dst)
{
    forEach(I, [&](cv::Mat_<cv::Vec3b>& _I, unsigned int i, unsigned int j) {
        if (mean(_I(i, j)) != 0) {
            dst.push_back(getShape(_I, i, j));
        }
    });
}
