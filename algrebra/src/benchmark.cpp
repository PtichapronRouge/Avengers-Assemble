/**@file	/data/Projets/Avengers-Assemble/algrebra/benchmark.cpp
 * @author	talos
 * @version	802
 * @date
 * 	Created:	12th May 2020
 * 	Last Update:	12th May 2020
 */

#include <chrono>
#include <utility>
#include <iostream>
#include <random>

#include "utils.hpp"

extern "C" int IntegerMatrixProduct_(int n, int* m1, int* m2, int* res);
extern "C" int NaiveIntegerMatrixProduct_(int n, int* A, int* B, int* C);
extern "C" int FloatMatrixProduct_(int n, float* A, float* B, float* C);
extern "C" int FloatDotProduct_(int n, float* A, float* x, float* y);
extern "C" int FloatPackedDotProduct_(int n, float* A, float* x, float* y);

std::random_device GLOBAL_ENGINE;

int main(int argc, char* argv[])
{
    const int n = (argc > 1 ? std::atoi(argv[1]) : 100);
    const unsigned int iterations = (argc > 2 ? std::atoi(argv[2]) : 100);

    const float mean = 0.0,
                sigma = 20.0;
    std::normal_distribution<float> dist(mean, sigma);
    std::vector<float> A(n*n),
                       B(n*n),
                       C(n*n, 0);
    random_matrix_init(n, n, &A[0], dist);
    random_matrix_init(n, n, &B[0], dist);

    auto runtime = [] (unsigned int iterations, auto&& func, auto&&... params)
    {
        const auto& start = std::chrono::high_resolution_clock::now();
        for(unsigned int i = 0; i < iterations; i++) {
            std::forward<decltype(func)>(func)
                    (std::forward<decltype(params)>(params)...);
        }
        const auto& stop = std::chrono::high_resolution_clock::now();
        auto total_duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
        //return float((total_duration/iterations).count());
        return float(total_duration.count());

    };

    std::cout << "FloatMatrixProduct_ (us): " << runtime(iterations, FloatMatrixProduct_, n, &A[0], &B[0], &C[0]) << std::endl;

    return 0;
}

