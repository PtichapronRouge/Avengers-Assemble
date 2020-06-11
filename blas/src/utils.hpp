/**@file	/data/Projets/Avengers-Assemble/algrebra/src/utils.hpp
 * @author	talos
 * @version	802
 * @date
 * 	Created:	14th May 2020
 * 	Last Update:	14th May 2020
 */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <random>
#include <utility>
#include <cxxtest/TestSuite.h>

extern std::random_device GLOBAL_ENGINE;

template <typename T, template<typename> class D>
void random_matrix_init(int n, int m, T* mat, D<T> dist)
{
    for (int i = 0, end = n*m; i < end; i++) {
        mat[i] = dist(GLOBAL_ENGINE);
    }
}

template <typename T>
void zero_matrix_init(int n, int m, T* mat)
{
    for (int i = 0, end = n*m; i < end; i++) {
        mat[i] = T();
    }
}

struct VectCmpParams
{
    VectCmpParams() : _ix(1), _iy(1), _tol(1e-6) {}

    int _n;
    int n() const {return _n;}
    VectCmpParams& n(int nn) {_n = nn; return *this;}

    float* _y;
    float* y() const {return _y;}
    VectCmpParams& y(float* yy) {_y = yy; return *this;}

    float* _c_y;
    float* c_y() const {return _c_y;}
    VectCmpParams& c_y(float* c_yy) {_c_y = c_yy; return *this;}

    int _ix;
    int incx() const {return _ix;}
    VectCmpParams& incx(int ix) {_ix = ix; return *this;}

    int _iy;
    int incy() const {return _iy;}
    VectCmpParams& incy(int iy) {_iy = iy; return *this;}

    float _tol;
    float tolerance() const {return _tol;}
    VectCmpParams& tolerance(float tol) {_tol = tol; return *this;}
};

void compareArrays(int n, float* x, int incx, float* y, int incy, float tolerance = 1e-6)
{
    auto square = [] (float a) {return a*a;};
    float ref_norm(0.0),
          asm_norm(0.0);
    for (int i = 0; i < n; i++) {
        asm_norm += square(x[i*incx]);
        ref_norm += square(y[i*incy]);
    }
    TS_ASSERT_DELTA((ref_norm - asm_norm)/ref_norm, 0.0, tolerance);
}

void compareArrays(const VectCmpParams& params)
{
    compareArrays(params.n(), params.y(), params.incx(), params.c_y(), params.incy(), params.tolerance());
}

template <typename F, typename G, typename ...Args>
void testBlas(F asm_blas, G c_blas, VectCmpParams params, Args... common_args)
{
    // Apply C function with additional param : tmp buffer to store result
    c_blas(common_args..., params.c_y());

    // Check return status of asm blas
    TS_ASSERT_EQUALS(asm_blas(common_args...), 0);

    // compare both resulting arrays
    compareArrays(params);
}

#endif // UTILS_HPP
