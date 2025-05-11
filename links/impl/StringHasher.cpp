#include "classes2.hpp"
std::unordered_set<uint16_t> StringHasher::genIDs;

uint16_t StringHasher::hashNameToId(const String &courseName) {
  uint32_t hash1 = 5381;
  for (int i = 0; i < courseName.length(); i++) {
    hash1 = ((hash1 << 5) + hash1) + courseName[i];
  }
  return hash1 % MAGIC;
}

uint16_t StringHasher::secondHash(const String &courseName) {
  uint32_t hash2 = 0;
  for (int i = 0; i < courseName.length(); i++) {
    hash2 = (hash2 * 31 + courseName[i]);
  }
  return (hash2 % (MAGIC - 1)) + 1;
}

bool StringHasher::isOccupied(uint16_t index) {
  return (genIDs.find(index) != genIDs.end());
}

uint16_t StringHasher::getIdForCourse(const String &courseName) {
  uint16_t index = hashNameToId(courseName);
  uint16_t stepSize = secondHash(courseName);
  uint16_t i = 0;
  while (isOccupied(index) && i < MAGIC) {
    index = (index + i * stepSize) % MAGIC;
    i++;
  }
  genIDs.insert(index);
  return index;
}



