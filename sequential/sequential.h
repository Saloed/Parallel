#pragma once

#include "../graph.h"

#include <chrono>

namespace Sequential {
    Path bellman_ford(const Graph &graph) {
        Path path(graph.size);
        bool has_change;

        for (int i = 0; i < graph.size - 1; i++) {
            has_change = false;
            for (int u = 0; u < graph.size; u++) {
                for (int v = 0; v < graph.size; v++) {
                    if (!graph.edgeExists(u, v)) continue;
                    int weight = graph.edgeWeight(u, v);
                    if (path.dist[u] + weight < path.dist[v]) {
                        has_change = true;
                        path.dist[v] = path.dist[u] + weight;
                        path.incoming_edge[v] = u;
                    }

                }
            }
            if (!has_change) {
                return path;
            }
        }

        for (int u = 0; u < graph.size; u++) {
            for (int v = 0; v < graph.size; v++) {
                if (!graph.edgeExists(u, v)) continue;
                int weight = graph.edgeWeight(u, v);
                if (path.dist[u] + weight < path.dist[v]) {
                    path.negative_cycle_in_graph = true;
                    return path;
                }

            }
        }
        return path;
    }
}