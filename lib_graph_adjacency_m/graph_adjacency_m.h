// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_GRAPH_ADJACENCY_M_GRAPH_ADJACENCY_M_H_
#define LIB_GRAPH_ADJACENCY_M_GRAPH_ADJACENCY_M_H_

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "../lib_triangle_matrix/trianglematrix.h"

template <class T>
class GraphAdjacencyM {
    Matrix<int> _oriented_graph;
    TriangleMatrix<int> _graph;
    std::unordered_map<T, int> _value_index;
    bool _is_oriented;
    bool _is_weighted;

public:
    GraphAdjacencyM(std::vector<std::pair<std::pair<T, T>, int>>, bool is_oriented = false);
    GraphAdjacencyM(std::vector<std::pair<T, T>>, bool oriented = false);

    bool has_vertex(const T&) const;
    bool has_edge(const T&, const T&);

    void add_edge(const T&, const T&, size_t weight = 1);
    void delete_edge(const T&, const T&);
    void delete_vertex_edges(const T&);

private:
    int& graph(int, int);

};

template <class T>
GraphAdjacencyM<T>::GraphAdjacencyM(std::vector<std::pair<std::pair<T, T>, int>> data, bool is_oriented) :
    _oriented_graph(), _graph(), _value_index(), _is_oriented(is_oriented), _is_weighted(true) {
    std::unordered_set<T> all_vertices;
    for (auto it = data.begin(); it != data.end(); it++) {
        all_vertices.insert(it->first.first);
        all_vertices.insert(it->first.second);
    }

    int index = 0;
    for (auto it = all_vertices.begin(); it != all_vertices.end(); it++) {
        _value_index[*it] = index;
        index++;
    }

    size_t size = all_vertices.size();
    if (_is_oriented) _oriented_graph = Matrix<int>(size, size);
    else _graph = TriangleMatrix<int>(size);
    

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            graph(i,j) = INT_MAX;
        }
    }

    for (auto it = data.begin(); it != data.end(); it++) {
        int from_ind = _value_index[it->first.first];
        int to_ind = _value_index[it->first.second];

        graph(from_ind, to_ind) = it->second;
    }
}

template <class T>
GraphAdjacencyM<T>::GraphAdjacencyM(std::vector<std::pair<T, T>> data, bool is_oriented) :
    _graph(), _is_oriented(is_oriented), _is_weighted(false) {
    std::unordered_set<T> all_vertices;
    for (auto it = data.begin(); it != data.end(); it++) {
        all_vertices.insert(it->first);
        all_vertices.insert(it->second);
    }

    int index = 0;
    for (auto it = all_vertices.begin(); it != all_vertices.end(); it++) {
        _value_index[*(it)] = index;
        index++;
    }

    size_t size = all_vertices.size();
    if (_is_oriented) _oriented_graph = Matrix<int>(size, size);
    else _graph = TriangleMatrix<int>(size);


    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            graph(i, j) = 0;
        }
    }

    for (auto it = data.begin(); it != data.end(); it++) {
        int from_ind = _value_index[it->first];
        int to_ind = _value_index[it->second];

        graph(from_ind, to_ind) = 1;
    }
}

template <class T>
bool GraphAdjacencyM<T>::has_vertex(const T& value) const {
    return _value_index.find(value) != _value_index.end();
}

template <class T>
bool GraphAdjacencyM<T>::has_edge(const T& from, const T& to) {
    if (_value_index.find(from) == _value_index.end()
        || _value_index.find(to) == _value_index.end()) return false;

    int from_ind = _value_index[from];
    int to_ind = _value_index[to];

    if (_is_weighted) {
        return graph(from_ind, to_ind) != INT_MAX;
    }
    else {
        return graph(from_ind, to_ind) != 0;
    }
}

template <class T>
void GraphAdjacencyM<T>::add_edge(const T& from, const T& to, size_t weight) {
    if (_value_index.find(from) == _value_index.end()
        || _value_index.find(to) == _value_index.end()) 
        throw std::logic_error("To add an edge vertices must exist");

    int from_ind = _value_index[from];
    int to_ind = _value_index[to];

    graph(from_ind, to_ind) = weight;
}

template <class T>
void GraphAdjacencyM<T>::delete_edge(const T& from, const T& to) {
    if (_value_index.find(from) == _value_index.end()
        || _value_index.find(to) == _value_index.end())
        throw std::logic_error("Vertex doesn't exist");

    int from_ind = _value_index[from];
    int to_ind = _value_index[to];

    if (_is_weighted) {
        if (graph(from_ind, to_ind) == INT_MAX) throw std::logic_error("Edge doesn't exist");
        graph(from_ind, to_ind) = INT_MAX;
    }
    else {
        if (graph(from_ind, to_ind) == 0) throw std::logic_error("Edge doesn't exist");
        graph(from_ind, to_ind) = 0;
    }
}

template <class T>
void GraphAdjacencyM<T>::delete_vertex_edges(const T& value) {
    if (_value_index.find(value) == _value_index.end())
        throw std::logic_error("Vertex doesn't exist");

    int value_ind = _value_index[value];
    size_t n = _is_oriented ? _oriented_graph.rows() : _graph.rows();

    if (_is_weighted) {
        for (size_t i = 0; i < n; i++) {
            graph(value_ind, i) = INT_MAX;
            graph(i, value_ind) = INT_MAX;
        }
    }
    else{
        for (size_t i = 0; i < n; i++) {
            graph(value_ind, i) = 0;
            graph(i, value_ind) = 0;
        }
    }
}

template <class T>
int& GraphAdjacencyM<T>::graph(int i, int j) {
    if (_is_oriented) {
        return _oriented_graph[i][j];
    }
    else {
        if (i > j) return _graph[j][i];
        return _graph[i][j];
    }
}

#endif  // LIB_GRAPH_ADJACENCY_M_GRAPH_ADJACENCY_M_H_
