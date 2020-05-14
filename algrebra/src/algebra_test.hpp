#include <cxxtest/TestSuite.h>

extern "C" int IntegerMatrixProduct_(int n, int* m1, int* m2, int* res);
extern "C" int NaiveIntegerMatrixProduct_(int n, int* A, int* B, int* C);
extern "C" int FloatMatrixProduct_(int n, float* A, float* B, float* C);
extern "C" int FloatDotProduct_(int n, float* A, float* x, float* y);
extern "C" int FloatPackedDotProduct_(int n, float* A, float* x, float* y);


template <typename T>
void init_matrices(int n, T* A, T* B)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[n*i+j] = static_cast<T>(i+j);
            B[n*i+j] = static_cast<T>(i-j);
        }
    }
}

template <typename T>
void erase_matrices(int n, T* C)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[n*i+j] = 0;
        }
    }
}

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

            init_matrices(n, A, B);

            erase_matrices(n, c_res);
            MatrixProductCpp(n, A, B, c_res);
            // Assembly function to compute the matrix product
            erase_matrices(n, asm_res);
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

            init_matrices(n, A, B);

            erase_matrices(n, c_res);
            MatrixProductCpp(n, A, B, c_res);
            // Assembly function to compute the matrix product
            erase_matrices(n, asm_res);
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

            init_matrices<float>(n, A, B);

            erase_matrices<float>(n, c_res);
            MatrixProductCpp<float>(n, A, B, c_res);
            // Assembly function to compute the matrix product
            erase_matrices(n, asm_res);
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
                  for (int i = 0; i < n; i++) {
                      x[i] = i;
                      for (int j = 0; j < n; j++) {
                          A[n*i+j] = i+j;
                      }
                  }

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

