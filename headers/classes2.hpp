#pragma once

#include "String.hpp"
#include <unordered_set>
#include <vector>
#include <variant>
#include <cstdint>

#define MAGIC 4096
#define ha(a) std::holds_alternative<a>
#define QUANTA 15
#define SIZE (24 * 60 / QUANTA)
#define ERROR_CONVERT_IDX 96

struct Time {
  static uint8_t TimeToIdx(const std::string &time1) noexcept;
  static const char* IdxToTime(uint8_t idx) noexcept;
};

struct UniCourse_t {
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
  String name = "Sleep";
};

struct Break_t {
  uint8_t Hrs;
  uint8_t maxConsecutiveHrs;
  String name = "Break";
};

struct None_t {
  String name = "None";
};

struct WORK {
  uint16_t ID = 0;
  std::variant<UniCourse_t, Mand_t> work_t;
  String tag = "Work";
};

struct SLEEP {
  Sleep_t sleep_t;
};

struct FREE {
  std::variant<Break_t, None_t> free_t;
  uint16_t ID = 2;
  String tag = "Free";
};

using act_t = std::variant<WORK, SLEEP, FREE>;

class StringHasher {
private:
  static std::unordered_set<uint16_t> genIDs;
  static uint16_t hashNameToId(const String &courseName);
  static uint16_t secondHash(const String &courseName);
  static bool isOccupied(uint16_t index);

public:
  static uint16_t getIdForCourse(const String &courseName);
};

class Activity_t {
  act_t actInfo;
  std::pair<uint8_t, uint8_t> _sched;

public:
  void printInfo() const;
  void debugActivity();
  std::pair<uint8_t, uint8_t> getSchedule();
  std::variant<WORK, SLEEP, FREE> getActivityInfo();

  template <class _Tp>
  Activity_t(_Tp act, uint8_t st, uint8_t end);

  void setEnd(uint8_t end);
  void setStart(uint8_t start);
  bool operator==(const Activity_t &other) const;
};

class TimeTable_t {
  std::vector<Activity_t *> _timeArray;

public:
  TimeTable_t();
  void insert(Activity_t* act) noexcept;
  void merge();
  void debug();
  bool isOverridable(uint8_t idx);
};


#include "classes.tci"
