#pragma once

#include <hayai/hayai.hpp>
#include "../fixtures.h"
#include "implementation.h"

BENCHMARK_P_F(SmallRandomGraphFixture, OpenMP, 10, 100, (int num_threads)) {
    auto &&graph = getGraph();
    auto &&path = OpenMP::bellman_ford(num_threads, graph);
    if (!(path == getPath())) throw std::invalid_argument( "result is incorrect" );
}

BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, OpenMP, (1));
BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, OpenMP, (2));
BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, OpenMP, (4));
BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, OpenMP, (8));
BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, OpenMP, (16));

BENCHMARK_P_F(GreatRandomGraphFixture, OpenMP, 10, 100, (int num_threads)) {
    auto &&graph = getGraph();
    auto &&path = OpenMP::bellman_ford(num_threads, graph);
    if (!(path == getPath())) throw std::invalid_argument( "result is incorrect" );
}

BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, OpenMP, (1));
BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, OpenMP, (2));
BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, OpenMP, (4));
BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, OpenMP, (8));
BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, OpenMP, (16));
