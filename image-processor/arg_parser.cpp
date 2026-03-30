#include "arg_parser.h"

void PrintHelp() {
    std::cout << "Usage:\n";
    std::cout << "./image_processor input.bmp output.bmp [filters]\n";
    std::cout << "Filters:\n";
    std::cout << "-crop width height\n";
    std::cout << "-gs\n";
    std::cout << "-neg\n";
    std::cout << "-sharp\n";
    std::cout << "-edge threshold\n";
    std::cout << "-blur sigma\n";
    std::cout << "-white r g b\n";
}

ImageProcessorArgs ExtractImageProcessorArgs(int argc, char** argv) {
    if (argc == 1) {
        PrintHelp();
        throw std::runtime_error("No arguments");
    }
    if (argc < 3) {
        PrintHelp();
        throw std::runtime_error("Not enough arguments");
    }

    ImageProcessorArgs result;
    result.input_file = argv[1];
    result.output_file = argv[2];

    int i = 3;

    while (i < argc) {
        std::string name = argv[i];

        if (name[0] != '-') {
            throw std::runtime_error("Filter name must start with '-'");
        }

        FilterArgs filter;
        filter.filter_name = name;
        ++i;

        while (i < argc && argv[i][0] != '-') {
            filter.filter_args.push_back(argv[i]);
            ++i;
        }

        result.filters.push_back(filter);
    }

    return result;
}