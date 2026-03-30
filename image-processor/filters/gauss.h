#pragma once

#include "filter.h"
#include <algorithm>
#include <cmath>
#include <vector>

class Gauss : public Filter {
public:
    explicit Gauss(double new_sigma);
    void Apply(BmpImage& img) override;

private:
    double sigma_;
};