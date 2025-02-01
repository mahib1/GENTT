#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include "types.hpp"

class Activity {
  actType _tag;
  act_t _act;
  std::pair<int, int> _sched;
  std::unordered_map<std::string, actType> _validStringMapper;

public:
  Activity(actType);
  Activity();
  ~Activity() = default;

  Activity(std::string actName);

  void constructStringMapper();
};


class TimeTable_t {
  std::vector<std::unique_ptr<Activity>> _TimeArray;

public:
  void addActivity(std::string, std::pair<uint8_t, uint8_t>);
  void scheduleSleep();
  void scheduleClass();
  void scheduleBreaks();
  void scheduleMand();

  void cronCollect();
  void displayTimeTable();
};
