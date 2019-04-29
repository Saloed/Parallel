#pragma once

#include <atomic>
#include "../graph.h"
#include <pthread.h>
#include <memory>

namespace Pthread {

    struct ThreadArg {
        int rank;
        int num_threads;
        pthread_barrier_t *barrier;
        std::atomic_bool *changes;
        Path *path;
        const Graph *graph;
    };


    void *thread_fn(void *arg) {
        auto &&args = reinterpret_cast<ThreadArg *>(arg);
        int my_rank = args->rank;
        int num_threads = args->num_threads;
        auto &&barrier = args->barrier;
        auto &&changes = args->changes;
        auto &&path = args->path;
        auto &&graph = args->graph;

        unsigned int n = graph->size;
        int ave = n / num_threads;

        int v_start = ave * my_rank;
        int v_end = ave * (my_rank + 1);
        if (my_rank + 1 == num_threads) {
            v_end = n;
        }

        for (int i = 0; i < n - 1; i++) {
            bool change = false;
            auto local_dist = path->dist;
            for (int u = 0; u < n; u++) {
                for (int v = v_start; v < v_end; v++) {
                    if (!graph->edgeExists(u, v)) continue;
                    auto weight = graph->edgeWeight(u, v);
                    auto newWeight = local_dist[u] + weight;
                    if (newWeight < path->dist[v]) {
                        change = true;
                        path->dist[v] = newWeight;
                        path->incoming_edge[v] = u;
                    }
                }
            }
            if (change && !changes[i].load()) changes[i].store(true);
            pthread_barrier_wait(barrier);
            if (!change && !changes[i].load()) break;
        }

        return nullptr;
    }

    Path bellman_ford(int num_threads, const Graph &graph) {
        unsigned int n = graph.size;

        int ave = n / num_threads;
        int local_start[num_threads];
        int local_end[num_threads];

        for (int i = 0; i < num_threads; i++) {
            local_start[i] = ave * i;
            local_end[i] = ave * (i + 1);
            if (i == num_threads - 1) {
                local_end[i] = n;
            }
        }

        auto &&threads = new pthread_t[num_threads];
        auto &&arguments = new ThreadArg[num_threads];
        auto &&changes = new std::atomic_bool[n];
        for (int i = 0; i < n; ++i) {
            changes[i] = false;
        }


        pthread_barrier_t barrier;
        pthread_barrier_init(&barrier, nullptr, num_threads);

        Path path(n);

        for (auto i = 0; i < num_threads; i++) {
            arguments[i] = ThreadArg{i, num_threads, &barrier, changes, &path, &graph};
            pthread_create(&threads[i], nullptr, thread_fn, (void *) &arguments[i]);
        }

        for (int i = 0; i < num_threads; i++) {
            pthread_join(threads[i], nullptr);
        }

        pthread_barrier_destroy(&barrier);

        delete threads;
        delete arguments;
        delete changes;

        bool has_change = false;

        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (!graph.edgeExists(u, v)) continue;
                int weight = graph.edgeWeight(u, v);
                if (path.dist[u] + weight < path.dist[v]) {
                    has_change = true;
                }

            }
        }
        path.negative_cycle_in_graph = has_change;

        return path;
    }
}