#pragma once

#include <vector>
#include <atomic>

static const int INF = std::numeric_limits<int>::max() >> 2;

class Graph {
public:
    explicit Graph(unsigned int size) : size(size), adjacency_matrix(size * size, INF),
                                        edge_mask(size * size, false) {};

    int edgeWeight(int from, int to) const {
        return adjacency_matrix[index(from, to)];
    }

    bool edgeExists(int from, int to) const {
        return edge_mask[index(from, to)];
    }

    void addEdge(int from, int to, int weight) {
        int idx = index(from, to);
        edge_mask[idx] = true;
        adjacency_matrix[idx] = weight;
    }


    ~Graph() = default;

    const unsigned int size;

private:
    inline int index(int from, int to) const {
        return from * size + to;
    }

    std::vector<int> adjacency_matrix;
    std::vector<bool> edge_mask;
};


class AtomicPath {
public:
    explicit AtomicPath(unsigned int size) : vertices_count(size) {
        dist = std::vector<std::atomic_int>(size);
        incoming_edge = std::vector<std::atomic_int>(size);
        dist[0] = 0;
        incoming_edge[0] = 0;
        for (auto i = 1; i < vertices_count; i++) {
            dist[i] = INF;
            incoming_edge[i] = -1;
        }
    }

    ~AtomicPath() = default;

    const unsigned int vertices_count;
    std::vector<std::atomic_int> dist;
    std::vector<std::atomic_int> incoming_edge;
    bool negative_cycle_in_graph = false;

};


class Path {
public:
    explicit Path(unsigned int size) : vertices_count(size), dist(size, INF), incoming_edge(size, -1) {
        dist[0] = 0;
        incoming_edge[0] = 0;
    }

    Path(const AtomicPath &ap) : vertices_count(ap.vertices_count) {
        negative_cycle_in_graph = ap.negative_cycle_in_graph;
        dist = std::vector<int>(vertices_count);
        incoming_edge = std::vector<int>(vertices_count);
        for (auto i = 0; i < vertices_count; i++) {
            dist[i] = ap.dist[i];
            incoming_edge[i] = ap.incoming_edge[i];
        }

    }

    ~Path() = default;

    unsigned int vertices_count;
    std::vector<int> dist;
    std::vector<int> incoming_edge;
    bool negative_cycle_in_graph = false;


    bool operator==(const Path &other) const {
        return vertices_count == other.vertices_count && dist == other.dist && incoming_edge == other.incoming_edge &&
               negative_cycle_in_graph == other.negative_cycle_in_graph;
    }
};