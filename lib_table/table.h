// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_TABLE_TABLE_H_
#define LIB_TABLE_TABLE_H_

#include "../lib_itable/itable.h"

template <class TKey, class TValue>
class Table : public ITable<TKey, TValue> {
public:
    virtual void print() const noexcept = 0;
    virtual ~Table() {}

    friend std::ostream& operator << (std::ostream& out, const Table& table) {
        table.print();
        return out;
    }
};

#endif  // LIB_TABLE_TABLE_H_
