#pragma once

#include <hayai/hayai.hpp>
#include "../fixtures.h"
#include "implementation.h"

BENCHMARK_P_F(SmallRandomGraphFixture, OpenMP, RUN_NUMBER, ITERATIONS, (int
        num_threads)) {
    runTest(num_threads, OpenMP::bellman_ford);
}

//BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, OpenMP, (1));
//BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, OpenMP, (2));
//BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, OpenMP, (4));
//BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, OpenMP, (8));
//BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, OpenMP, (16));

BENCHMARK_P_F(GreatRandomGraphFixture, OpenMP, RUN_NUMBER, ITERATIONS, (int
        num_threads)) {
    runTest(num_threads, OpenMP::bellman_ford);
}

BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, OpenMP, (1));

BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, OpenMP, (2));

BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, OpenMP, (4));

BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, OpenMP, (8));

BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, OpenMP, (16));
