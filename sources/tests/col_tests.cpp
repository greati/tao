#include "gtest/gtest.h"
#include "linear_algebra/Col.h"

namespace {

    TEST(ColDouble, CreationInitializer) {
        tao::Col<double> col {1.0, 2.0, 3.0};
        ASSERT_EQ(col.nrows(), 3);
        ASSERT_EQ(col.ncols(), 1);
    };

    TEST(ColDouble, Access) {
        tao::Col<double> col {1.0, 2.0, 3.0};
        ASSERT_FLOAT_EQ(col(0), 1.0);
        ASSERT_FLOAT_EQ(col(1), 2.0);
        ASSERT_FLOAT_EQ(col(2), 3.0);
    }

    TEST(ColDouble, VectorSum) {
        tao::Col<double> col1 {1.0, 2.0, 3.0};
        tao::Col<double> col2 {100.0, 200.0, 300.0};
        tao::Col<double> sum = col1 + col2;
        ASSERT_TRUE(sum == (tao::Col<double>{101.0, 202.0, 303.0}));
    }
}