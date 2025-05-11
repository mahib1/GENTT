#pragma once

#include <cstddef>
#include <cstring>

class String {
  char* _buff; 
  size_t _size;

  size_t myStrlen(const char* str) const noexcept; 
  
public:
  String();
  String(const char* other);
  String(const String& other);
  String(String&& other);
  
  String& operator=(const String& other);
  String& operator=(const char* other) noexcept; 

  const char* get() const noexcept;
  size_t length() const noexcept; 
  char operator[](size_t idx) const noexcept;
  char* begin();
  char* end();

  ~String();
};
