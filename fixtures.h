#pragma once

#include <hayai/hayai.hpp>
#include "graph.h"
#include "sequential/sequential.h"
#include "test_data.h"
#include <functional>

template<unsigned int graph_size>
class RandomGraphFixture : public ::hayai::Fixture {
public:
    void SetUp() override {
        graph = TestData<graph_size>::data[run];
        targetPath = new Path(graph_size);
        Sequential::bellman_ford(0, graph, targetPath);
        run++;
    }

    void TearDown() override {
        delete targetPath;
    }

    void runTest(int num_threads, const std::function<void(int, const Graph *, Path *)> &test) {
        auto &&path = new Path(graph->size);
        test(num_threads, graph, path);
        if (!(*path == *targetPath)) throw std::invalid_argument("result is incorrect");
        delete path;
    }

private:
    int run = 0;

    Graph *graph = nullptr;
    Path *targetPath = nullptr;
};


class SmallRandomGraphFixture : public RandomGraphFixture<SMALL_SIZE> {
};

class GreatRandomGraphFixture : public RandomGraphFixture<GREAT_SIZE> {
};