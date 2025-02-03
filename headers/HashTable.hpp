#pragma once 

#define MAGIC 4096

#include <stdlib.h>

template <class K, class V>
class bucket_t {
  K key; 
  V val;

  bucket_t(K key,  V val) : key(key), val(val) {};
};


template <class K, class V>
class HashTable {
  bucket_t<K,V>* _table;
  size_t _size;
  size_t _cap;

  size_t Hash(K& key);
  size_t DoubleHash(K& key);
  
  size_t Hash(int key);
  size_t Hash(const char* key);

public:
  HashTable() {
    _table = new bucket_t<K, V>[_cap];
    _size = 0;
  }

  void insert(K& key, V& val);
  void remove(K& key, V& val);
  void remove(K& key);
  bool find(K& key);

  bucket_t<K, V>* begin();
  bucket_t<K,V>* end();
};
