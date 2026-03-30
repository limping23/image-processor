#pragma once

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

#pragma pack(push, 1)

struct BmpFileHeader {
    uint16_t bf_type;
    uint32_t bf_size;
    uint16_t bf_reserved1;
    uint16_t bf_reserved2;
    uint32_t bf_off_bits;
};

struct BmpInfoHeader {
    uint32_t bi_size;
    int32_t bi_width;
    int32_t bi_height;
    uint16_t bi_planes;
    uint16_t bi_bit_count;
    uint32_t bi_compression;
    uint32_t bi_size_image;
    int32_t bi_x_pels_per_meter;
    int32_t bi_y_pels_per_meter;
    uint32_t bi_clr_used;
    uint32_t bi_clr_important;
};

#pragma pack(pop)

struct Pixel {
    unsigned char b;
    unsigned char g;
    unsigned char r;
};

struct BmpImage {
    BmpFileHeader file_header;
    BmpInfoHeader info_header;
    std::vector<std::vector<Pixel>> matrix;
};

BmpImage ReadBmp(const std::string& path);
void WriteBmp(const std::string& path, const BmpImage& img);