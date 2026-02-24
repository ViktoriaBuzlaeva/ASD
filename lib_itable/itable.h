// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_ITABLE_ITABLE_H_
#define LIB_ITABLE_ITABLE_H_

#include <iostream>
#include "../lib_pair/pair.h"

template <class TKey, class TValue>
class ITable {
public:
	virtual void insert(const TKey&, const TValue&) = 0;
	virtual void erase(const TKey&) = 0;
	virtual TValue& found(const TKey&) = 0;
	virtual bool is_empty() const noexcept = 0;
	virtual ~ITable() {}
};

#endif  // LIB_ITABLE_ITABLE_H_
