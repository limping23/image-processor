#pragma once

#include "filter.h"

class Crop : public Filter {
public:
    Crop(int new_width, int new_height);
    void Apply(BmpImage& img) override;

private:
    int width_;
    int height_;
};
