#include "grayscale.h"

void Grayscale::Apply(BmpImage& img) {
    const double red_coefficient = 0.299;
    const double green_coefficient = 0.587;
    const double blue_coefficient = 0.114;
    const int width = img.info_header.bi_width;
    const int height = img.info_header.bi_height;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            const double new_color = img.matrix[i][j].r * red_coefficient + img.matrix[i][j].g * green_coefficient +
                                     img.matrix[i][j].b * blue_coefficient;

            const unsigned char gray = static_cast<unsigned char>(new_color);
            img.matrix[i][j].r = gray;
            img.matrix[i][j].g = gray;
            img.matrix[i][j].b = gray;
        }
    }
}