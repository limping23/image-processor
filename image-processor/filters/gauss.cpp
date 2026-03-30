#include "gauss.h"

Gauss::Gauss(double new_sigma) : sigma_(new_sigma) {
}

void Gauss::Apply(BmpImage& img) {
    const int weight_radius_multiplier = 3;
    const int weight_center_offset = 1;
    const double min_color_value = 0.0;
    const double max_color_value = 255.0;

    const int width = img.info_header.bi_width;
    const int height = img.info_header.bi_height;

    if (sigma_ <= 0) {
        return;
    }

    const int radius = static_cast<int>(std::ceil(weight_radius_multiplier * sigma_));
    const int size = 2 * radius + weight_center_offset;

    std::vector<double> weights(size);
    double sum = 0.0;

    for (int i = -radius; i <= radius; ++i) {
        const double value = std::exp(-(i * i) / (2.0 * sigma_ * sigma_));
        weights[i + radius] = value;
        sum += value;
    }

    for (int i = 0; i < size; ++i) {
        weights[i] /= sum;
    }

    std::vector<std::vector<Pixel>> temp(height, std::vector<Pixel>(width));
    std::vector<std::vector<Pixel>> new_matrix(height, std::vector<Pixel>(width));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double new_r = 0.0;
            double new_g = 0.0;
            double new_b = 0.0;

            for (int k = -radius; k <= radius; ++k) {
                int nx = x + k;

                if (nx < 0) {
                    nx = 0;
                }
                if (nx >= width) {
                    nx = width - 1;
                }

                new_r += img.matrix[y][nx].r * weights[k + radius];
                new_g += img.matrix[y][nx].g * weights[k + radius];
                new_b += img.matrix[y][nx].b * weights[k + radius];
            }

            new_r = std::min(max_color_value, std::max(min_color_value, new_r));
            new_g = std::min(max_color_value, std::max(min_color_value, new_g));
            new_b = std::min(max_color_value, std::max(min_color_value, new_b));

            temp[y][x].r = static_cast<unsigned char>(new_r);
            temp[y][x].g = static_cast<unsigned char>(new_g);
            temp[y][x].b = static_cast<unsigned char>(new_b);
        }
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double new_r = 0.0;
            double new_g = 0.0;
            double new_b = 0.0;

            for (int k = -radius; k <= radius; ++k) {
                int ny = y + k;

                if (ny < 0) {
                    ny = 0;
                }
                if (ny >= height) {
                    ny = height - 1;
                }

                new_r += temp[ny][x].r * weights[k + radius];
                new_g += temp[ny][x].g * weights[k + radius];
                new_b += temp[ny][x].b * weights[k + radius];
            }

            new_r = std::min(max_color_value, std::max(min_color_value, new_r));
            new_g = std::min(max_color_value, std::max(min_color_value, new_g));
            new_b = std::min(max_color_value, std::max(min_color_value, new_b));

            new_matrix[y][x].r = static_cast<unsigned char>(new_r);
            new_matrix[y][x].g = static_cast<unsigned char>(new_g);
            new_matrix[y][x].b = static_cast<unsigned char>(new_b);
        }
    }

    img.matrix = new_matrix;
}