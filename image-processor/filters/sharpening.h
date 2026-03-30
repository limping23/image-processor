#pragma once

#include "filter.h"
#include <algorithm>
#include <vector>

class Sharpening : public Filter {
public:
    void Apply(BmpImage& img) override;
};