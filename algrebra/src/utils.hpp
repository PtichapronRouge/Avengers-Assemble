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

#endif // UTILS_HPP
