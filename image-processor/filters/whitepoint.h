#pragma once

#include "filter.h"

class Whitepoint : public Filter {
public:
    Whitepoint(int new_r, int new_g, int new_b);

    void Apply(BmpImage& img) override;

private:
    int white_r_;
    int white_g_;
    int white_b_;
};