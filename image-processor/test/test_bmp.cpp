#include <cassert>
#include <fstream>
#include "../bmp.h"

const int INVALIDWIDTH = -67;
const int INVALIDHEIGHT = 52;
const uint8_t RED = 255;
const uint8_t GREEN = 255;
const uint8_t BLUE = 255;

void TestFileNotFound404() {
    try {
        auto img = ReadBmp("serega.bmp");
        assert(false);
    } catch (const std::runtime_error& err) {
        assert(std::string(err.what()) == "Cannot open file");
    }
}

void TestWrongSignature() {
    std::ofstream file("wrong.bmp", std::ios::binary);
    const int not_bmp = 0x1234;
    file.write(reinterpret_cast<const char*>(&not_bmp), sizeof(not_bmp));
    file.close();

    try {
        auto img = ReadBmp("wrong.bmp");
        assert(false);
    } catch (const std::runtime_error& err) {
        assert(std::string(err.what()) == "Cannot open file");
    }
}

void TestWrongSize() {
    BmpImage img;
    img.info_header.bi_width = INVALIDWIDTH;
    img.info_header.bi_height = INVALIDHEIGHT;

    try {
        WriteBmp("sizseven.bmp", img);
        assert(false);
    } catch (const std::runtime_error& err) {
        assert(std::string(err.what()) == "Incorrect image size");
    }
}

void TestReadWriteBmp() {
    BmpImage img;
    img.info_header.bi_width = 2;
    img.info_header.bi_height = 2;

    img.matrix = {{{{RED, 0, 0}, {0, GREEN, 0}}, {{0, 0, BLUE}, {RED, GREEN, BLUE}}}};

    WriteBmp("test.bmp", img);
    auto read_img = ReadBmp("test.bmp");

    assert(read_img.info_header.bi_width == 2);
    assert(read_img.info_header.bi_height == 2);

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            assert(read_img.matrix[i][j].r == img.matrix[i][j].r);
            assert(read_img.matrix[i][j].g == img.matrix[i][j].g);
            assert(read_img.matrix[i][j].b == img.matrix[i][j].b);
        }
    }
}