#pragma once

#include "String.hpp"
#include <cstdlib>
#include <sys/types.h>
#include <unordered_set>
#include <vector>
#include <variant>
#include <cstdint>
#include <fstream>
#include <iostream>

#define MAGIC 4096
#define ha(a) std::holds_alternative<a>
#define QUANTA 15
#define SIZE (24 * 60 / QUANTA)
#define ERROR_CONVERT_IDX 96

struct Time {
  static uint8_t TimeToIdx(const std::string &time1) noexcept;
  static const char* IdxToTime(uint8_t idx) noexcept;
};

struct uniCourse_t {
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
  std::variant<uniCourse_t, Mand_t> work_t;
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
  act_t getActivityInfo();

  template <class _Tp>
  Activity_t(_Tp act, uint8_t st, uint8_t end);

  void setEnd(uint8_t end);
  void setStart(uint8_t start);
  bool operator==(const Activity_t &other) const;
};

class TimeTable_t {
  std::vector<Activity_t *> _timeArray; //96 

public:
  uint8_t findLongestFreeBlock(uint8_t reqLength);
  uint8_t findNextFreeBlock(uint8_t reqLength);
  bool isFree(uint8_t idx);
  void scheduleClasses(std::vector<uniCourse_t>& courses); 
  void scheduleSleep();
  void scheduleMand(std::vector<Mand_t>& tasks);
  void validate();


  TimeTable_t();
  void insert(Activity_t* act) noexcept;
  void merge();
  void refresh();
  void debug();
  void devDebug();
  bool isOverridable(uint8_t idx);
  ~TimeTable_t();
};



uint8_t Time::TimeToIdx(const std::string &time1) noexcept {
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

const char* Time::IdxToTime(uint8_t idx) noexcept {
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
      case 10:
        s_hrs = "10";
      case 20:
        s_hrs = "20";
      default:
        s_hrs = "no"; 
    }

    if (hrs < 10) {
      s_hrs = "0" + std::to_string(hrs);
    }
  }

  std::string s_mins = std::to_string(mins);
  if (mins == 0)
    s_mins = "00";
  if (mins == 30)
    s_mins = "30";

  static std::string timeStr;
  timeStr = s_hrs + s_mins;
  return timeStr.c_str();
}

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

void Activity_t::printInfo() const {
  if (ha(WORK)(actInfo)) {
    const WORK &work = std::get<WORK>(actInfo);
    if (ha(uniCourse_t)(work.work_t)) {
      const uniCourse_t &course = std::get<uniCourse_t>(work.work_t);
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

void Activity_t::debugActivity() {
  uint8_t start = _sched.first;
  uint8_t end = _sched.second;

  printf("%s ", Time::IdxToTime(start));
  printf("to %s ->", Time::IdxToTime(end));

  if (ha(WORK)(actInfo)) {
    const WORK &work = std::get<WORK>(actInfo);
    if (ha(uniCourse_t)(work.work_t)) {
      const uniCourse_t &course = std::get<uniCourse_t>(work.work_t);
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

std::pair<uint8_t, uint8_t> Activity_t::getSchedule() {
  return _sched;
}

std::variant<WORK, SLEEP, FREE> Activity_t::getActivityInfo() {
  return actInfo;
}

template <class _Tp>
Activity_t::Activity_t(_Tp act, uint8_t st, uint8_t end) {
  actInfo = act;
  _sched.first = st;
  _sched.second = end;
}

void Activity_t::setEnd(uint8_t end) {
  _sched.second = end;
}

void Activity_t::setStart(uint8_t start) {
  _sched.first = start;
}

bool Activity_t::operator==(const Activity_t &other) const {
  return (_sched.first == other._sched.first) && (_sched.second == other._sched.second);
}






//implemeting TimeTable_t class - 

TimeTable_t::TimeTable_t() {
  // Create a default activity covering the full day.
  Activity_t* defaultActivity = new Activity_t {FREE{None_t{}}, 0, SIZE - 1};

  // Resize the vector and fill all slots with the default activity.
  _timeArray.resize(SIZE, defaultActivity);

  // Optionally, you can still call insert(defaultActivity) if needed,
  // but now every slot is already a valid pointer.
  // insert(defaultActivity);
}

void TimeTable_t::insert(Activity_t* act) noexcept {
  auto [start, end] = act -> getSchedule();
  for(uint8_t i = start; i <= end; i++) {
    if(isOverridable(i)) {
      _timeArray[i] = act;
    }
  }
}

void TimeTable_t::refresh() {
  for(int i = 0; i < SIZE; i++) {
    _timeArray[i] -> setStart(i);
  }
  
  merge();
}

void TimeTable_t::merge() {
  for(int i = 0; i < SIZE; i++) {
    int j = i;
    while(_timeArray[j] == _timeArray[j + 1] && j < SIZE - 1) {
      j++;
    }

    if(j == 0) continue;

    for(int k = i; i <= j; k++) {
      _timeArray[k] -> setStart(i); 
      _timeArray[k] -> setEnd(j);
    }
  }
}

void TimeTable_t::debug() {
  // Group contiguous slots that point to the same activity.
  uint8_t groupStart = 0;
  Activity_t* currentAct = _timeArray[0];

  for (uint8_t i = 1; i < _timeArray.size(); i++) {
    // When the pointer changes, print the group.
    if (_timeArray[i] != currentAct) {
      const char* startTime = Time::IdxToTime(groupStart);
      const char* endTime = Time::IdxToTime(i - 1);
      printf("%d, %d\n", groupStart, i - 1);
      printf("%s", Time::IdxToTime(groupStart));
      printf(" to %s -> ", Time::IdxToTime(i-1));
      currentAct->printInfo();
      currentAct = _timeArray[i];
      groupStart = i;
    }
  }

  // Print the last group.
  printf("%s", Time::IdxToTime(groupStart));
  printf(" to %s -> ", Time::IdxToTime(95));
  currentAct->printInfo();
}

bool TimeTable_t::isOverridable(uint8_t idx) {
  act_t activity = _timeArray[idx] -> getActivityInfo();
  if(ha(FREE)(activity)) {
    const FREE& free1 = std::get<FREE>(activity);

    if(ha(None_t)(free1.free_t)) {
      return true;
    }

    return false;
  }
  return false;
} 

bool TimeTable_t::isFree(uint8_t slot) {
  Activity_t* act = _timeArray[slot];

  if(ha(FREE)(act -> getActivityInfo())) {
    return true;
  }

  return false;
}

TimeTable_t::~TimeTable_t() {
  printf("Freeing!\n");
  for(int i = 0; i < _timeArray.size(); i++) {
    Activity_t* act = _timeArray[i]; 
    if(act == nullptr) continue;
    free(act);
  }
}

uint8_t TimeTable_t::findLongestFreeBlock(uint8_t reqLength) {
  uint8_t res = -1;
  uint8_t len = 0;
  
  for(uint8_t i = 0; i < SIZE; i++) {
    if(!isFree(i)) continue;

    uint8_t j = i;
    uint8_t currLen = 0;
    while(isFree(j) && j < SIZE) {
      currLen++;
      j++; 
    }

    if(currLen < reqLength) continue;

    if(len < currLen) {
      res = i;
      len = currLen;
    }
  }

  return res;
}


void TimeTable_t::devDebug() {
  printf("Refreshing...\n");
  printf("Refreshed!...\n");
  for(uint8_t i = 0; i < 96; i++) {
    _timeArray[i] -> debugActivity();
  }

  printf("Execution complete\n");
}
