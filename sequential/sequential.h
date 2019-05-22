#pragma once

#include "../graph.h"

#include <chrono>

namespace Sequential {
    void bellman_ford(int ignored, const Graph *graphArg, Path *path) {
        bool has_change;
        auto &&graph = *graphArg;
        for (int i = 0; i < graph.size - 1; i++) {
            auto local_dist = path->dist;
            has_change = false;
            for (int u = 0; u < graph.size; u++) {
                for (int v = 0; v < graph.size; v++) {
                    if (!graph.edgeExists(u, v)) continue;
                    int weight = graph.edgeWeight(u, v);
                    auto newWeight = local_dist[u] + weight;
                    if (newWeight < path->dist[v]) {
                        has_change = true;
                        path->dist[v] = newWeight;
                        path->incoming_edge[v] = u;
                    }

                }
            }
            if (!has_change) {
                return;
            }
        }

        for (int u = 0; u < graph.size; u++) {
            for (int v = 0; v < graph.size; v++) {
                if (!graph.edgeExists(u, v)) continue;
                int weight = graph.edgeWeight(u, v);
                if (path->dist[u] + weight < path->dist[v]) {
                    path->negative_cycle_in_graph = true;
                    return;
                }

            }
        }
    }
}