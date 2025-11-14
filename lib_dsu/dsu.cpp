// Copyright 2025 Viktoria Buzlaeva

#include "../lib_dsu/dsu.h"
#include <stdexcept>

DSU::DSU(size_t size) : _size(size) {
    _parent = new int[_size];
    _rank = new int[_size];
    for (size_t i = 0; i < _size; i++) {
        _parent[i] = i;
        _rank[i] = 1;
    }
}

DSU::~DSU() {
    delete[] _parent;
    delete[] _rank;
}

void DSU::unite(int x, int y) {
    if (x >= _size || y >= _size || x < 0 || y < 0) throw std::logic_error("Invalid input");
    if (x == y) return;
    int parent_x = find(x);
    int parent_y = find(y);
    if (_rank[parent_x] >= _rank[parent_y]) {
        _parent[parent_x] = parent_y;
    }
    else {
        _parent[parent_y] = parent_x;
    }
    if (_rank[parent_x] == _rank[parent_y]) {
        _rank[parent_x]++;
    }
}

int DSU::find(int x) {
    if (x >= _size || x < 0) throw std::logic_error("Invalid input");
    return x = find_rec(_parent[x]);
}

int DSU::find_rec(int x) {
    if (_parent[x] == x) return x;
    return x = find_rec(_parent[x]);
}
