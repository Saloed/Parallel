#pragma once

#include <hayai/hayai.hpp>
#include "../fixtures.h"
#include "implementation.h"

BENCHMARK_P_F(SmallRandomGraphFixture, Pthread, RUN_NUMBER, ITERATIONS, (int
        num_threads)) {
    runTest(num_threads, Pthread::bellman_ford);

}

//BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, Pthread, (1));
//BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, Pthread, (2));
//BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, Pthread, (4));
//BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, Pthread, (8));
//BENCHMARK_P_INSTANCE(SmallRandomGraphFixture, Pthread, (16));

BENCHMARK_P_F(GreatRandomGraphFixture, Pthread, RUN_NUMBER, ITERATIONS, (int
        num_threads)) {
    runTest(num_threads, Pthread::bellman_ford);
}

BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, Pthread, (1));
BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, Pthread, (2));
BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, Pthread, (4));
BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, Pthread, (8));
BENCHMARK_P_INSTANCE(GreatRandomGraphFixture, Pthread, (16));
