#include "edge.h"

Edge::Edge(double new_threshold) : threshold_(new_threshold) {
}

void Edge::Apply(BmpImage& img) {
    const int matrix_size = 3;
    const int white_color = 255;
    const int black_color = 0;
    const int color_scale = 255;

    Grayscale grayscale;
    grayscale.Apply(img);

    const int width = img.info_header.bi_width;
    const int height = img.info_header.bi_height;

    const int edge_matrix[matrix_size][matrix_size] = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

    std::vector<std::vector<Pixel>> new_matrix = img.matrix;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int value = 0;

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

                    value += img.matrix[ni][nj].r * edge_matrix[ki + 1][kj + 1];
                }
            }

            if (value > threshold_ * color_scale) {
                new_matrix[i][j].r = white_color;
                new_matrix[i][j].g = white_color;
                new_matrix[i][j].b = white_color;
            } else {
                new_matrix[i][j].r = black_color;
                new_matrix[i][j].g = black_color;
                new_matrix[i][j].b = black_color;
            }
        }
    }

    img.matrix = new_matrix;
}