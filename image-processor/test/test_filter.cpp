#include <cassert>
#include "../pipeline.h"
#include "../arg_parser.h"

const int VOSEM = 8;

void TestPipeline() {
    std::vector<FilterArgs> args = {{"-gs", {}}, {"-sharp", {}}, {"-edge", {"0.5"}}};
    Pipeline p(args);

    assert(true);
}

void TestUnknownFilter() {
    std::vector<FilterArgs> args = {{"-sosisochki", {}}};
    try {
        Pipeline p(args);
        assert(false);
    } catch (const std::runtime_error&) {
        assert(true);
    }
}

void TestCropWithoutArgs() {
    std::vector<FilterArgs> args = {{"-crop", {"100"}}};
    try {
        Pipeline p(args);
        assert(false);
    } catch (...) {
        assert(true);
    }
}

void TestWhite() {
    std::vector<FilterArgs> args = {{"-white", {"256", "256", "0"}}};
    try {
        Pipeline p(args);
        assert(false);
    } catch (...) {
        assert(true);
    }
}

void TestExtraArgs() {
    std::vector<FilterArgs> args = {{"-gs", {"67"}}};
    try {
        Pipeline p(args);
        assert(false);
    } catch (...) {
        assert(true);
    }
}

void TestFilters() {
    char arg0[] = "name";
    char arg1[] = "in.bmp";
    char arg2[] = "out.bmp";
    char arg3[] = "-gs";
    char arg4[] = "-edge";
    char arg5[] = "0.5";
    char arg6[] = "-sharp";
    char arg7[] = "-neg";

    char* argv[] = {arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7};

    auto res = ExtractImageProcessorArgs(VOSEM, argv);

    assert(res.filters.size() == 4);
    assert(res.filters[0].filter_name == "-gs");
    assert(res.filters[1].filter_name == "-edge");
    assert(res.filters[1].filter_args[0] == "0.5");
    assert(res.filters[2].filter_name == "-sharp");
    assert(res.filters[3].filter_name == "-neg");
}

void TestFilterNameWithoutTire() {
    char arg0[] = "name";
    char arg1[] = "in.bmp";
    char arg2[] = "out.bmp";
    char arg3[] = "gs";
    char* argv[] = {arg0, arg1, arg2, arg3};

    try {
        ExtractImageProcessorArgs(4, argv);
        assert(false);
    } catch (...) {
        assert(true);
    }
}