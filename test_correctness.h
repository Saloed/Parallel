#pragma once

#include "sequential/sequential.h"

void test_correctness() {
    int graph_data[4][4] = {
            {0,   100, 100, 100},
            {100, 0,   100, -1},
            {100, -1,  0,   100},
            {100, 200, 2,   0}
    };
    Graph graph(4);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            graph.addEdge(i, j, graph_data[i][j]);
    }
    Path target_path(4);
    target_path.dist[0] = 0;
    target_path.dist[1] = 99;
    target_path.dist[2] = 100;
    target_path.dist[3] = 98;

    Path path(4);
    Sequential::bellman_ford(0, &graph, &path);

    std::cout << (path == target_path) << std::endl;

}