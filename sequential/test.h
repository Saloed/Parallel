#pragma once

#include <hayai/hayai.hpp>
#include "../fixtures.h"
#include "sequential.h"


//BENCHMARK_F(SmallRandomGraphFixture, Sequential, 10, 100) {
//    auto &&graph = getGraph();
//    auto &&path = Sequential::bellman_ford(graph);
//    if (!(path == getPath())) throw std::invalid_argument( "result is incorrect" );
//}


BENCHMARK_F(GreatRandomGraphFixture, Sequential, 10, 10) {
    auto &&graph = getGraph();
    auto &&path = Sequential::bellman_ford(graph);
    if (!(path == getPath())) throw std::invalid_argument( "result is incorrect" );
}
