#include <iostream>
#include <stdexcept>
#include "arg_parser.h"
#include "bmp.h"
#include "pipeline.h"

int main(int argc, char** argv) {
    try {
        ImageProcessorArgs args = ExtractImageProcessorArgs(argc, argv);
        BmpImage img = ReadBmp(args.input_file);

        Pipeline pipeline(args.filters);
        pipeline.Run(img);

        WriteBmp(args.output_file, img);
        return 0;

    } catch (const std::exception& err) {
        std::cerr << "Error: " << err.what() << "\n";
        return 1;
    }
}
