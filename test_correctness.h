#pragma once

#include "fixtures.h"
#include "sequential/sequential.h"
#include "openmp_bf/implementation.h"

bool test_omp() {
    SmallRandomGraphFixture fixture;
    fixture.SetUp();
    auto &&graph = fixture.getGraph();
    auto &&path1 = Sequential::bellman_ford(graph);
    auto &&path2 = OpenMP::bellman_ford < 8>(graph);
    return path1 == path2;
}