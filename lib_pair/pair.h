// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_PAIR_PAIR_H_
#define LIB_PAIR_PAIR_H_

template <class TKey, class TValue>
struct TPair {
    TKey key;
    TValue value;

    TPair() = default;
    TPair(const TKey& k, const TValue& v) : key(k), value(v) {}

    bool operator == (const TPair& other) const {
        return key == other.key;
    }
};

#endif  // LIB_PAIR_PAIR_H_
