#include "../headers/classes.hpp"
#include <cstdint>
#include <string>
#include <unordered_map>

void Activity::constructMappers() {
  _validStringMapper["Mand"] = actType::Mand;
  _validStringMapper["Sleep"] = actType::Sleep;
  _validStringMapper["Break"] = actType::Break;
  _validStringMapper["uniCourse"] = actType::UniCourse;
  _validStringMapper["none"] = actType::None;

  _validTypeMapper[actType::Mand] = "Mandatory"; 
  _validTypeMapper[actType::Sleep] = "Sleep";
  _validTypeMapper[actType::Break] = "Break";
  _validTypeMapper[actType::UniCourse] = "College Lecture";
  _validTypeMapper[actType::None] = "none";
}

Activity::Activity(std::string activityName) {
  if (!_validStringMapper.count(activityName)) {
    // this should never run!
    fprintf(stderr, "Invalid Constructor argument : %s\n",
            activityName.c_str());
    exit(0);
  }

  _tag = _validStringMapper[activityName];
  switch (_tag) {
  case actType::None:
    _act = none_t();
    break;
  case actType::UniCourse:
    _act = uniCourse_t();
    break;
  case actType::Break:
    _act = break_t();
    break;
  case actType::Sleep:
    _act = sleep_t();
    break;
  case actType::Mand:
    _act = mand_t();
    break;
  }
  
  _sched = {96, 96};
}

uint8_t Activity::debugActivity(const uint8_t& idx) {
  if(_sched.first != idx) 
    fprintf(stderr, "Something went wrong while displaying the Time Table!\n");

  //now process the current Activity
  Time t;
  std::string t1 = t.IdxToTime(_sched.first);
  std::string t2 = t.IdxToTime(_sched.second);

  printf("%s to %s -> %s", t1.c_str(), t2.c_str(), debugAct(_act));


  return _sched.second;
}
