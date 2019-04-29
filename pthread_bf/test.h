#pragma once

#include <hayai/hayai.hpp>
#include "../fixtures.h"
#include "implementation.h"

BENCHMARK_P_F(SmallRandomGraphFixture, Pthread, 10, 100, (int num_threads)) {
    auto &&graph = getGraph();
    auto &&path = Pthread::bellman_ford(num_threads, graph);
    if (!(path == getPath())) {
        std::cout << path.diff(getPath());
        throw std::invalid_argument("result is incorrect");
    }
}

BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, Pthread, (1));
BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, Pthread, (2));
BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, Pthread, (4));
BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, Pthread, (8));
BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, Pthread, (16));

BENCHMARK_P_F(GreatRandomGraphFixture, Pthread, 10, 100, (int num_threads)) {
    auto &&graph = getGraph();
    auto &&path = Pthread::bellman_ford(num_threads, graph);
    if (!(path == getPath())) {
        std::cout << path.diff(getPath());
        throw std::invalid_argument("result is incorrect");
    }
}

BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, Pthread, (1));
BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, Pthread, (2));
BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, Pthread, (4));
BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, Pthread, (8));
BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, Pthread, (16));
