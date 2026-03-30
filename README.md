# Image Processor

## Description

Console app for changing BMP images

Reads an input file, applies filters, and writes the result into an output file

## Usage

```bash
./image_processor input.bmp output.bmp [filters]
```
## Filters
- ``` -crop width height ``` — crop image from top-left
- ``` -gs ``` — grayscale
- ``` -neg ``` — negative
- ``` -sharp ``` — sharpening
- ``` -edge threshold ``` — edge detection
- ``` -blur sigma ``` — Gaussian blur
- ``` -white r g b ``` — change white balance
### Build
```bash
g++ -std=c++17 image_processor.cpp bmp.cpp arg_parser.cpp filter/*.cpp -o image_processor
```
### Tests
```bash
g++ -std=c++17 test/test_main.cpp test/test_bmp.cpp test/test_filter.cpp bmp.cpp filter/*.cpp -o tests
```
### Example
```bash
./image_processor input.bmp output.bmp -crop 200 200 -gs -edge 0.2
```
Code in example will sequently apply crop filter (width - 200; height - 200), grayscale and edge detection (threshold - 0.2)
#### Made as project on C++ course at FCS HSE
