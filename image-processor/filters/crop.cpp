#include "crop.h"

Crop::Crop(int new_width, int new_height) : width_(new_width), height_(new_height) {
}

void Crop::Apply(BmpImage& img) {
    const int prev_width = img.info_header.bi_width;
    const int prev_height = img.info_header.bi_height;

    if (width_ > prev_width) {
        width_ = prev_width;
    }
    if (height_ > prev_height) {
        height_ = prev_height;
    }

    std::vector<std::vector<Pixel>> new_matrix;
    new_matrix.resize(height_);

    for (int i = 0; i < height_; ++i) {
        new_matrix[i].resize(width_);
    }

    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            new_matrix[i][j] = img.matrix[i][j];
        }
    }

    img.matrix = new_matrix;
    img.info_header.bi_width = width_;
    img.info_header.bi_height = height_;
}