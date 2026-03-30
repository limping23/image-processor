#include <iostream>

void TestPipeline();
void TestUnknownFilter();
void TestCropWithoutArgs();
void TestWhite();
void TestExtraArgs();
void TestFilters();
void TestFilterNameWithoutTire();
void TestFileNotFound404();
void TestWrongSignature();
void TestWrongSize();
void TestReadWriteBmp();

int main() {
    TestPipeline();
    TestUnknownFilter();
    TestCropWithoutArgs();
    TestWhite();
    TestExtraArgs();
    TestFilters();
    TestFilterNameWithoutTire();
    TestFileNotFound404();
    TestWrongSignature();
    TestWrongSize();
    TestReadWriteBmp();
    std::cout << "All assetions passed!" << "\n";
}
