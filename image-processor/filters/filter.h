#pragma once

#include "../bmp.h"

class Filter {
public:
    virtual void Apply(BmpImage& img) = 0;
    virtual ~Filter() = default;
};
