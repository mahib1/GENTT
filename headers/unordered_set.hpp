
#pragma once

#include "HashTable.hpp"
#include "Hasher.hpp"

template <class _Tp>
class u_set {
  HashTable<size_t, _Tp> _ht;
  Hasher<_Tp> _hasher;
  size_t _size;

public:
  u_set() : _size(0) {}

  void insert(const _Tp& val) {
    size_t hashKey = _hasher.Hash(val);
    if (!_ht.find(hashKey)) {
      _ht.insert(hashKey, val);
      _size++;
    }
  }

  void remove(const _Tp& val) {
    size_t hashKey = _hasher.Hash(val);
    if (_ht.find(hashKey)) {
      _ht.remove(hashKey);
      _size--;
    }
  }

  bool find(const _Tp& val) {
    return _ht.find(_hasher.Hash(val));
  }

  size_t size() const {
    return _size;
  }

  bucket_t<size_t, _Tp>* begin() {
    return _ht.begin();
  }

  bucket_t<size_t, _Tp>* end() {
    return _ht.end();
  }
};
;
