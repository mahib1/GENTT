#include "String.hpp"

size_t String::myStrlen(const char* str) const noexcept {
  size_t i;
  for(i = 0; str[i] != '\0'; i++) {}
  return i;
}

String::String() : _size(0), _buff(nullptr) {}

String::String(const char* other) {
  _size = myStrlen(other);
  _buff = new char[_size + 1];
  memcpy(_buff, other, _size);
  _buff[_size] = '\0';
}


String::String(const String& other) : _size(other._size) {
  _buff = new char[_size + 1];
  memcpy(_buff, other._buff, _size);
  _buff[_size] = '\0';
}

String::String(String&& other) : _size(other._size), _buff(other._buff) {
  other._buff = nullptr;
}


String& String::operator=(const String& other) {
  if (this == &other) return *this;
  delete[] _buff;
  _size = other._size;
  _buff = new char[_size + 1];
  memcpy(_buff, other._buff, _size);
  _buff[_size] = '\0';
  return *this;
}

String& String::operator=(const char* other) noexcept {
  delete[] _buff;
  _size = myStrlen(other);
  _buff = new char[_size + 1];
  memcpy(_buff, other, _size);
  _buff[_size] = '\0';
  return *this;
}


String::~String() {
  delete[] _buff;
}


const char* String::get() const noexcept {
  return _buff ? _buff : "";
}

size_t String::length() const noexcept {
  return _size;
}

char String::operator[](size_t idx) const noexcept {
  return (idx < _size) ? _buff[idx] : '\0';
}

char* String::begin() {
  return _buff;
}

char* String::end() {
  return _buff + _size;
}
