#pragma once

#include <memory>
#include <vector>
#include "arg_parser.h"
#include "bmp.h"
#include "filters/filter.h"
#include <stdexcept>
#include "filters/crop.h"
#include "filters/edge.h"
#include "filters/gauss.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/sharpening.h"
#include "filters/whitepoint.h"

class Pipeline {
public:
    explicit Pipeline(const std::vector<FilterArgs>& args);

    void Run(BmpImage& img);

private:
    std::vector<std::unique_ptr<Filter>> filters_;
};