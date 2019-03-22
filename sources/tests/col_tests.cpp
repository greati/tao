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
}
