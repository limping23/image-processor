#pragma once

#include "filter.h"
#include "grayscale.h"

class Edge : public Filter {
public:
    explicit Edge(double new_threshold);
    void Apply(BmpImage& img) override;

private:
    double threshold_;
};