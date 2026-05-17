// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_GRAPH_ADJACENCY_L_GRAPH_ADJACENCY_L_H_
#define LIB_GRAPH_ADJACENCY_L_GRAPH_ADJACENCY_L_H_

#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include "../lib_priority_queue/priority_queue.h"

template <class T>
struct Edge {
    int to_vertex;
    int weight;

    Edge(int to_vertex_, int weight_)
        : to_vertex(to_vertex_), weight(weight_) {
    }
};

template <class T>
struct Vertex {
    T value;
    std::list<Edge<T>> edges;

    Vertex(const T& value_) : value(value_), edges() {}
};

template <class T>
class GraphAdjacencyL {
    std::vector<Vertex<T>> _graph;
    bool _is_oriented;
    bool _is_weighted;

public:
    GraphAdjacencyL(std::vector<std::pair<std::pair<T, T>, int>>, bool is_oriented = false);
    GraphAdjacencyL(std::vector<std::pair<T, T>>, bool oriented = false);

    bool has_vertex(const T&) const;
    bool has_edge(const T&, const T&) const;

    void add_edge(const T&, const T&, size_t weight = 1);
    void delete_edge(const T&, const T&);
    void delete_vertex(const T&);

    std::vector<T> find_min_way(const T&, const T&);

private:
    int find_vertex_index(const T&) const;
    void  add_directed_edge(int, int, int);
    bool remove_edge(int, int);

};

template <class T>
GraphAdjacencyL<T>::GraphAdjacencyL(std::vector<std::pair<std::pair<T, T>, int>> data, bool is_oriented) :
    _graph(), _is_oriented(is_oriented), _is_weighted(true) {
    std::unordered_set<T> all_vertices;
    for (auto it = data.begin(); it != data.end(); it++) {
        all_vertices.insert(it->first.first);
        all_vertices.insert(it->first.second);
    }

    for (auto it = all_vertices.begin(); it != all_vertices.end(); it++) {
        _graph.push_back(Vertex<T>(*it));
    }

    for (auto it = data.begin(); it != data.end(); it++) {
        int from_id = find_vertex_index(it->first.first);
        int to_id = find_vertex_index(it->first.second);
        add_directed_edge(from_id, to_id, it->second);
        if (!_is_oriented) {
            add_directed_edge(to_id, from_id, it->second);
        }
    }
}

template <class T>
GraphAdjacencyL<T>::GraphAdjacencyL(std::vector<std::pair<T, T>> data, bool is_oriented) :
    _graph(), _is_oriented(is_oriented), _is_weighted(false) {
    std::unordered_set<T> all_vertices;
    for (auto it = data.begin(); it != data.end(); it++) {
        all_vertices.insert(it->first);
        all_vertices.insert(it->second);
    }

    for (auto it = all_vertices.begin(); it != all_vertices.end(); it++) {
        _graph.push_back(Vertex<T>(*it));
    }

    for (auto it = data.begin(); it != data.end(); it++) {
        int from_id = find_vertex_index(it->first);
        int to_id = find_vertex_index(it->second);
        add_directed_edge(from_id, to_id, 1);
        if (!_is_oriented) {
            add_directed_edge(to_id, from_id, 1);
        }
    }
}

template <class T>
bool GraphAdjacencyL<T>::has_vertex(const T& value) const {
    return find_vertex_index(value) != -1;
}

template <class T>
bool GraphAdjacencyL<T>::has_edge(const T& from, const T& to) const {
    int from_id = find_vertex_index(from);
    int to_id = find_vertex_index(to);

    if (from_id == -1 || to_id == -1) return false;

    for (auto it = _graph[from_id].edges.begin(); it != _graph[from_id].edges.end(); it++) {
        if ((*it).to_vertex == to_id) return true;
    }

    return false;
}

template <class T>
void GraphAdjacencyL<T>::add_edge(const T& from, const T& to, size_t weight) {
    if (!_is_weighted && weight != 1) weight = 1;

    int from_id = find_vertex_index(from);
    int to_id = find_vertex_index(to);

    if (!_graph.empty() && from_id == -1 && to_id == -1)
        throw std::logic_error("To add an edge at least one vertex must exist");

    if (from_id == -1) {
        _graph.push_back(Vertex<T>(from));
        from_id = _graph.size() - 1;
    }

    if (to_id == -1) {
        _graph.push_back(Vertex<T>(to));
        to_id = _graph.size() - 1;
    }

    add_directed_edge(from_id, to_id, weight);
    if (!_is_oriented) {
        add_directed_edge(to_id, from_id, weight);
    }
}

