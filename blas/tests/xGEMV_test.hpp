/**@file	/data/Projets/Avengers-Assemble/blas/lvl2/xGEMV_test.hpp
 * @author	talos
 * @version	802
 * @date
 * 	Created:	11th Jun 2020
 * 	Last Update:	11th Jun 2020
 */

#ifndef XGEMV_TEST_HPP
#define XGEMV_TEST_HPP

#include "../src/utils.hpp"

extern "C" int SGEMV_(int m, int n,
                        float alpha, float* A,
                        float* x,
                        float beta, float* y);

class XGEMVTest : public CxxTest::TestSuite
{
public:
    static void c_sgemv(int m, int n,
                 float alpha, float* A,
                 float* x,
                 float beta, float* y,
                 float* res)
    {
        float sum;
        for (int i = 0; i < m; i++) {
            sum = 0.0;
            for (int j = 0; j < n; j++) {
                sum += A[n*i+j]*x[j];
            }
            res[i] = beta*y[i] + alpha*sum;
        }
    }

    void testSAXPY_simple(void)
    {
        const float alpha = 2.0,
                    beta = 3.0;
        const int n(20),
                  m(7);
        float A[m*n],
              x[n],
              y[m],
              c_y[m];

        std::normal_distribution<float> dist(0, 50);
        random_matrix_init(n, m, &A[0], dist);
        random_matrix_init(n, 1, &x[0], dist);
        random_matrix_init(m, 1, &y[0], dist);

        VectCmpParams params;
        params.n(m).y(y).c_y(c_y);

        testBlas(SGEMV_, c_sgemv, params,
                 m, n, alpha, A, x, beta, y);
    }
};

#endif // XGEMV_TEST_HPP
