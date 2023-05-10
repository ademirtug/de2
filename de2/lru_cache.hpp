#pragma once

#include "framework.h"

//term: least recently used cache
template<typename K, typename V> class lru_cache {
public:
	typedef typename std::list<K>::iterator order_iterator_t;

	lru_cache(size_t max_size = 250
	) : max_size_(max_size){};
	virtual ~lru_cache() {};
	
	bool exists(K key) {
		return data_.find(key) != data_.end();
	}

	V& get(K key) {
		auto it = data_.find(key);
		if (it == data_.end())
			throw std::range_error("no such item in the list");
		order_iterator_t oit = std::find(order_.begin(), order_.end(), key);
		order_.splice(order_.begin(), order_, oit);
		return it->second;
	}

	void put(K key, V val) {
		auto it = data_.find(key);
		if (it == data_.end()) {
			data_[key] = val;
		}
		else {
			order_.remove(key);
		}
		order_.push_front(key);

		if (data_.size() > max_size_){
			data_.erase(std::prev(data_.end()));
			order_.pop_back();
		}
	}
protected:
	std::unordered_map<K, V> data_;
	std::list<K> order_;
	size_t max_size_;
};
