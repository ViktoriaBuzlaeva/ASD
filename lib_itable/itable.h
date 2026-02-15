// Copyright 2026 Viktoria Buzlaeva

#ifndef LIB_ITABLE_ITABLE_H_
#define LIB_ITABLE_ITABLE_H_

#include <iostream>

template <class TKey, class TValue>
class ITable {
public:
	virtual void insert(const TKey&, const TValue&);
	virtual void erase(const TKey&);
	virtual TValue& found(const TKey&) const noexcept;
	virtual bool is_empty() const noexcept;
	// virtual friend std::ostream& operator << (std::ostream& out, const ITable&);
};

#endif  // LIB_ITABLE_ITABLE_H_
