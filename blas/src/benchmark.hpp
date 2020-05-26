/**@file	/data/Projets/Avengers-Assemble/blas/src/benchmark.hpp
 * @author	talos
 * @version	802
 * @date
 * 	Created:	26th May 2020
 * 	Last Update:	26th May 2020
 */

#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <chrono>
#include <utility>

template <typename F, typename ...Args>
float runtime(unsigned int iterations, F func, Args&&...args)
{
    const auto start = std::chrono::high_resolution_clock::now();

    for (unsigned int i = 0; i < iterations; i++) {
        func(std::forward<Args>(args)...);
    }

    const auto& stop = std::chrono::high_resolution_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);

    return float(total_duration.count())/iterations;
}

#endif // BENCHMARK_HPP
