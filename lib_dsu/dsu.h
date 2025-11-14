// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_DSU_DSU_H_
#define LIB_DSU_DSU_H_

class DSU {
    int* _parent, * _rank;
    size_t _size;

public:
    DSU(size_t);
    ~DSU();

    void unite(int, int);
    int find(int);

private:
    int find_rec(int);
};

#endif  // LIB_DSU_DSU_H_
