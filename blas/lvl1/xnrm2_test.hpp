/**@file	/data/Projets/Avengers-Assemble/blas/lvl1/xnrm2_test.hpp
 * @author	talos
 * @version	802
 * @date
 * 	Created:	17th May 2020
 * 	Last Update:	17th May 2020
 */

#ifndef XNRM2_TEST_HPP
#define XNRM2_TEST_HPP

#include <cxxtest/TestSuite.h>

#include "../src/utils.hpp"

extern "C" float SNRM2_(int n, float* x, int incx);

class XNRM2Test : public CxxTest::TestSuite
{
public:
    void testSNRM2_multipleOf4(void)
    {
        const int n(30);
        alignas(16) float x[n];
        std::normal_distribution<float> dist(0, 50);
        random_matrix_init(n, 1, &x[0], dist);

        float asm_norm = SNRM2_(n, &x[0], 1);

        float ref_norm = 0.0;
        for (int i = 0; i < n; i++) {
            ref_norm += x[i]*x[i];
        }

        float tolerance = 1e-6;
        TS_ASSERT_DELTA((asm_norm - ref_norm)/ref_norm, 0.0, tolerance);
    }

};

#endif // XNRM2_TEST_HPP
