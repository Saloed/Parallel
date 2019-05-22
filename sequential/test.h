#pragma once

#include <hayai/hayai.hpp>
#include "../fixtures.h"
#include "sequential.h"


//BENCHMARK_F(SmallRandomGraphFixture, Sequential, RUN_NUMBER, 100) {
//runTest(0, Sequential::bellman_ford);
//}


BENCHMARK_F(GreatRandomGraphFixture, Sequential, RUN_NUMBER, ITERATIONS) {
    runTest(0, Sequential::bellman_ford);
}
