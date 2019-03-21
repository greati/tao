#include "gtest/gtest.h"
#include "linear_algebra/Mat.h"

namespace {

    TEST(MatDouble, Creation) {
        tao::Mat<double> mat {
            {1.0, 2.0},
            {3.0, 4.0},
            {5.0, 6.0}
        };
    };

    TEST(MatDouble, InitializerError) {
        try {
            tao::Mat<double> mat2 {
                {1.0, 2.0},
                {3.0},
                {5.0, 6.0}
            };
            FAIL();
        } catch (std::invalid_argument& e1) {
            try {
                tao::Mat<double> mat2 {
                    {1.0, 2.0},
                    {3.0},
                };
                FAIL();
            } catch(std::invalid_argument& e2) {
            
            }
        }
    };

    TEST(MatDouble, InitializerAllEmptyError) {
        try {
            tao::Mat<double> mat2 {};
            FAIL();
        } catch (std::invalid_argument& e) {
            SUCCEED();
        }
    };

    TEST(MatDouble, InitializerColsEmptyError) {
        try {
            tao::Mat<double> mat2 {
                {}, {}
            };
            FAIL();
        } catch (std::invalid_argument& e) {
            SUCCEED();
        }
    };
};
