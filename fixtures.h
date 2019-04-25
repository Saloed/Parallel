#pragma once

#include <hayai/hayai.hpp>
#include "graph.h"
#include "sequential/sequential.h"


template<unsigned int graph_size>
class RandomGraphFixture : public ::hayai::Fixture {
public:
    void SetUp() override {
        graph = new Graph(graph_size);
        fillGraphRandomly();
        targetPath = new Path(Sequential::bellman_ford(*graph));
    }

    void TearDown() override {
        delete graph;
    }

    Graph getGraph() const {
        return *graph;
    }

    Path getPath() const {
        return *targetPath;
    }

private:

    void fillGraphRandomly() {
        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(1, 100000);
        for (auto i = 0; i < graph_size; i++) {
            for (auto j = 0; j < graph_size; j++) {
                graph->addEdge(i, j, uniform_dist(e1));
            }
        }
    }

    Graph *graph = nullptr;
    Path *targetPath = nullptr;
};


class SmallRandomGraphFixture : public RandomGraphFixture<10> {
};

class GreatRandomGraphFixture : public RandomGraphFixture<100> {
};