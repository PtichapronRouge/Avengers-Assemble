#include <cxxtest/TestSuite.h>

#include <vector>

extern "C" int MatrixProduct_(int n, int* m1, int* m2, int* res);

class AlgebraTest : public CxxTest::TestSuite
{
    public:
        void testIntegerMatrixProd(void)
        {
            const unsigned int n(5);
            int A[n*n],
                B[n*n],
                c_res[n*n],
                asm_res[n*n];
            for (uint i = 0; i < n; ++i) {
                for (uint j = 0; j < n; ++j) {
                    A[n*i+j] = i+j;
                    B[n*i+j] = i-j;
                    c_res[n*i+j] = 0;
                    asm_res[n*i+j] = 0;
                }
            }
            // C function to compute the matrix product
            for (size_t i = 0; i < n; i++) {
                for (size_t k = 0; k < n; k++) {
                    for (size_t j = 0; j < n; j++) {
                        c_res[n*i+j] += A[n*i+k] * B[n*k+j];
                    }
                }
            }
            // Assembly function to compute the matrix product
            MatrixProduct_(n, A, B, asm_res);
            // asm_res & c_res must be equal
            TS_ASSERT_SAME_DATA(asm_res, c_res, n);
        }

        void XtestFloatMatrixProd(void)
        {
            // not yet implemented
        }
};

