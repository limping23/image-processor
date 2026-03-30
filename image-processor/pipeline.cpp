#include "pipeline.h"

Pipeline::Pipeline(const std::vector<FilterArgs>& args) {
    const double max_edge_threshold = 1.0;
    const int min_color_value = 0;
    const int max_color_value = 255;

    for (size_t i = 0; i < args.size(); ++i) {
        const FilterArgs& filter_args = args[i];

        if (filter_args.filter_name == "-crop") {
            if (filter_args.filter_args.size() != 2) {
                throw std::runtime_error("Filter -crop requires 2 arguments: width and height");
            }

            const int width = std::stoi(filter_args.filter_args[0]);
            const int height = std::stoi(filter_args.filter_args[1]);

            if (width <= 0 || height <= 0) {
                throw std::runtime_error("Crop width and height must be positive");
            }

            filters_.push_back(std::make_unique<Crop>(width, height));

        } else if (filter_args.filter_name == "-gs") {
            if (!filter_args.filter_args.empty()) {
                throw std::runtime_error("Filter -gs does not require any arguments");
            }

            filters_.push_back(std::make_unique<Grayscale>());

        } else if (filter_args.filter_name == "-neg") {
            if (!filter_args.filter_args.empty()) {
                throw std::runtime_error("Filter -neg does not require any arguments");
            }

            filters_.push_back(std::make_unique<Negative>());

        } else if (filter_args.filter_name == "-sharp") {
            if (!filter_args.filter_args.empty()) {
                throw std::runtime_error("Filter -sharp does not require any arguments");
            }

            filters_.push_back(std::make_unique<Sharpening>());

        } else if (filter_args.filter_name == "-edge") {
            if (filter_args.filter_args.size() != 1) {
                throw std::runtime_error("Filter -edge requires 1 argument: threshold");
            }

            const double threshold = std::stod(filter_args.filter_args[0]);

            if (threshold > max_edge_threshold) {
                throw std::runtime_error("Edge threshold must be lower than 1");
            }

            filters_.push_back(std::make_unique<Edge>(threshold));

        } else if (filter_args.filter_name == "-blur") {
            if (filter_args.filter_args.size() != 1) {
                throw std::runtime_error("Filter -blur requires 1 argument: sigma");
            }

            const double sigma = std::stod(filter_args.filter_args[0]);

            if (sigma <= 0) {
                throw std::runtime_error("Blur sigma must be positive");
            }

            filters_.push_back(std::make_unique<Gauss>(sigma));

        } else if (filter_args.filter_name == "-white") {
            if (filter_args.filter_args.size() != 3) {
                throw std::runtime_error("Filter -white requires 3 arguments: red, green, blue");
            }

            const int r = std::stoi(filter_args.filter_args[0]);
            const int g = std::stoi(filter_args.filter_args[1]);
            const int b = std::stoi(filter_args.filter_args[2]);

            if (r < min_color_value || r > max_color_value || g < min_color_value || g > max_color_value ||
                b < min_color_value || b > max_color_value) {
                throw std::runtime_error("White point values must be in range [0, 255]");
            }

            filters_.push_back(std::make_unique<Whitepoint>(r, g, b));

        } else {
            throw std::runtime_error("Unknown filter: " + filter_args.filter_name);
        }
    }
}

void Pipeline::Run(BmpImage& img) {
    for (size_t i = 0; i < filters_.size(); ++i) {
        filters_[i]->Apply(img);
    }
}