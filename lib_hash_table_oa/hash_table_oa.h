// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_HASH_TABLE_OA_HASH_TABLE_OA_H_
#define LIB_HASH_TABLE_OA_HASH_TABLE_OA_H_

#define SIZE 100
#define SHIFT 7

#include <iomanip>
#include <algorithm>
#include "../lib_table/table.h"
#include "../lib_tvector/tvector.h"

bool is_coprime(size_t f, size_t s) {
    while (s != 0) {
        size_t t = s;
        s %= f;
        f = t;
    }
    return f == 1;
}

enum Status { Busy, Empty, Deleted };

template <class TVal>
struct HashData {
    Status state;
    std::string key;
    TVal value;

    HashData() {
        state = Empty;
        key = "";
        value = TVal();
    }

    HashData(const std::string& k, const TVal& v, Status st = Busy) : key(k), value(v), state(st) {}

    HashData& operator = (const HashData& other) {
        state = other.state;
        key = other.key;
        value = other.value;
        return *this;
    }

    bool operator == (const HashData& other) const {
        return key == other.key;
    }
};

template <class TValue>
class HashTableOA : public Table<std::string, TValue> {
    TVector<HashData<TValue>> _rows;
    size_t _size;
    size_t _shift;
    size_t _count;

public:
    HashTableOA(size_t size = SIZE);

    bool is_full() const noexcept;

    void insert(const std::string&, const TValue&) override;
    void erase(const std::string&) override;
    TValue& found(const std::string&) override;
    bool is_empty() const noexcept override;
    void print() const noexcept override;

private:
    size_t h(const std::string&) const noexcept;
    size_t hh(size_t) const noexcept;
};

template <class TValue>
HashTableOA<TValue>::HashTableOA(size_t size) : _size(size), _rows(size), _count(0) {
    _rows.shrink_to_fit();
    if (size == SIZE) { _shift = SHIFT; return; }
    for (size_t i = std::max((size_t)2, _size / 15); i < _size; i++) {
        if (is_coprime(i, _size)) {
            _shift = i;
            return;
        }
    }
}

template <class TValue>
bool HashTableOA<TValue>::is_full() const noexcept {
    return _count == _size;
}

template <class TValue>
void HashTableOA<TValue>::insert(const std::string& key, const TValue& val) {
    if (is_full()) throw std::logic_error("Table is full");
    size_t hash = h(key);
    while (1) {
        if (_rows[hash].state != Busy) {
            _rows[hash] = HashData<TValue>(key, val);
            _count++;
            return;
        }
        if (_rows[hash].key == key) throw std::logic_error("Key already exists");
        hash = hh(hash);
    }
}

template <class TValue>
void HashTableOA<TValue>::erase(const std::string& key) {
    size_t hash = h(key);
    size_t first_hash = hash;
    while (1) {
        if (_rows[hash].state == Empty) break;
        if (_rows[hash].state == Busy && _rows[hash].key == key) {
            _rows[hash].state = Deleted;
            _count--;
            return;
        }
        hash = hh(hash);
        if (first_hash == hash) break;
    }

    throw std::logic_error("Key doesn't exist");
}

template <class TValue>
TValue& HashTableOA<TValue>::found(const std::string& key) {
    if (is_empty()) throw std::logic_error("Table is empty");
    size_t hash = h(key);
    size_t first_hash = hash;
    while (1) {
        if (_rows[hash].state == Empty) break;
        if (_rows[hash].state == Busy && _rows[hash].key == key) {
            return _rows[hash].value;
        }
        hash = hh(hash);
        if (first_hash == hash) break;
        
    }
    throw std::logic_error("Key doesn't exist");
}

template <class TValue>
bool HashTableOA<TValue>::is_empty() const noexcept {
    return _count == 0;
}

template <class TValue>
void HashTableOA<TValue>::print() const noexcept {
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

    for (size_t i = 0; i < _size; i++) {
        if (_rows[i].state == Busy) {
            std::cout << "| " << std::left << std::setw(key_length) << _rows[i].key << "| "
                << std::setw(value_length) << _rows[i].value << "|" << std::endl;
        }
    }

    std::cout << "+-" << std::string(key_length, '-') << "+-"
        << std::string(value_length, '-') << "+" << std::endl;
}

template <class TValue>
size_t HashTableOA<TValue>::h(const std::string& key) const noexcept {
    size_t  hash = 0;
    for (int i = 0; i < key.size(); i++) hash += key[i];
    hash %= _size;
    return hash;
}

template <class TValue>
size_t HashTableOA<TValue>::hh(size_t hash) const noexcept {
    return (hash + _shift) % _size;
}

#endif  // LIB_HASH_TABLE_OA_HASH_TABLE_OA_H_
