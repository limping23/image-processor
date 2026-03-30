#include "whitepoint.h"

#include <algorithm>

Whitepoint::Whitepoint(int new_r, int new_g, int new_b) : white_r_(new_r), white_g_(new_g), white_b_(new_b) {
}

void Whitepoint::Apply(BmpImage& img) {
    const int min_white_value = 1;
    const double min_color_value = 0.0;
    const double max_color_value = 255.0;
    const double color_scale = 255.0;

    const int width = img.info_header.bi_width;
    const int height = img.info_header.bi_height;

    white_r_ = std::max(min_white_value, white_r_);
    white_g_ = std::max(min_white_value, white_g_);
    white_b_ = std::max(min_white_value, white_b_);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double new_r = img.matrix[i][j].r * color_scale / white_r_;
            double new_g = img.matrix[i][j].g * color_scale / white_g_;
            double new_b = img.matrix[i][j].b * color_scale / white_b_;

            new_r = std::min(max_color_value, std::max(min_color_value, new_r));
            new_g = std::min(max_color_value, std::max(min_color_value, new_g));
            new_b = std::min(max_color_value, std::max(min_color_value, new_b));

            img.matrix[i][j].r = static_cast<unsigned char>(new_r);
            img.matrix[i][j].g = static_cast<unsigned char>(new_g);
            img.matrix[i][j].b = static_cast<unsigned char>(new_b);
        }
    }
}