#pragma once

#include <cstdint>
#include <variant>
#include "String.hpp"
#include <vector>
#include "unordered_set.hpp"

#define MAGIC 4096

class StringHasher {
private:
  static UnorderedSet<uint16_t> genIDs;

  static uint16_t hashNameToId(const String& courseName) {
    uint32_t hash1 = 5381;
    for (int i = 0; i < courseName.length(); i++) {
      hash1 = ((hash1 << 5) + hash1) + courseName[i];
    }
    return hash1 % MAGIC;
  }

  static uint16_t secondHash(const String& courseName) {
    uint32_t hash2 = 0;
    for (int i = 0; i < courseName.length(); i++) {
      hash2 = (hash2 * 31 + courseName[i]);
    }
    return (hash2 % (MAGIC - 1)) + 1;
  }

  static bool isOccupied(uint16_t index) {
    return (genIDs.find(index) != genIDs.end());
  }

public:
  static uint16_t getIdForCourse(const String& courseName) {
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
};

struct UniCourse_t  {
  String courseName;
  std::vector<std::vector<std::pair<uint8_t, uint8_t>>> courseSchedule;
  uint16_t lecHrs;
  uint16_t assignments;
  uint16_t courseID;
};


struct Mand_t {
  String taskName;
  uint16_t Hrs;
  uint16_t taskID;
};

struct Sleep_t {
  uint8_t totHrs;
  uint8_t minConsecutiveHrs;
};

struct Break_t {
  uint8_t Hrs;
  uint8_t maxConsecutiveHrs;
};

struct None_t {};


struct WORK {
  uint16_t ID = 0;
  std::variant<UniCourse_t, Mand_t> work_t; 
  String tag;
};

struct SLEEP {

};

struct FREE {

};

using act_t = std::variant<WORK, SLEEP, FREE>;

class Activity_t {
  act_t actInfo;
};
