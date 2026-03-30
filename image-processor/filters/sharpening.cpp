#include "sharpening.h"

void Sharpening::Apply(BmpImage& img) {
    const int matrix_size = 3;
    const int center_value = 5;
    const int min_color_value = 0;
    const int max_color_value = 255;

    const int width = img.info_header.bi_width;
    const int height = img.info_header.bi_height;

    const int sharp_matrix[matrix_size][matrix_size] = {{0, -1, 0}, {-1, center_value, -1}, {0, -1, 0}};

    std::vector<std::vector<Pixel>> new_matrix = img.matrix;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int r = 0;
            int g = 0;
            int b = 0;

            for (int ki = -1; ki <= 1; ++ki) {
                for (int kj = -1; kj <= 1; ++kj) {
                    int ni = i + ki;
                    int nj = j + kj;

                    if (ni < 0) {
                        ni = 0;
                    }
                    if (ni >= height) {
                        ni = height - 1;
                    }
                    if (nj < 0) {
                        nj = 0;
                    }
                    if (nj >= width) {
                        nj = width - 1;
                    }

                    r += img.matrix[ni][nj].r * sharp_matrix[ki + 1][kj + 1];
                    g += img.matrix[ni][nj].g * sharp_matrix[ki + 1][kj + 1];
                    b += img.matrix[ni][nj].b * sharp_matrix[ki + 1][kj + 1];
                }
            }

            new_matrix[i][j].r = std::min(max_color_value, std::max(min_color_value, r));
            new_matrix[i][j].g = std::min(max_color_value, std::max(min_color_value, g));
            new_matrix[i][j].b = std::min(max_color_value, std::max(min_color_value, b));
        }
    }

    img.matrix = new_matrix;
}