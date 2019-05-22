#pragma once

#include <atomic>
#include "../graph.h"
#include "omp.h"

namespace OpenMP {
    void bellman_ford(int num_threads, const Graph *graphArg, Path *path) {
        auto &&graph = *graphArg;
        unsigned int n = graph.size;
        omp_set_num_threads(num_threads);

        int ave = n / num_threads;
        int local_start[num_threads];
        int local_end[num_threads];

#pragma omp parallel for
        for (int i = 0; i < num_threads; i++) {
            local_start[i] = ave * i;
            local_end[i] = ave * (i + 1);
            if (i == num_threads - 1) {
                local_end[i] = n;
            }
        }

        std::atomic_bool has_change = false;
        std::atomic_bool break_loop = false;
        auto local_dist = path->dist;

#pragma omp parallel
        {
            int my_rank = omp_get_thread_num();
            int v_start = local_start[my_rank];
            int v_end = local_end[my_rank];
            for (int i = 0; i < n - 1; i++) {
                if (break_loop) break;
                for (int u = 0; u < n; u++) {
                    for (int v = v_start; v < v_end; v++) {
                        if (!graph.edgeExists(u, v)) continue;
                        auto weight = graph.edgeWeight(u, v);
                        auto newWeight = local_dist[u] + weight;
                        if (newWeight < path->dist[v]) {
                            if (!has_change) has_change = true;
                            path->dist[v] = newWeight;
                            path->incoming_edge[v] = u;
                        }
                    }
                }
#pragma omp barrier
#pragma omp single
                {
                    break_loop = !has_change;
                    has_change = false;
                    local_dist = path->dist;

                }

            }
        }

        if (!has_change) return;

        has_change = false;
#pragma omp for collapse(2)
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (!graph.edgeExists(u, v)) continue;
                int weight = graph.edgeWeight(u, v);
                if (path->dist[u] + weight < path->dist[v]) {
                    has_change = true;
                }

            }
        }
        path->negative_cycle_in_graph = has_change;
   }
}