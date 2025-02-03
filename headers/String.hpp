#pragma once

#include <cstddef>
#include <cstring>

class String {
  char* _buff; 
  size_t _size;

  size_t myStrlen(const char* str) const noexcept {
    size_t i;
    for(i = 0; str[i] != '\0'; i++) {}
    return i;
  }


public:
  String() : _size(0), _buff(nullptr) {}

  String(const char* other) {
    _size = myStrlen(other);
    _buff = new char[_size + 1];
    memcpy(_buff, other, _size);
    _buff[_size] = '\0';
  }

  String(const String& other) : _size(other._size) {
    _buff = new char[_size + 1];
    memcpy(_buff, other._buff, _size);
    _buff[_size] = '\0';
  }

  String(String&& other) : _size(other._size), _buff(other._buff) {
    other._buff = nullptr;
  }

  String& operator=(const String& other) {
    if (this == &other) return *this;
    delete[] _buff;
    _size = other._size;
    _buff = new char[_size + 1];
    memcpy(_buff, other._buff, _size);
    _buff[_size] = '\0';
    return *this;
  }

  String& operator=(const char* other) noexcept {
    delete[] _buff;
    _size = myStrlen(other);
    _buff = new char[_size + 1];
    memcpy(_buff, other, _size);
    _buff[_size] = '\0';
    return *this;
  }

  ~String() {
    delete[] _buff;
  }

  const char* get() const noexcept {
    return _buff ? _buff : "";
  }

  size_t length() const noexcept {
    return _size;
  }

  char operator[](size_t idx) const noexcept {
    return (idx < _size) ? _buff[idx] : '\0';
  }

  char* begin() {
    return _buff;
  }

  char* end() {
    return _buff + _size;
  }
};
