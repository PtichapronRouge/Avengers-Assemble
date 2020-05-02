#include <cxxtest/TestSuite.h>

extern "C" int MatrixProduct_(int n, int* m1, int* m2, int* res);
extern "C" int NaiveMatrixProduct_(int n, int* A, int* B, int* C);

void init_matrices(int n, int* A, int* B)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[n*i+j] = i+j;
            B[n*i+j] = i+j;
        }
    }
}

void erase_matrices(int n, int* C)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[n*i+j] = 0;
        }
    }
}

void MatrixProductCpp(int n, int* A, int* B, int* res)
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
            NaiveMatrixProduct_(n, A, B, asm_res);
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
            MatrixProduct_(n, A, B, asm_res);
            // asm_res & c_res must be equal
            TS_ASSERT_SAME_DATA(asm_res, c_res, n*n);
        }

        void XtestFloatMatrixProd(void)
        {
            // not yet implemented
        }
};

