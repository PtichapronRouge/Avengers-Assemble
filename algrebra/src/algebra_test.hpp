#include <cxxtest/TestSuite.h>

#include "utils.hpp"

extern "C" int IntegerMatrixProduct_(int n, int* m1, int* m2, int* res);
extern "C" int NaiveIntegerMatrixProduct_(int n, int* A, int* B, int* C);
extern "C" int FloatMatrixProduct_(int n, float* A, float* B, float* C);
extern "C" int FloatDotProduct_(int n, float* A, float* x, float* y);
extern "C" int FloatPackedDotProduct_(int n, float* A, float* x, float* y);

std::random_device GLOBAL_ENGINE;

template <typename T>
void MatrixProductCpp(int n, T* A, T* B, T* res)
{
    // C function to compute the matrix product
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                res[n*i+j] += A[n*i+k] * B[n*k+j];
            }
        }
    }
}

class AlgebraTest : public CxxTest::TestSuite
{
    public:
        void testNaiveIntegerMatrixProd(void)
        {
            const int n(20);
            int A[n*n],
                B[n*n],
                c_res[n*n],
                asm_res[n*n];

            std::uniform_int_distribution<> dist(-50, 50);
            random_matrix_init(n, n, &A[0], dist);
            random_matrix_init(n, n, &B[0], dist);
            zero_matrix_init(n, n, &c_res[0]);
            zero_matrix_init(n, n, &asm_res[0]);

            MatrixProductCpp(n, A, B, c_res);
            // Assembly function to compute the matrix product
            NaiveIntegerMatrixProduct_(n, A, B, asm_res);
            // asm_res & c_res must be equal
            TS_ASSERT_SAME_DATA(asm_res, c_res, n*n);
        }

        void testIntegerMatrixProd(void)
        {
            const int n(20);
            int A[n*n],
                B[n*n],
                c_res[n*n],
                asm_res[n*n];

            std::uniform_int_distribution<> dist(-50, 50);
            random_matrix_init(n, n, &A[0], dist);
            random_matrix_init(n, n, &B[0], dist);
            zero_matrix_init(n, n, &c_res[0]);
            zero_matrix_init(n, n, &asm_res[0]);

            MatrixProductCpp(n, A, B, c_res);
            // Assembly function to compute the matrix product
            IntegerMatrixProduct_(n, A, B, asm_res);
            // asm_res & c_res must be equal
            TS_ASSERT_SAME_DATA(asm_res, c_res, n*n);
        }

        void testFloatMatrixProd(void)
        {
            const int n(20);
            float A[n*n],
                  B[n*n],
                  c_res[n*n],
                  asm_res[n*n];

            std::normal_distribution<float> dist(0, 50);
            random_matrix_init(n, n, &A[0], dist);
            random_matrix_init(n, n, &B[0], dist);
            zero_matrix_init(n, n, &c_res[0]);
            zero_matrix_init(n, n, &asm_res[0]);

            MatrixProductCpp<float>(n, A, B, c_res);
            // Assembly function to compute the matrix product
            FloatMatrixProduct_(n, A, B, asm_res);
            // asm_res & c_res must be equal
            TS_ASSERT_SAME_DATA(asm_res, c_res, n*n);
        }

        void testFloatDotProd(void)
        {
            const int n(20);
            float A[n*n],
                  x[n],
                  y_c[n],
                  y_asm[n];
            std::normal_distribution<float> dist(0, 50);
            random_matrix_init(n, n, &A[0], dist);
            random_matrix_init(n, 1, &x[0], dist);

            // C dot product
            for (int i = 0; i < n; i++) {
                y_c[i] = 0;
                y_asm[i] = 0;
                int row = n*i;
                for (int j = 0; j < n; j++) {
                    y_c[i] += A[row + j]*x[j];
                }
            }
            FloatPackedDotProduct_(n, A, x, y_asm);
            TS_ASSERT_SAME_DATA(y_asm, y_c, n);
        }
};

