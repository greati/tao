#include "gtest/gtest.h"
#include "tao/linalg/dyn/Col.h"
#include "tao/linalg/dyn/VecOperations.h"
#include <cmath>

namespace {

    TEST(ColDouble, CreationInitializer) {
        tao::deprecated::Col<double> col {1.0, 2.0, 3.0};
        ASSERT_EQ(col.nrows(), 3);
        ASSERT_EQ(col.ncols(), 1);
    };

    TEST(ColDouble, Access) {
        tao::deprecated::Col<double> col {1.0, 2.0, 3.0};
        ASSERT_FLOAT_EQ(col(0), 1.0);
        ASSERT_FLOAT_EQ(col(1), 2.0);
        ASSERT_FLOAT_EQ(col(2), 3.0);
    }

    TEST(ColDouble, VectorSum) {
        tao::deprecated::Col<double> col1 {1.0, 2.0, 3.0};
        tao::deprecated::Col<double> col2 {100.0, 200.0, 300.0};
        tao::deprecated::Col<double> sum = col1 + col2;
        ASSERT_TRUE(sum == (tao::deprecated::Col<double>{101.0, 202.0, 303.0}));

        col1 += col2;
        ASSERT_TRUE(col1 == (tao::deprecated::Col<double>{101.0, 202.0, 303.0}));
    }

    TEST(ColDouble, VectorDiff) {
        tao::deprecated::Col<double> col1 {1.0, 2.0, 3.0};
        tao::deprecated::Col<double> col2 {100.0, 200.0, 300.0};
        tao::deprecated::Col<double> diff = col1 - col2;
        ASSERT_TRUE(diff == (tao::deprecated::Col<double>{-99.0, -198.0, -297.0}));

        col1 -= col2;
        ASSERT_TRUE(col1 == (tao::deprecated::Col<double>{-99.0, -198.0, -297.0}));
    }

    TEST(ColDouble, VectorMult) {
        tao::deprecated::Col<double> col1 {1.0, 2.0, 3.0};
        tao::deprecated::Col<double> col2 {100.0, 200.0, 300.0};
        tao::deprecated::Col<double> mult = col1 * col2;
        ASSERT_TRUE(mult == (tao::deprecated::Col<double>{100.0, 400.0, 900.0}));
        ASSERT_TRUE(mult == (col2*col1));

        col1 *= col2;
        ASSERT_TRUE(col1 == (tao::deprecated::Col<double>{100.0, 400.0, 900.0}));
    }

    TEST(ColDouble, VectorDiv) {
        tao::deprecated::Col<double> col1 {1.0, 2.0, 3.0};
        tao::deprecated::Col<double> col2 {100.0, 200.0, 300.0};
        tao::deprecated::Col<double> div = col1 / col2;
        ASSERT_TRUE(div == (tao::deprecated::Col<double>{1.0/100.0, 2.0/200.0, 3.0/300.0}));

        col1 /= col2;
        ASSERT_TRUE(col1 == (tao::deprecated::Col<double>{1.0/100.0, 2.0/200.0, 3.0/300.0}));
    }

    TEST(ColDouble, VectorDot) {
        tao::deprecated::Col<double> col1 {1.0, 2.0, 3.0};
        tao::deprecated::Col<double> col2 {100.0, 200.0, 300.0};
        double dotres = col1.dot(col2);
        ASSERT_FLOAT_EQ(dotres, 1400.0);
    }

    TEST(ColDouble, ScalarOps) {
        tao::deprecated::Col<double> col1 {2.0, 4.0, 6.0};
        ASSERT_TRUE((col1 / 2.0) == (tao::deprecated::Col<double>{1.0, 2.0, 3.0}));
        ASSERT_TRUE((2.0 / col1)  == (tao::deprecated::Col<double>{2.0/2.0, 2.0/4.0, 2.0/6.0}));
        ASSERT_TRUE((2.0 * col1) == (tao::deprecated::Col<double>{4.0, 8.0, 12.0}));
        ASSERT_TRUE((col1 * 2.0) == (tao::deprecated::Col<double>{4.0, 8.0, 12.0}));
        col1 /= 2.0;
        ASSERT_TRUE(col1 == (tao::deprecated::Col<double>{1.0, 2.0, 3.0}));
        col1 *= 2.0;
        ASSERT_TRUE(col1 == (tao::deprecated::Col<double>{2.0, 4.0, 6.0}));
    }

    TEST(ColDouble, Norm) {
        tao::deprecated::Col<double> col1 {2.0, 3.0, 5.0};
        ASSERT_FLOAT_EQ(col1.norm(), std::sqrt(38));
        tao::deprecated::Col<double> col2 {1.5, -5.0, 10.0};
        ASSERT_NEAR(col2.norm(), 11.2805, 0.0001);
        tao::deprecated::Col<double> col3 {0.0, 0.0, 0.0};
        ASSERT_FLOAT_EQ(col3.norm(), 0.0);
    }

    TEST(ColDouble, Unit) {
        tao::deprecated::Col<double> col1 {2.0, 3.0, 5.0};

        ASSERT_NE(col1.norm(), 1.0);

        auto col1unit = col1.unit().value();
        ASSERT_FLOAT_EQ(col1unit.norm(), 1.0);

        col1.unit(true);
        ASSERT_FLOAT_EQ(col1.norm(), 1.0);
    
        ASSERT_NEAR(col1(0), 0.324444, 0.0001);
        ASSERT_NEAR(col1(1), 0.4867, 0.0001);
        ASSERT_NEAR(col1(2), 0.8111, 0.0001);
    }

    TEST(ColDouble, Cross) {
        tao::deprecated::Col<double> col1 {1.0, 2.0, 3.0};
        tao::deprecated::Col<double> col2 {1.0, 5.0, 7.0};

        tao::deprecated::Col<double> across = tao::deprecated::cross(col1, col2);

        ASSERT_NEAR(across(0), -1.0, 0.0001);
        ASSERT_NEAR(across(1), -4.0, 0.0001);
        ASSERT_NEAR(across(2), 3.0, 0.0001);

        ASSERT_EQ(col1.dot(across), 0.0);
        ASSERT_EQ(col2.dot(across), 0.0);
    }
}
