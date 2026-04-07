// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_HASH_TABLE_C_HASH_TABLE_C_H_
#define LIB_HASH_TABLE_C_HASH_TABLE_C_H_

#define SIZE 100

#include <iomanip>
#include "../lib_table/table.h"
#include "../lib_list/list.h"
#include "../lib_tvector/tvector.h"

template <class TVal>
struct HashDataC {
    std::string key;
    TVal value;

    HashDataC() {
        key = "";
        value = TVal();
    }

    HashDataC(const std::string& k, const TVal& v) : key(k), value(v) {}

    HashDataC& operator = (const HashDataC& other) {
        key = other.key;
        value = other.value;
        return *this;
    }

    bool operator == (const HashDataC& other) const {
        return key == other.key;
    }
};

template <class TValue>
class HashTableC : public Table<std::string, TValue> {
    TVector<List<HashDataC<TValue>>> _rows;
    size_t _count;

public:
    HashTableC(size_t size = SIZE);

    void insert(const std::string&, const TValue&) override;
    void erase(const std::string&) override;
    TValue& found(const std::string&) override;
    bool is_empty() const noexcept override;
    void print() const noexcept override;

private:
    HashDataC<TValue>* find(const std::string&, size_t);
    size_t h(const std::string&) const noexcept;
};

template <class TValue>
HashTableC<TValue>::HashTableC(size_t size) : _rows(size), _count(0) {
    _rows.shrink_to_fit();
}

template <class TValue>
void HashTableC<TValue>::insert(const std::string& key, const TValue& val) {
    size_t hash = h(key);
    HashDataC<TValue>* found = find(key, hash);
    if (found) throw std::logic_error("Key already exists");
    HashDataC<TValue> h(key, val);
    _rows[hash].push_back(h);
    _count++;
}

template <class TValue>
void HashTableC<TValue>::erase(const std::string& key) {
    if (is_empty()) throw std::logic_error("Table is empty");
    size_t hash = h(key);
    if (!_rows[hash].is_empty() && _rows[hash].head()->value.key == key) {
        _rows[hash].pop_front();
        _count--;
        return;
    }
    for (auto it1 = _rows[hash].begin(); it1 != _rows[hash].end(); it1++) {
        auto it2 = it1;
        it2++;
        if (it2 != _rows[hash].end() && (*it2).key == key) {
            _rows[hash].erase(it1.get_node());
            _count--;
            return;
        }
    }
    throw std::logic_error("Key doesn't exist");
}

template <class TValue>
TValue& HashTableC<TValue>::found(const std::string& key) {
    if (is_empty()) throw std::logic_error("Table is empty");
    size_t hash = h(key);
    HashDataC<TValue>* found = find(key, hash);
    if (found) return found->value;
    throw std::logic_error("Key doesn't exist");
}

template <class TValue>
bool HashTableC<TValue>::is_empty() const noexcept {
    return _count == 0;
}

template <class TValue>
void HashTableC<TValue>::print() const noexcept {
    if (is_empty()) {
        std::cout << "Table is empty" << std::endl;
        return;
    }

    int key_length = 15;
    int value_length = 40;

    std::cout << "+-" << std::string(key_length, '-') << "+-"
        << std::string(value_length, '-') << "+" << std::endl;

    std::cout << "| " << std::left << std::setw(key_length) << "Key" << "| "
        << std::setw(value_length) << "Value" << "|" << std::endl;

    std::cout << "+-" << std::string(key_length, '-') << "+-"
        << std::string(value_length, '-') << "+" << std::endl;

    for (size_t i = 0; i < _rows.size(); i++) {
        for (auto it = _rows[i].begin(); it != _rows[i].end(); it++) {
            std::cout << "| " << std::left << std::setw(key_length) << (*it).key << "| "
                << std::setw(value_length) << (*it).value << "|" << std::endl;
        }
    }

    std::cout << "+-" << std::string(key_length, '-') << "+-"
        << std::string(value_length, '-') << "+" << std::endl;
}

template <class TValue>
HashDataC<TValue>* HashTableC<TValue>::find(const std::string& key, size_t hash) {
    for (auto it = _rows[hash].begin(); it != _rows[hash].end(); it++) {
        if ((*it).key == key) {
            return &(*it);
        }
    }
    return nullptr;
}

template <class TValue>
size_t HashTableC<TValue>::h(const std::string& key) const noexcept {
    size_t  hash = 0;
    for (int i = 0; i < key.size(); i++) hash += key[i];
    hash %= _rows.size();
    return hash;
}

#endif  // LIB_HASH_TABLE_C_HASH_TABLE_C_H_
