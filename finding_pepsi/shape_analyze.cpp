//
//  shape_analyze.cpp
//  finding_pepsi
//
//  Created by Paweł Rybak on 12/12/2018.
//  Copyright © 2018 Paweł Rybak. All rights reserved.
//

#include "shape_analyze.hpp"


double m(cv::Mat& I, int p, int q)
{
    double sum = 0;
    
    forEach(I, [&](cv::Mat_<cv::Vec3b>& _I, unsigned int i, unsigned int j) {
        if (mean(_I(i, j)) == 255) {
            sum += (pow(i, p)) * (pow(j, q));
        }
    });
    
    return sum;
}

Point centrPoint(cv::Mat& I)
{
    const double m00 = m(I, 0, 0);
    return { m(I, 0, 1) / m00, m(I, 1, 0) / m00 };
}

double M(cv::Mat& I, int p, int q)
{
    double sum = 0;
    double x_m, y_m;
    std::tie(x_m, y_m) = centrPoint(I);
    
    forEach(I, [&](cv::Mat_<cv::Vec3b>& _I, unsigned int i, unsigned int j) {
        if (mean(_I(i, j)) == 255) {
            sum += pow(i - x_m, p) * pow(j - y_m , q);
        }
    });

    return sum;
}

int field(cv::Mat& I)
{
    return m(I, 0, 0);
}

int circ(cv::Mat& I)
{
    return field(edgeFilter(I));
}

double malinowska(cv::Mat& I)
{
    double _f = field(I);
    double _c = circ(I);
    return _c / (2 * sqrt(M_PI * _f)) - 1.0;
}

Rect mbb(cv::Mat& I)
{
    unsigned int x_min = UINT_MAX;
    unsigned int x_max = 0;
    unsigned int y_min = UINT_MAX;
    unsigned int y_max = 0;
    
    forEach(I, [&](cv::Mat_<cv::Vec3b>& _I, unsigned int i, unsigned int j) {
        if (mean(_I(i, j)) == 255) {
            x_min = std::min(x_min, i);
            x_max = std::max(x_max, i);
            y_min = std::min(y_min, j);
            y_max = std::max(y_max, j);
        }
    });
    
    return { y_min, x_min, y_max, x_max };
}

double dist(Point lhs, Point rhs)
{
    return sqrt(pow(rhs.first - lhs.first, 2) + pow(rhs.second - lhs.second, 2));
}

double rDist(cv::Mat& I, cv::Mat& O)
{
    return dist(centrPoint(I), centrPoint(O)) / sqrt(field(I) + field(O));
}
