#pragma once

#include "filter.h"

class Grayscale : public Filter {
public:
    void Apply(BmpImage& img) override;
};