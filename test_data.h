#pragma once

#include <random>
#include "graph.h"

# define RUN_NUMBER 10
# define ITERATIONS 10
# define SMALL_SIZE 10
# define GREAT_SIZE 500

template<int graph_size>
class TestData {
public:
    static std::vector<Graph *> data;

    static void generate();

    static void free();
};

template<int size>
void fillGraphRandomly(Graph *graph) {
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, 100000);
    for (auto i = 0; i < size; i++) {
        for (auto j = 0; j < size; j++) {
            graph->addEdge(i, j, uniform_dist(e1));
        }
    }
}

template<int size>
void generate_data(std::vector<Graph *> &data) {
    for (int i = 0; i < RUN_NUMBER; i++) {
        auto graph = new Graph(size);
        fillGraphRandomly<size>(graph);
        data[i] = graph;
    }
}

template<>
std::vector<Graph *> TestData<SMALL_SIZE>::data(RUN_NUMBER);

template<>
void TestData<SMALL_SIZE>::generate() {
    generate_data<SMALL_SIZE>(data);
}

template<>
std::vector<Graph *> TestData<GREAT_SIZE>::data(RUN_NUMBER);

template<>
void TestData<GREAT_SIZE>::generate() {
    generate_data<GREAT_SIZE>(data);
}

template<>
void TestData<SMALL_SIZE>::free() {
    for (auto &i : data) {
        delete i;
    }
}

template<>
void TestData<GREAT_SIZE>::free() {
    for (auto &i : data) {
        delete i;
    }
}

