#include "gtest/gtest.h"
#include "linear_algebra/Row.h"

namespace {

    TEST(RowDouble, CreationInitializer) {
        tao::Row<double> row {1.0, 2.0, 3.0};
        ASSERT_EQ(row.nrows(), 1);
        ASSERT_EQ(row.ncols(), 3);
    };

    TEST(RowDouble, Access) {
        tao::Row<double> row {1.0, 2.0, 3.0};
        ASSERT_FLOAT_EQ(row(0), 1.0);
        ASSERT_FLOAT_EQ(row(1), 2.0);
        ASSERT_FLOAT_EQ(row(2), 3.0);
    }
}
