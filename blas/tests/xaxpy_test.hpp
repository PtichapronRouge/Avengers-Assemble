/**@file	/data/Projets/Avengers-Assemble/blas/lvl1/xaxpy_test.hpp
 * @author	talos
 * @version	802
 * @date
 * 	Created:	16th May 2020
 * 	Last Update:	16th May 2020
 */

#ifndef XAXPY_TEST_HPP
#define XAXPY_TEST_HPP

#include <cxxtest/TestSuite.h>
#include <iostream>

#include "../src/utils.hpp"

extern "C" int SAXPY_(int n, float alpha, float* x, int sx, float* y, int sy);

class XAXPYTest : public CxxTest::TestSuite
{
public:
    static void c_saxpy(int n, float alpha, float* x, int sx, float* y, int sy, float* res)
    {
        for (int i = 0; i < n; i++) {
            res[i] = alpha * x[i*sx] + y[i*sy];
        }
    }

    void testSAXPY_multipleOf4(void)
    {
        const float alpha = 1.0;
        const int n(20);
        float   x[n],
                y[n],
                c_y[n];

        std::normal_distribution<float> dist(0, 50);
        random_matrix_init(n, 1, &x[0], dist);
        random_matrix_init(n, 1, &y[0], dist);

        VectCmpParams params;
        params.n(n).y(y).c_y(c_y);

        testBlas(SAXPY_, c_saxpy, params,
                 n, alpha, x, 1, y, 1);
    }

    void testSAXPY_notMultipleOf4(void)
    {
        const float alpha = 3.0;
        const int n(23);
        alignas(16) float   x[n],
                            y[n],
                            c_y[n];

        std::normal_distribution<float> dist(0, 50);
        random_matrix_init(n, 1, &x[0], dist);
        random_matrix_init(n, 1, &y[0], dist);

        VectCmpParams params;
        params.n(n).y(y).c_y(c_y);

        testBlas(SAXPY_, c_saxpy, params,
                 n, alpha, x, 1, y, 1);
    }

    void testSAXPY_lessThan4Elems(void)
    {
        const float alpha = 1;
        const int n(3);
        alignas(16) float   x[n],
                            y[n],
                            c_y[n];

        std::normal_distribution<float> dist(0, 50);
        random_matrix_init(n, 1, &x[0], dist);
        random_matrix_init(n, 1, &y[0], dist);

        VectCmpParams params;
        params.n(n).y(y).c_y(c_y);

        testBlas(SAXPY_, c_saxpy, params,
                 n, alpha, x, 1, y, 1);
    }

    void testSAXPY_invalidSize(void)
    {
        // test return type when size param is 0
        int status_0 = SAXPY_(0, 1.0, NULL, 1, NULL, 1);
        TS_ASSERT_EQUALS(status_0, 1);

        // test return type when size param is negative
        int status_m1 = SAXPY_(-1, 1.0, NULL, 1, NULL, 1);
        TS_ASSERT_EQUALS(status_m1, 1);
    }

    void testSAXPY_notAligned(void)
    {
        const int n(20);
        alignas(16) float x[n];

        // test return type when x aligned on 16.k + 3
        int nalign_x_3 = SAXPY_(n-3, 1.0, &x[0]+3, 1, &x[0], 1);
        TS_ASSERT_EQUALS(nalign_x_3, 2);

        // test return type when y aligned on 16.k + 3
        int nalign_y_3 = SAXPY_(n-3, 1.0, &x[0], 1, &x[0]+3, 1);
        TS_ASSERT_EQUALS(nalign_y_3, 2);
    }

    void testSAXPY_strided(void)
    {
        const float alpha = 1;
        const int n(23);
        const int incx = 2,
                  incy = 3;

        const int XSIZE = n*incx,
                  YSIZE = n*incy;
        float   x[XSIZE],
                y[YSIZE],
                c_y[YSIZE];

        std::normal_distribution<float> dist(0, 50);
        random_matrix_init(XSIZE, 1, &x[0], dist);
        random_matrix_init(YSIZE, 1, &y[0], dist);

        VectCmpParams params;
        params.n(n).y(y).c_y(c_y);

        testBlas(SAXPY_, c_saxpy, params,
                 n, alpha, x, 1, y, 1);
    }
};

#endif // XAXPY_TEST_HPP