template <class T>
void GraphAdjacencyL<T>::delete_edge(const T& from, const T& to) {
    int from_id = find_vertex_index(from);
    int to_id = find_vertex_index(to);

    if (from_id == -1 || to_id == -1) throw std::logic_error("Vertex doesn't exist");

    if (!remove_edge(from_id, to_id)) throw std::logic_error("Edge doesn't exist");
    if (!_is_oriented) {
        remove_edge(to_id, from_id);
    }
}

template <class T>
void GraphAdjacencyL<T>::delete_vertex(const T& value) {
    int id = find_vertex_index(value);
    if (id == -1) throw std::logic_error("Vertex doesn't exist");

    for (size_t i = 0; i < _graph.size(); i++) {
        for (auto it = _graph[i].edges.begin(); it != _graph[i].edges.end(); it++) {
            if ((*it).to_vertex == id) {
                _graph[i].edges.erase(it);
                break;
            }
        }
    }
    _graph.erase(_graph.begin() + id);

    for (size_t i = 0; i < _graph.size(); i++) {
        for (auto it = _graph[i].edges.begin(); it != _graph[i].edges.end(); it++) {
            if ((*it).to_vertex > id) {
                (*it).to_vertex--;
            }
        }
    }
}

template <class T>
std::vector<T> GraphAdjacencyL<T>::find_min_way(const T& start, const T& finish) {
    int start_id = find_vertex_index(start);
    int finish_id = find_vertex_index(finish);
    if (start_id == -1 || finish_id == -1) throw std::logic_error("Vertex doesn't exist");

    std::vector<int> distance(_graph.size(), INT_MAX);  // Минимальное расстояние от начала до каждой вершины
    distance[start_id] = 0;
    std::vector<int> previous(_graph.size(), -1);  // Предыдущая вершина на кратчайшем пути

    PriorityQueue<PriorityPair<int>> queue;  // Очередь, отсортированная по возрастанию расстояния до вершины

    int order = 0;
    queue.push(PriorityPair<int>(0, start_id, order));
    order++;

    while (!queue.is_empty()) {
        PriorityPair<int> cur = queue.head();
        queue.pop();

        int cur_distance = cur.key;  // Расстояние до вершины
        int cur_vertex = cur.value;  // Индекс вершины

        if (cur_distance != distance[cur_vertex]) continue;  // Уже посещали вершину (нашли кратчайший путь)

        if (cur_vertex == finish_id) break;

        // Для всех соседей вершины проверяем, не улучшит ли путь через неё текущее расстояние до соседа
        for (auto it = _graph[cur_vertex].edges.begin(); it != _graph[cur_vertex].edges.end(); it++) {
            int neighbor_vertex = (*it).to_vertex;
            int edge_weight = (*it).weight;

            int new_distance = cur_distance + edge_weight;
            if (new_distance < distance[neighbor_vertex]) {
                distance[neighbor_vertex] = new_distance;
                previous[neighbor_vertex] = cur_vertex;
                queue.push(PriorityPair<int>(new_distance, neighbor_vertex, order));
                order++;
            }
        }
    }

    if (distance[finish_id] == INT_MAX) throw std::logic_error("Path doesn't exist");

    std::vector<T> path;
    int v = finish_id;
    while (v != -1) {
        path.push_back(_graph[v].value);
        v = previous[v];
    }
    std::reverse(path.begin(), path.end());
    return path;
}

template <class T>
int GraphAdjacencyL<T>::find_vertex_index(const T& value) const {
    for (int i = 0; i < _graph.size(); i++) {
        if (_graph[i].value == value) return i;
    }
    return -1;
}

template <class T>
void  GraphAdjacencyL<T>::add_directed_edge(int from_id, int to_id, int weight) {
    for (auto it = _graph[from_id].edges.begin(); it != _graph[from_id].edges.end(); it++) {
        if ((*it).to_vertex == to_id) return;
    }
    _graph[from_id].edges.push_back(Edge<T>(to_id, weight));
}

template <class T>
bool GraphAdjacencyL<T>::remove_edge(int from_id, int to_id) {
    for (auto it = _graph[from_id].edges.begin(); it != _graph[from_id].edges.end(); it++) {
        if ((*it).to_vertex == to_id) {
            _graph[from_id].edges.erase(it);
            return true;
        }
    }
    return false;
}

#endif  // LIB_GRAPH_ADJACENCY_L_GRAPH_ADJACENCY_L_H_

