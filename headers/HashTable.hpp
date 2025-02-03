#pragma once

#include <cstring>
#include <functional>

template <class K>
class Hasher {
public:
    size_t operator()(const K& key, size_t cap) const {
        return std::hash<K>{}(key) % cap;
    }

    size_t doubleHash(const K& key, size_t cap) const {
        return (std::hash<K>{}(key) % (cap - 1)) + 1;
    }
};

template <>
class Hasher<int> {
public:
    size_t operator()(const int& key, size_t cap) const {
        return key % cap;
    }

    size_t doubleHash(const int& key, size_t cap) const {
        return (key % (cap - 1)) + 1;
    }
};

template <>
class Hasher<const char*> {
public:
    size_t operator()(const char* key, size_t cap) const {
        size_t hash = 0;
        for (size_t i = 0; key[i] != '\0'; i++) {
            hash = hash * 31 + key[i];
        }
        return hash % cap;
    }

    size_t doubleHash(const char* key, size_t cap) const {
        size_t hash2 = 0;
        for (size_t i = 0; key[i] != '\0'; i++) {
            hash2 = hash2 * 17 + key[i];
        }
        return (hash2 % (cap - 1)) + 1;
    }
};

template <class K, class V>
class HashTable {
public:
    struct bucket_t {
        K key;
        V val;
        bool isOccupied;
        
        bucket_t() : isOccupied(false) {}
        bucket_t(const K& key, const V& val) : key(key), val(val), isOccupied(true) {}
    };

private:
    bucket_t* _table;
    size_t _size;
    size_t _cap;
    float _loadFactor;
    Hasher<K> _hasher;

    void resize();

public:

    HashTable(size_t initialCap = 16, float loadFactor = 0.7);
    ~HashTable();

    void insert(const K& key, const V& val);
    void remove(const K& key);
    bool find(const K& key) const;
    bucket_t* begin();
    bucket_t* end();
    V* get(const K& key);
};

template <class K, class V>
HashTable<K, V>::HashTable(size_t initialCap, float loadFactor)
    : _cap(initialCap), _loadFactor(loadFactor), _size(0) {
    _table = new bucket_t[_cap];
}

template <class K, class V>
HashTable<K, V>::~HashTable() {
    delete[] _table;
}

template <class K, class V>
void HashTable<K, V>::resize() {
    size_t newCap = _cap * 2;
    bucket_t* newTable = new bucket_t[newCap];

    for (size_t i = 0; i < _cap; i++) {
        if (_table[i].isOccupied) {
            size_t index = _hasher(_table[i].key, newCap);
            size_t step = _hasher.doubleHash(_table[i].key, newCap);

            while (newTable[index].isOccupied) {
                index = (index + step) % newCap;
            }
            newTable[index] = std::move(_table[i]);
        }
    }

    delete[] _table;
    _table = newTable;
    _cap = newCap;
}

template <class K, class V>
void HashTable<K, V>::insert(const K& key, const V& val) {
    if (_size >= _cap * _loadFactor) {
        resize();
    }

    size_t index = _hasher(key, _cap);
    size_t step = _hasher.doubleHash(key, _cap);

    while (_table[index].isOccupied) {
        index = (index + step) % _cap;
    }

    _table[index] = bucket_t(key, val);
    _size++;
}

template <class K, class V>
void HashTable<K, V>::remove(const K& key) {
    size_t index = _hasher(key, _cap);
    size_t step = _hasher.doubleHash(key, _cap);

    while (_table[index].isOccupied) {
        if (_table[index].key == key) {
            _table[index].isOccupied = false;
            _size--;
            return;
        }
        index = (index + step) % _cap;
    }
}

template <class K, class V>
bool HashTable<K, V>::find(const K& key) const {
    size_t index = _hasher(key, _cap);
    size_t step = _hasher.doubleHash(key, _cap);

    while (_table[index].isOccupied) {
        if (_table[index].key == key) {
            return true;
        }
        index = (index + step) % _cap;
    }
    return false;
}

template <class K, class V>
typename HashTable<K, V>::bucket_t* HashTable<K, V>::begin() {
    for (size_t i = 0; i < _cap; i++) {
        if (_table[i].isOccupied) {
            return &_table[i];
        }
    }
    return nullptr;
}

template <class K, class V>
typename HashTable<K, V>::bucket_t* HashTable<K, V>::end() {
    return &_table[_cap];
}

template <class K, class V>
V* HashTable<K, V>::get(const K& key) {
    size_t index = Hash(key);
    size_t step = DoubleHash(key);

    while (_table[index].isOccupied) {
        if (_table[index].key == key) {
            return &_table[index].val;
        }
        index = (index + step) % _cap;
    }
    return nullptr;
}
