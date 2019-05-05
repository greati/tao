#include "gtest/gtest.h"
#include "tao/linalg/dyn/Row.h"

namespace {

    TEST(RowDouble, CreationInitializer) {
        tao::deprecated::Row<double> row {1.0, 2.0, 3.0};
        ASSERT_EQ(row.nrows(), 1);
        ASSERT_EQ(row.ncols(), 3);
    };

    TEST(RowDouble, Access) {
        tao::deprecated::Row<double> row {1.0, 2.0, 3.0};
        ASSERT_FLOAT_EQ(row(0), 1.0);
        ASSERT_FLOAT_EQ(row(1), 2.0);
        ASSERT_FLOAT_EQ(row(2), 3.0);
    }

    TEST(RowDouble, VectorSum) {
        tao::deprecated::Row<double> row1 {1.0, 2.0, 3.0};
        tao::deprecated::Row<double> row2 {100.0, 200.0, 300.0};
        tao::deprecated::Row<double> sum = row1 + row2;
        ASSERT_TRUE(sum == (tao::deprecated::Row<double>{101.0, 202.0, 303.0}));
    }

    TEST(RowDouble, VectorDot) {
        tao::deprecated::Row<double> row1 {1.0, 2.0, 3.0};
        tao::deprecated::Row<double> row2 {100.0, 200.0, 300.0};
        double dotres = row1.dot(row2);
        ASSERT_FLOAT_EQ(dotres, 1400.0);
    }
}
