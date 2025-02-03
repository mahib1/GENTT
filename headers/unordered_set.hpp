#pragma once

#include "HashTable.hpp"

template <class _Tp>
class u_set {
private:
  HashTable<size_t, _Tp> _ht;
  Hasher<_Tp> _hasher;
  size_t _size;

public:
  u_set() : _size(0) {}

  void insert(const _Tp& val) {
    size_t hashKey = _hasher(val, _ht.getCapacity());  
    if (!_ht.find(hashKey)) {
      _ht.insert(hashKey, val);
      _size++;
    }
  }

  void remove(const _Tp& val) {
    size_t hashKey = _hasher(val, _ht.getCapacity());  
    if (_ht.find(hashKey)) {
      _ht.remove(hashKey);
      _size--;
    }
  }

  _Tp* find(const _Tp& val) {
    size_t hashKey = _hasher(val, _ht.getCapacity());  
    return _ht.get(hashKey);
  }

  size_t size() const {
    return _size;
  }

  typename HashTable<size_t, _Tp>::bucket_t* begin() {
    return _ht.begin();
  }

  typename HashTable<size_t, _Tp>::bucket_t* end() {
    return _ht.end();
  }
};
