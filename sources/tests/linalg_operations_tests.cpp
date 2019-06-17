#include "gtest/gtest.h"
#include "tao/core.h"
#include <cmath>

namespace {

    TEST(LinalgOperations, CreationInitializer) {
        tao::Vec3<double> col {1.0, 2.0, 3.0};
        ASSERT_EQ(col.nrows(), 3);
        ASSERT_EQ(col.ncols(), 1);
    };

    TEST(LinalgOperations, Access) {
        tao::Vec3<double> col {1.0, 2.0, 3.0};
        ASSERT_FLOAT_EQ(col(0), 1.0);
        ASSERT_FLOAT_EQ(col(1), 2.0);
        ASSERT_FLOAT_EQ(col(2), 3.0);
    }

    TEST(LinalgOperations, VectorSum) {
        tao::Vec3<double> col1 {1.0, 2.0, 3.0};
        tao::Vec3<double> col2 {100.0, 200.0, 300.0};
        tao::Vec3<double> sum = col1 + col2;
        ASSERT_TRUE(sum == (tao::Vec3<double>{101.0, 202.0, 303.0}));

        col1 += col2;
        ASSERT_TRUE(col1 == (tao::Vec3<double>{101.0, 202.0, 303.0}));
    }

    TEST(LinalgOperations, VectorDiff) {
        tao::Vec3<double> col1 {1.0, 2.0, 3.0};
        tao::Vec3<double> col2 {100.0, 200.0, 300.0};
        tao::Vec3<double> diff = col1 - col2;
        ASSERT_TRUE(diff == (tao::Vec3<double>{-99.0, -198.0, -297.0}));

        col1 -= col2;
        ASSERT_TRUE(col1 == (tao::Vec3<double>{-99.0, -198.0, -297.0}));
    }

    TEST(LinalgOperations, VectorDiv) {
        tao::Vec3<double> col1 {1.0, 2.0, 3.0};
        tao::Vec3<double> col2 {100.0, 200.0, 300.0};
        tao::Vec3<double> div = col1 / col2;
        ASSERT_TRUE(div == (tao::Vec3<double>{1.0/100.0, 2.0/200.0, 3.0/300.0}));

        col1 /= col2;
        ASSERT_TRUE(col1 == (tao::Vec3<double>{1.0/100.0, 2.0/200.0, 3.0/300.0}));
    }

    TEST(LinalgOperations, VectorDot) {
        tao::Vec3<double> col1 {1.0, 2.0, 3.0};
        tao::Vec3<double> col2 {100.0, 200.0, 300.0};
        double dotres = tao::dot(col1, col2);
        ASSERT_FLOAT_EQ(dotres, 1400.0);
    }

    TEST(LinalgOperations, ScalarOps) {
        tao::Vec3<double> col1 {2.0, 4.0, 6.0};
        ASSERT_TRUE((col1 / 2.0) == (tao::Vec3<double>{1.0, 2.0, 3.0}));
        ASSERT_TRUE((2.0 / col1)  == (tao::Vec3<double>{2.0/2.0, 2.0/4.0, 2.0/6.0}));
        ASSERT_TRUE((2.0 * col1) == (tao::Vec3<double>{4.0, 8.0, 12.0}));
        ASSERT_TRUE((col1 * 2.0) == (tao::Vec3<double>{4.0, 8.0, 12.0}));
        col1 /= 2.0;
        ASSERT_TRUE(col1 == (tao::Vec3<double>{1.0, 2.0, 3.0}));
        col1 *= 2.0;
        ASSERT_TRUE(col1 == (tao::Vec3<double>{2.0, 4.0, 6.0}));
    }

    TEST(LinalgOperations, Norm) {
        tao::Vec3<double> col1 {2.0, 3.0, 5.0};
        ASSERT_FLOAT_EQ(tao::norm(col1), std::sqrt(38));
        tao::Vec3<double> col2 {1.5, -5.0, 10.0};
        ASSERT_NEAR(tao::norm(col2), 11.2805, 0.0001);
        tao::Vec3<double> col3 {0.0, 0.0, 0.0};
        ASSERT_FLOAT_EQ(tao::norm(col3), 0.0);
    }

    TEST(LinalgOperations, Unit) {
        tao::Vec3<double> col1 {2.0, 3.0, 5.0};

        ASSERT_NE(tao::norm(col1), 1.0);

        auto col1unit = tao::unitize(col1);
        ASSERT_FLOAT_EQ(tao::norm(col1unit), 1.0);

        ASSERT_NEAR(col1unit(0), 0.324444, 0.0001);
        ASSERT_NEAR(col1unit(1), 0.4867, 0.0001);
        ASSERT_NEAR(col1unit(2), 0.8111, 0.0001);
    }

    TEST(LinalgOperations, Cross) {
        tao::Vec3<double> col1 {1.0, 2.0, 3.0};
        tao::Vec3<double> col2 {1.0, 5.0, 7.0};

        tao::Vec3<double> across = tao::cross(col1, col2);

        ASSERT_NEAR(across(0), -1.0, 0.0001);
        ASSERT_NEAR(across(1), -4.0, 0.0001);
        ASSERT_NEAR(across(2), 3.0, 0.0001);

        ASSERT_EQ(tao::dot(col1,across), 0.0);
        ASSERT_EQ(tao::dot(col2, across), 0.0);
    }

    TEST(LinalgOperations, Det4x4) {
        tao::Mat<float, 4, 4> mat1 = {
            {5.0, 3.0, -2.0, -6.0},
            {1.0, 2.0, 7.0, 4.0},
            {-10.0, 3.0, 5.0, -3.0},
            {-4.0, 2.0, 6.0, 1.0},
        };   

        ASSERT_EQ(tao::det(mat1), 174.0);
    }


    TEST(LinalgOperations, Inv4x4) {
         tao::Mat<float, 4, 4> mat1 = {
            {5.0, 3.0, -2.0, -6.0},
            {1.0, 2.0, 7.0, 4.0},
            {-10.0, 3.0, 5.0, -3.0},
            {-4.0, 2.0, 6.0, 1.0},
        };

        tao::Mat<float, 4, 4> mat1inv = {
            {15.0/174.0, -39.0/174.0, -51.0/174.0, 93.0/174.0},
            {-17/174.0, 311/174.0, 255/174.0, -581/174.0},
            {21/174.0, -159/174.0, -141/174.0, 339/174.0},
            {-32/174.0, 176/174.0, 132/174.0, -326/174.0},
        };

        ASSERT_TRUE(tao::inverse(mat1).eq(mat1inv, 0.0001));
    }
}
