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

std::random_device GLOBAL_ENGINE;

class XAXPYTest : public CxxTest::TestSuite
{
public:
    void testSAXPY_multipleOf4(void)
    {
        const int n(20);
        float   x[n],
                y[n],
                c_y[n];
        float alpha = 1;
        std::normal_distribution<float> dist(0, 50);

        random_matrix_init(n, 1, &x[0], dist);
        random_matrix_init(n, 1, &y[0], dist);

        for(int i = 0; i < n; i++){
            c_y[i] = alpha*x[i] + y[i];
        }
        int status = SAXPY_(n, alpha, x, 1, y, 1);
        std::cout << "\n";

        TS_ASSERT_EQUALS(status, 0);
        TS_ASSERT_SAME_DATA(y, c_y, n*sizeof(float));
    }

    void testSAXPY_notMultipleOf4(void)
    {
        const int n(23);
        float   x[n],
                y[n],
                c_y[n];
        float alpha = 1;
        std::normal_distribution<float> dist(0, 50);

        random_matrix_init(n, 1, &x[0], dist);
        random_matrix_init(n, 1, &y[0], dist);

        for(int i = 0; i < n; i++){
            c_y[i] = alpha*x[i] + y[i];
        }
        int status = SAXPY_(n, alpha, x, 1, y, 1);
        std::cout << "\n";

        TS_ASSERT_EQUALS(status, 0);
        TS_ASSERT_SAME_DATA(y, c_y, n*sizeof(float));
    }

    void testSAXPY_lessThan4Elems(void)
    {
        const int n(3);
        alignas(16) float   x[n],
                            y[n],
                            c_y[n];
        float alpha = 1;
        std::normal_distribution<float> dist(0, 50);

        random_matrix_init(n, 1, &x[0], dist);
        random_matrix_init(n, 1, &y[0], dist);

        for(int i = 0; i < n; i++){
            c_y[i] = alpha*x[i] + y[i];
        }
        int status = SAXPY_(n, alpha, x, 1, y, 1);
        std::cout << "\n";

        TS_ASSERT_EQUALS(status, 0);
        TS_ASSERT_SAME_DATA(y, c_y, n*sizeof(float));
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
};

#endif // XAXPY_TEST_HPP
