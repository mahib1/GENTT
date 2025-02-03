#pragma once

#include "String.hpp"
#include <unordered_set>
#include <cstdint>
#include <variant>
#include <vector>

#define MAGIC 4096
#define ha(a) std::holds_alternative<a>
#define QUANTA 15
#define SIZE (24 * 60 / QUANTA)
#define ERROR_CONVERT_IDX 96

struct Time {
  static uint8_t TimeToIdx(const std::string &time1) noexcept {
    if (time1.length() != 4)
      return ERROR_CONVERT_IDX;

    std::vector<uint8_t> legalMins = {0, 15, 30, 45};

    uint8_t hrs = std::stol(time1.substr(0, 2));
    uint8_t mins = std::stol(time1.substr(2, 2));

    if (mins >= 60)
      return ERROR_CONVERT_IDX;

    if (hrs >= 24)
      return ERROR_CONVERT_IDX;

    uint8_t flag = 0;
    for (int i = 0; i < 4; i++) {
      if (legalMins[i] == mins)
        flag = 1;
    }

    if (flag == 0)
      return ERROR_CONVERT_IDX;

    uint8_t idx = ((hrs * 60) + mins) / 15;

    return idx;
  }

  static const char* IdxToTime(uint8_t idx) noexcept {
    if (idx == ERROR_CONVERT_IDX) {
      return "";
    }

    uint8_t hrs = 0;
    uint8_t mins = 0;

    while (idx >= 4) {
      hrs++;
      idx -= 4;
    }

    mins += idx * 15;

    std::string s_hrs = std::to_string(hrs);
    if (s_hrs.length() != 2) {
      switch (hrs) {
      case 0:
        s_hrs = "00";

      case 10:
        s_hrs = "10";

      case 20:
        s_hrs = "20";

      default:
        s_hrs = "no"; // never to run
      }

      if (hrs < 10 && hrs != 0) {
        s_hrs = "0" + std::to_string(hrs);
      }
    }

    std::string s_mins = std::to_string(mins);
    if (mins == 0)
      s_mins = "00";
    if (mins == 30)
      s_mins = "30";

    const char* t = (s_hrs + s_mins).c_str();

    return t;
  }
};

class StringHasher {
private:
  static std::unordered_set<uint16_t> genIDs;

  static uint16_t hashNameToId(const String &courseName) {
    uint32_t hash1 = 5381;
    for (int i = 0; i < courseName.length(); i++) {
      hash1 = ((hash1 << 5) + hash1) + courseName[i];
    }
    return hash1 % MAGIC;
  }

  static uint16_t secondHash(const String &courseName) {
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
  static uint16_t getIdForCourse(const String &courseName) {
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

class Activity_t {
  act_t actInfo;
  std::pair<uint8_t, uint8_t> _sched;

public:
  void debugActivity() {
    uint8_t start = _sched.first;
    uint8_t end = _sched.second;

    printf("%s to %s -> ", Time::IdxToTime(start), Time::IdxToTime(end));

    if (ha(WORK)(actInfo)) {
      const WORK &work = std::get<WORK>(actInfo);
      if (ha(UniCourse_t)(work.work_t)) {
        const UniCourse_t &course = std::get<UniCourse_t>(work.work_t);
        printf("Course: %s\n", course.courseName.get());
      } else if (ha(Mand_t)(work.work_t)) {
        const Mand_t &task = std::get<Mand_t>(work.work_t);
        printf("Task: %s\n", task.taskName.get());
      }
    } else if (ha(SLEEP)(actInfo)) {
      const SLEEP &sleep = std::get<SLEEP>(actInfo);
      printf("%s\n", sleep.sleep_t.name.get());
    } else if (ha(FREE)(actInfo)) {
      const FREE &freeTime = std::get<FREE>(actInfo);
      if (ha(Break_t)(freeTime.free_t)) {
        const Break_t &breakTime = std::get<Break_t>(freeTime.free_t);
        printf("%s\n", breakTime.name.get());
      } else if (ha(None_t)(freeTime.free_t)) {
        const None_t &none = std::get<None_t>(freeTime.free_t);
        printf("%s\n", none.name.get());
      }
    }
  }

  std::pair<uint8_t, uint8_t> getSchedule() { return _sched; }
  std::variant<WORK, SLEEP, FREE> getActivityInfo() {return actInfo; }

  template <typename _Tp>
  Activity_t(_Tp act, uint8_t st, uint8_t end) : actInfo(act) {
    _sched = {st, end};
  }
};

class TimeTable_t {
  std::vector<Activity_t *> _timeArray;

public:
  TimeTable_t() {
    for (int i = 0; i < 96; i++) {
      _timeArray.push_back(0);
    }
  }

  void debug() {
    int st = 0, et = 0;
    int K = 8;

    for (int i = 0; i < _timeArray.size(); i++) {
      if (_timeArray[i] != nullptr) {
        if (i > 0 && _timeArray[i] == _timeArray[i - 1]) {
          et = i;
        } else {
          if (i > 0 && et - st >= K) {
            _timeArray[st]->debugActivity();
          }
          st = et = i;
        }
      }
    }

    if (et - st >= K) {
      _timeArray[st]->debugActivity();
    }
  }

  void insert(Activity_t* act1) {
    auto [start, end] = act1 -> getSchedule();
    for(int i = start; i < end; i++) {
      auto info = _timeArray[i] -> getActivityInfo();
      if(ha(FREE)(info)) {
        const FREE freeTime = std::get<FREE>(info);

        if(ha(None_t)(freeTime.free_t)) {
          _timeArray[i] = act1;     
        }
      }
    }
  }
};
