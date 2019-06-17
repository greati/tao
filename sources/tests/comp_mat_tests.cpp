#include "gtest/gtest.h"
#include "tao/linalg/Mat.h"

namespace {

    TEST(CompMatFloat, CreationInitializer) {
        tao::Mat<float, 3, 2> mat {
            {1.0, 2.0},
            {3.0, 4.0},
            {5.0, 6.0}
        };

        ASSERT_EQ(mat.nrows(), 3);
        ASSERT_EQ(mat.ncols(), 2);
    };

    TEST(CompMatFloat, InitializerError) {
        try {
            tao::Mat<float, 3, 2> mat2 {
                {1.0, 2.0},
                {3.0},
                {5.0, 6.0}
            };
            FAIL();
        } catch (std::invalid_argument& e1) {
            try {
                tao::Mat<float, 2, 2> mat2 {
                    {1.0, 2.0},
                    {3.0},
                };
                FAIL();
            } catch(std::invalid_argument& e2) {
            
            }
        }
    };

    /*
    TEST(CompMatFloat, InitializerColsEmptyError) {
        try {
            tao::Mat<float, 1, 1> mat2 ({
                {}, {}
            });
            FAIL();
        } catch (std::invalid_argument& e) {
            SUCCEED();
        }
    };*/

    TEST(CompMatFloat, AccessOperatorSuccess0) {
        tao::Mat<double, 2, 4> mat {
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

    TEST(CompMatFloat, AccessOperatorSuccess1) {
        tao::Mat<float, 2, 2> mat {
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

    TEST(CompMatFloat, AccessOperatorSuccess2) {
        tao::Mat<float, 2, 1> mat {
            {
                {{1.0}},
                {{3.0}}
            }
        };
        ASSERT_EQ(mat.nrows(), 2);
        ASSERT_EQ(mat.ncols(), 1);
        ASSERT_FLOAT_EQ(mat(0, 0), 1.0);
        ASSERT_FLOAT_EQ(mat(1, 0), 3.0);
    }

    TEST(CompMatFloat, AccessOperatorSuccess3) {
        tao::Mat<float, 1, 2> mat {
            {1.0, 3.0}
        };
        ASSERT_EQ(mat.nrows(), 1);
        ASSERT_EQ(mat.ncols(), 2);
        ASSERT_FLOAT_EQ(mat(0, 0), 1.0);
        ASSERT_FLOAT_EQ(mat(0, 1), 3.0);
    }

    TEST(CompMatFloat, AccessOperatorSuccess4) {
        tao::Mat<float, 1, 1> mat {
            {
                {1.0}
            }
        };
        ASSERT_EQ(mat.nrows(), 1);
        ASSERT_EQ(mat.ncols(), 1);
        ASSERT_FLOAT_EQ(mat(0, 0), 1.0);
    }

    TEST(CompMatFloat, AccessOperatorFailure0) {
        tao::Mat<float, 2, 4> mat {
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

    TEST(CompMatFloat, SetValue) {
        tao::Mat<float, 2, 4> mat {
            {1.0, 2.0, 3.0, 4.0},
            {3.0, 4.0, 10.0, 20.0}
        };
        ASSERT_FLOAT_EQ(mat(0, 0), 1.0);
        mat(0, 0) = 100.0;
        ASSERT_FLOAT_EQ(mat(0, 0), 100.0);
        mat(0, 0) = 30.0;
        ASSERT_FLOAT_EQ(mat(0, 0), 30.0);
        mat(1, 3) = 1231.0;
        ASSERT_FLOAT_EQ(mat(1, 3), 1231.0);
    }

    TEST(CompMatFloat, ElementWiseOperations) {
        tao::Mat<float, 2, 2> mat1 {
            {1.0, 2.0},
            {3.0, 4.0}
        }; 

        tao::Mat<float, 2, 2> mat2 {
            {5.0, 6.0},
            {7.0, 8.0}
        };

        tao::Mat<float, 2, 2> matdiv {
            {1.0/5.0, 2.0/6.0},
            {3.0/7.0, 4.0/8.0}
        };

        tao::Mat<float, 2, 2> matsum {
            {6.0, 8.0},
            {10.0, 12.0}
        };

        tao::Mat<float, 2, 2> matsub {
            {-4.0, -4.0},
            {-4.0, -4.0}
        };

        ASSERT_TRUE(mat1 + mat2 == matsum);
        ASSERT_TRUE((mat1 - mat2) == matsub);
        ASSERT_TRUE((mat1 / mat2) == matdiv);
        ASSERT_TRUE(-matsum == (tao::Mat<float, 2, 2>{{-6.0, -8.0},{-10.0, -12.0}}));
        ASSERT_TRUE(-matsub == (tao::Mat<float, 2, 2>{{4.0, 4.0},{4.0, 4.0}}));
    }

    TEST(CompMatFloat, ElementWiseOperationsAssignment) {
        tao::Mat<float, 2, 2> mat1 {
            {1.0, 2.0},
            {3.0, 4.0}
        }; 

        tao::Mat<float, 2, 2> mat2 {
            {5.0, 6.0},
            {7.0, 8.0}
        };

        auto matd1 = mat1;
        auto matd2 = mat2;

        tao::Mat<float, 2, 2> matsum {
            {6.0, 8.0},
            {10.0, 12.0}
        };

        mat1 += mat2;
        ASSERT_TRUE(mat1 == matsum);

        tao::Mat<float, 2, 2> matsub {
            {-4.0, -4.0},
            {-4.0, -4.0}
        };

        mat1 -= mat2;
        ASSERT_TRUE(mat1 == (matsum - mat2));

        tao::Mat<float, 2, 2> matdiv {
            {1.0/5.0, 2.0/6.0},
            {3.0/7.0, 4.0/8.0}
        };
        matd1 /= matd2;
        ASSERT_TRUE(matd1 == (matdiv));

    }

    TEST(CompMatFloat, MatrixMultiplication) {
        tao::Mat<float, 2, 2> mat1 {
            {
                {1.0, 2.0},
                {3.0, 4.0}
            }
        }; 

        tao::Mat<float, 2, 2> mat2 {
            {
                {5.0, 6.0},
                {7.0, 8.0}
            }
        };

        tao::Mat<float, 2, 3> mat3 {
            {
                {5.0, 6.0, 10.0},
                {7.0, 8.0, 11.0}
            }
        };

        ASSERT_TRUE((mat1 * mat2) == (tao::Mat<float, 2, 2>{{{19.0, 22.0},{43.0, 50.0}}}));
        ASSERT_TRUE((mat1 * mat3) == (tao::Mat<float, 2, 3>{
                        {
                            {19.0, 22.0, 32.0}, 
                            {43.0, 50.0, 74.0}
                        }
                    }));
    }

    TEST(CompMatFloat, ScalarMult) {
        tao::Mat<float, 2, 3> mat = {
            {10.0, 20.0, 4.0},
            {5.0, 10.0, 3.0}
        };

        ASSERT_TRUE((2.0f * mat) == (tao::Mat<float, 2, 3>{{20.0, 40.0, 8.0}, {10.0, 20.0, 6.0}}));
        ASSERT_TRUE((mat * 2.0f) == (tao::Mat<float, 2, 3>{{20.0, 40.0, 8.0}, {10.0, 20.0, 6.0}}));

        mat *= 2.0;
        ASSERT_TRUE(mat == (tao::Mat<float, 2, 3>{{20.0, 40.0, 8.0}, {10.0, 20.0, 6.0}}));
    }

    TEST(CompMatFloat, ScalarDiv) {
        tao::Mat<float, 2, 3> mat = {
            {10.0, 20.0, 4.0},
            {5.0, 10.0, 3.0}
        };

        ASSERT_TRUE((2.0f / mat) == (tao::Mat<float, 2, 3>{
                    {2.0/10.0, 2.0/20.0, 2.0/4.0}, 
                    {2.0/5.0, 2.0/10.0, 2.0/3.0}})
                );
        ASSERT_TRUE((mat / 2.0f) == (tao::Mat<float, 2, 3>{{5.0, 10.0, 2.0}, {5.0/2.0, 5.0, 3.0/2.0}}));

        mat /= 2.0f;
        ASSERT_TRUE(mat == (tao::Mat<float, 2, 3>{{5.0, 10.0, 2.0}, {5.0/2.0, 5.0, 3.0/2.0}}));
    }

    TEST(CompMatFloat, FloatingEq) {
        tao::Mat<float, 2, 3> mat1 = {
            {10.0001, 20.0, 4.0},
            {5.0, 10.0, 3.0}
        };
    
        tao::Mat<float, 2, 3> mat2 = {
            {10.000001, 20.0, 4.0},
            {5.0, 10.0, 3.0}
        };

        ASSERT_TRUE(mat1.eq(mat2, 0.0001));
    }

};
