#include "bmp.h"

#include <stdexcept>

BmpImage ReadBmp(const std::string& path) {
    const int bmp_signature = 0x4D42;
    const int bmp_info_header_size = 40;
    const int bmp_bits_per_pixel = 24;
    const int bmp_no_compression = 0;
    const int bmp_planes = 1;
    const int bmp_bytes_per_pixel = 3;
    const int bmp_row_align = 4;

    BmpImage img;
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }

    file.read(reinterpret_cast<char*>(&img.file_header), sizeof(img.file_header));
    file.read(reinterpret_cast<char*>(&img.info_header), sizeof(img.info_header));

    if (!file) {
        throw std::runtime_error("Cannot open file");
    }

    if (img.file_header.bf_type != bmp_signature) {
        throw std::runtime_error("Input file must be .bmp file");
    }

    if (img.info_header.bi_size != bmp_info_header_size) {
        throw std::runtime_error("Input file must be .bmp file");
    }

    if (img.info_header.bi_planes != bmp_planes) {
        throw std::runtime_error("Incorrect BMP type");
    }

    if (img.info_header.bi_bit_count != bmp_bits_per_pixel) {
        throw std::runtime_error("Incorrect BMP type");
    }

    if (img.info_header.bi_compression != bmp_no_compression) {
        throw std::runtime_error("Incorrect BMP type");
    }

    const int width = img.info_header.bi_width;
    int height = img.info_header.bi_height;

    if (width <= 0) {
        throw std::runtime_error("Incorrect BMP type");
    }

    if (height == 0) {
        throw std::runtime_error("Incorrect BMP type");
    }

    bool top_down = false;
    if (height < 0) {
        top_down = true;
        height = -height;
    }

    const int padding = (bmp_row_align - (width * bmp_bytes_per_pixel) % bmp_row_align) % bmp_row_align;

    img.matrix.resize(height);
    for (int i = 0; i < height; ++i) {
        img.matrix[i].resize(width);
    }

    file.seekg(img.file_header.bf_off_bits, std::ios::beg);

    if (!file) {
        throw std::runtime_error("Incorrect BMP type");
    }

    char skip_buffer[3] = {0, 0, 0};

    if (top_down) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                file.read(reinterpret_cast<char*>(&img.matrix[i][j]), sizeof(Pixel));
            }

            file.read(skip_buffer, padding);

            if (!file) {
                throw std::runtime_error("Incorrect BMP type");
            }
        }
    } else {
        for (int i = height - 1; i >= 0; --i) {
            for (int j = 0; j < width; ++j) {
                file.read(reinterpret_cast<char*>(&img.matrix[i][j]), sizeof(Pixel));
            }

            file.read(skip_buffer, padding);

            if (!file) {
                throw std::runtime_error("Incorrect BMP type");
            }
        }
    }

    img.info_header.bi_height = height;

    return img;
}

void WriteBmp(const std::string& path, const BmpImage& img) {
    const int bmp_signature = 0x4D42;
    const int bmp_info_header_size = 40;
    const int bmp_bits_per_pixel = 24;
    const int bmp_no_compression = 0;
    const int bmp_pixel_offset = 54;
    const int bmp_planes = 1;
    const int bmp_bytes_per_pixel = 3;
    const int bmp_row_align = 4;

    std::ofstream file(path, std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }

    const int width = img.info_header.bi_width;
    const int height = img.info_header.bi_height;

    if (width <= 0 || height <= 0) {
        throw std::runtime_error("Incorrect image size");
    }

    const int padding = (bmp_row_align - (width * bmp_bytes_per_pixel) % bmp_row_align) % bmp_row_align;

    BmpFileHeader file_header;
    BmpInfoHeader info_header;

    file_header.bf_type = bmp_signature;
    file_header.bf_size = bmp_pixel_offset + (width * bmp_bytes_per_pixel + padding) * height;
    file_header.bf_reserved1 = 0;
    file_header.bf_reserved2 = 0;
    file_header.bf_off_bits = bmp_pixel_offset;

    info_header.bi_size = bmp_info_header_size;
    info_header.bi_width = width;
    info_header.bi_height = height;
    info_header.bi_planes = bmp_planes;
    info_header.bi_bit_count = bmp_bits_per_pixel;
    info_header.bi_compression = bmp_no_compression;
    info_header.bi_size_image = (width * bmp_bytes_per_pixel + padding) * height;
    info_header.bi_x_pels_per_meter = 0;
    info_header.bi_y_pels_per_meter = 0;
    info_header.bi_clr_used = 0;
    info_header.bi_clr_important = 0;

    file.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
    file.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));

    if (!file) {
        throw std::runtime_error("Incorrect BMP type");
    }

    const char empty[3] = {0, 0, 0};

    for (int i = height - 1; i >= 0; --i) {
        for (int j = 0; j < width; ++j) {
            file.write(reinterpret_cast<const char*>(&img.matrix[i][j]), sizeof(Pixel));
        }

        file.write(empty, padding);
    }

    if (!file) {
        throw std::runtime_error("Incorrect BMP type");
    }
}