#pragma once

#include "filter.h"

class Negative : public Filter {
public:
    void Apply(BmpImage& img) override;
};