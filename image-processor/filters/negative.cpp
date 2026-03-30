#include "negative.h"

void Negative::Apply(BmpImage& img) {
    const int max_color_value = 255;

    const int width = img.info_header.bi_width;
    const int height = img.info_header.bi_height;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            img.matrix[i][j].r = max_color_value - img.matrix[i][j].r;
            img.matrix[i][j].g = max_color_value - img.matrix[i][j].g;
            img.matrix[i][j].b = max_color_value - img.matrix[i][j].b;
        }
    }
}