#include "gtest/gtest.h"
#include "linear_algebra/Mat.h"

namespace {

    TEST(MatDouble, CreationInitializer) {
        tao::Mat<double> mat {
            {1.0, 2.0},
            {3.0, 4.0},
            {5.0, 6.0}
        };

        ASSERT_EQ(mat.nrows(), 3);
        ASSERT_EQ(mat.ncols(), 2);
    };

    TEST(MatDouble, CreationSquare) {
        tao::Mat<double> mat {20}; 
        ASSERT_EQ(mat.nrows(), 20);
        ASSERT_EQ(mat.ncols(), 20);
    }

    TEST(MatDouble, CreationDimensionsNoDefault) {
        tao::Mat<double> mat {20, 10}; 
        ASSERT_EQ(mat.nrows(), 20);
        ASSERT_EQ(mat.ncols(), 10);
    }

    TEST(MatDouble, CreationDimensionsDefault) {
        tao::Mat<double> mat {20, 10, 1.0}; 
        ASSERT_EQ(mat.nrows(), 20);
        ASSERT_EQ(mat.ncols(), 10);
    }

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

    TEST(MatDouble, AccessOperatorSuccess0) {
        tao::Mat<double> mat {
            {1.0, 2.0, 3.0, 4.0},
            {3.0, 4.0, 10.0, 20.0}
        };
        ASSERT_EQ(mat.nrows(), 2);
        ASSERT_EQ(mat.ncols(), 4);
        ASSERT_FLOAT_EQ(mat(0, 0), 1.0);
        ASSERT_FLOAT_EQ(mat(0, 1), 2.0);
        ASSERT_FLOAT_EQ(mat(0, 2), 3.0);
        ASSERT_FLOAT_EQ(mat(0, 3), 4.0);
        ASSERT_FLOAT_EQ(mat(1, 0), 3.0);
        ASSERT_FLOAT_EQ(mat(1, 1), 4.0);
        ASSERT_FLOAT_EQ(mat(1, 2), 10.0);
        ASSERT_FLOAT_EQ(mat(1, 3), 20.0);
    }

    TEST(MatDouble, AccessOperatorSuccess1) {
        tao::Mat<double> mat {
            {1.0, 2.0},
            {3.0, 4.0}
        };
        ASSERT_EQ(mat.nrows(), 2);
        ASSERT_EQ(mat.ncols(), 2);
        ASSERT_FLOAT_EQ(mat(0, 0), 1.0);
        ASSERT_FLOAT_EQ(mat(0, 1), 2.0);
        ASSERT_FLOAT_EQ(mat(1, 0), 3.0);
        ASSERT_FLOAT_EQ(mat(1, 1), 4.0);
    }

    TEST(MatDouble, AccessOperatorSuccess2) {
        tao::Mat<double> mat {
            {1.0},
            {3.0}
        };
        ASSERT_EQ(mat.nrows(), 2);
        ASSERT_EQ(mat.ncols(), 1);
        ASSERT_FLOAT_EQ(mat(0, 0), 1.0);
        ASSERT_FLOAT_EQ(mat(1, 0), 3.0);
    }

    TEST(MatDouble, AccessOperatorSuccess3) {
        tao::Mat<double> mat {
            {1.0, 3.0}
        };
        ASSERT_EQ(mat.nrows(), 1);
        ASSERT_EQ(mat.ncols(), 2);
        ASSERT_FLOAT_EQ(mat(0, 0), 1.0);
        ASSERT_FLOAT_EQ(mat(0, 1), 3.0);
    }

    TEST(MatDouble, AccessOperatorSuccess4) {
        tao::Mat<double> mat {
            {1.0}
        };
        ASSERT_EQ(mat.nrows(), 1);
        ASSERT_EQ(mat.ncols(), 1);
        ASSERT_FLOAT_EQ(mat(0, 0), 1.0);
    }

    TEST(MatDouble, AccessOperatorFailure0) {
        tao::Mat<double> mat {
            {1.0, 2.0, 3.0, 4.0},
            {3.0, 4.0, 10.0, 20.0}
        };
        ASSERT_EQ(mat.nrows(), 2);
        ASSERT_EQ(mat.ncols(), 4);
        ASSERT_THROW(mat(-1, 0), std::invalid_argument);
        ASSERT_THROW(mat(-10, 3), std::invalid_argument);
        ASSERT_THROW(mat(0, -1), std::invalid_argument);
        ASSERT_THROW(mat(0, -13), std::invalid_argument);
        ASSERT_THROW(mat(3, 0), std::invalid_argument);
        ASSERT_THROW(mat(20, 1), std::invalid_argument);
        ASSERT_THROW(mat(0, 4), std::invalid_argument);
        ASSERT_THROW(mat(1, 15), std::invalid_argument);
        ASSERT_THROW(mat(-1, -1), std::invalid_argument);
        ASSERT_THROW(mat(10, 10), std::invalid_argument);
    }
};
