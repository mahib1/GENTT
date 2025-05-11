#include "classes2.hpp"

TimeTable_t::TimeTable_t() {
  
  auto defaultActivity = std::make_shared<Activity_t>(FREE{None_t{}}, 0, SIZE - 1);
  _timeArray.resize(SIZE, defaultActivity);
}

void TimeTable_t::insert(std::shared_ptr<Activity_t> act) noexcept {
  auto [start, end] = act->getSchedule();
  for (uint8_t i = start; i <= end; i++) {
    if (isOverridable(i)) {
      _timeArray[i] = act;
    }
  }
}

void TimeTable_t::refresh() {
  for (int i = 0; i < SIZE; i++) {
    _timeArray[i]->setStart(i);
  }
  merge();
}

void TimeTable_t::merge() {
  for (int i = 0; i < SIZE; i++) {
    int j = i;
    while (j < SIZE - 1 && (*_timeArray[j]) == (*_timeArray[j + 1])) {
      j++;
    }
    if (j == 0) continue;
    for (int k = i; k <= j; k++) {
      _timeArray[k]->setStart(i);
      _timeArray[k]->setEnd(j);
    }
  }
}

void TimeTable_t::debug() {
  uint8_t groupStart = 0;
  auto currentAct = _timeArray[0];

  for (uint8_t i = 1; i < _timeArray.size(); i++) {
    if (_timeArray[i] != currentAct) {
      printf("%s to %s -> ", Time::IdxToTime(groupStart), Time::IdxToTime(i - 1));
      currentAct->printInfo();
      currentAct = _timeArray[i];
      groupStart = i;
    }
  }
  printf("%s to %s -> ", Time::IdxToTime(groupStart), Time::IdxToTime(95));
  currentAct->printInfo();
}

bool TimeTable_t::isOverridable(uint8_t idx) {
  act_t activity = _timeArray[idx]->getActivityInfo();
  if (ha(FREE)(activity)) {
    const FREE &free1 = std::get<FREE>(activity);
    if (ha(None_t)(free1.free_t)) {
      return true;
    }
    return false;
  }
  return false;
}

bool TimeTable_t::isFree(uint8_t slot) {
  if (ha(FREE)(_timeArray[slot]->getActivityInfo())) {
    return true;
  }
  return false;
}

void TimeTable_t::devDebug() {
  printf("Refreshing...\n");
  refresh();
  printf("Refreshed!...\n");
  for (uint8_t i = 0; i < SIZE; i++) {
    _timeArray[i]->debugActivity();
  }
  printf("Execution complete\n");
}

TimeTable_t::~TimeTable_t() { 
  printf("TimeTable_t destructor called; smart pointers automatically free activities.\n");
}

