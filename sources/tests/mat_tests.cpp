#include "gtest/gtest.h"
#include "linalg/Mat.h"

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
            tao::Mat<double> mat2 {{}};
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

    TEST(MatDouble, SetValue) {
        tao::Mat<double> mat {
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


    TEST(MatDouble, ElementWiseOperations) {
        tao::Mat<double> mat1 {
            {1.0, 2.0},
            {3.0, 4.0}
        }; 

        tao::Mat<double> mat2 {
            {5.0, 6.0},
            {7.0, 8.0}
        };

        tao::Mat<double> matdiv {
            {1.0/5.0, 2.0/6.0},
            {3.0/7.0, 4.0/8.0}
        };

        tao::Mat<double> matsum {
            {6.0, 8.0},
            {10.0, 12.0}
        };

        tao::Mat<double> matsub {
            {-4.0, -4.0},
            {-4.0, -4.0}
        };

        ASSERT_TRUE(mat1 + mat2 == matsum);
        ASSERT_TRUE((mat1 - mat2) == matsub);
        ASSERT_TRUE((mat1 / mat2) == matdiv);
        ASSERT_TRUE(-matsum == (tao::Mat<double>{{-6.0, -8.0},{-10.0, -12.0}}));
        ASSERT_TRUE(-matsub == (tao::Mat<double>{{4.0, 4.0},{4.0, 4.0}}));
    }

    TEST(MatDouble, ElementWiseOperationsAssignment) {
        tao::Mat<double> mat1 {
            {1.0, 2.0},
            {3.0, 4.0}
        }; 

        tao::Mat<double> mat2 {
            {5.0, 6.0},
            {7.0, 8.0}
        };

        auto matd1 = mat1;
        auto matd2 = mat2;

        tao::Mat<double> matsum {
            {6.0, 8.0},
            {10.0, 12.0}
        };

        mat1 += mat2;
        ASSERT_TRUE(mat1 == matsum);

        tao::Mat<double> matsub {
            {-4.0, -4.0},
            {-4.0, -4.0}
        };

        mat1 -= mat2;
        ASSERT_TRUE(mat1 == (matsum - mat2));

        tao::Mat<double> matdiv {
            {1.0/5.0, 2.0/6.0},
            {3.0/7.0, 4.0/8.0}
        };
        matd1 /= matd2;
        ASSERT_TRUE(matd1 == (matdiv));

    }


    TEST(MatDouble, MatrixMultiplicationError) {
        tao::Mat<double> mat1 {
            {1.0},
            {3.0}
        }; 

        tao::Mat<double> mat2 {
            {5.0, 6.0},
            {7.0, 8.0}
        };   

        tao::Mat<double> mat3 {
            {1.0, 5.0} 
        };
    
        ASSERT_THROW(mat1 * mat2, std::invalid_argument);    
        ASSERT_THROW(mat2 * mat3, std::invalid_argument);    
    }

    TEST(MatDouble, MatrixMultiplication) {
        tao::Mat<double> mat1 {
            {1.0, 2.0},
            {3.0, 4.0}
        }; 

        tao::Mat<double> mat2 {
            {5.0, 6.0},
            {7.0, 8.0}
        };

        tao::Mat<double> mat3 {
            {5.0, 6.0, 10.0},
            {7.0, 8.0, 11.0}
        };

        ASSERT_TRUE((mat1 * mat2) == (tao::Mat<double>{{19.0, 22.0},{43.0, 50.0}}));
        ASSERT_TRUE((mat1 * mat3) == (tao::Mat<double>{{19.0, 22.0, 32.0}, {43.0, 50.0, 74.0}}));
    }

    TEST(MatDouble, ScalarMult) {
        tao::Mat<double> mat = {
            {10.0, 20.0, 4.0},
            {5.0, 10.0, 3.0}
        };

        ASSERT_TRUE((2.0 * mat) == (tao::Mat<double>{{20.0, 40.0, 8.0}, {10.0, 20.0, 6.0}}));
        ASSERT_TRUE((mat * 2.0) == (tao::Mat<double>{{20.0, 40.0, 8.0}, {10.0, 20.0, 6.0}}));

        mat *= 2.0;
        ASSERT_TRUE(mat == (tao::Mat<double>{{20.0, 40.0, 8.0}, {10.0, 20.0, 6.0}}));
    }

    TEST(MatDouble, ScalarDiv) {
        tao::Mat<double> mat = {
            {10.0, 20.0, 4.0},
            {5.0, 10.0, 3.0}
        };

        ASSERT_TRUE((2.0 / mat) == (tao::Mat<double>{
                    {2.0/10.0, 2.0/20.0, 2.0/4.0}, 
                    {2.0/5.0, 2.0/10.0, 2.0/3.0}})
                );
        ASSERT_TRUE((mat / 2.0) == (tao::Mat<double>{{5.0, 10.0, 2.0}, {5.0/2.0, 5.0, 3.0/2.0}}));

        mat /= 2.0;
        ASSERT_TRUE(mat == (tao::Mat<double>{{5.0, 10.0, 2.0}, {5.0/2.0, 5.0, 3.0/2.0}}));
    }

    TEST(MatDouble, FloatingEq) {
        tao::Mat<double> mat1 = {
            {10.0001, 20.0, 4.0},
            {5.0, 10.0, 3.0}
        };
    
        tao::Mat<double> mat2 = {
            {10.000001, 20.0, 4.0},
            {5.0, 10.0, 3.0}
        };

        ASSERT_TRUE(mat1.eq(mat2, 0.0001));
    }

};
