#include "../headers/classes.hpp"
#include <string>
#include <unordered_map>

void Activity::constructStringMapper() {
  _validStringMapper["Mand"] = actType::Mand;
  _validStringMapper["Sleep"] = actType::Sleep;
  _validStringMapper["Break"] = actType::Break;
  _validStringMapper["uniCourse"] = actType::UniCourse;
  _validStringMapper["none"] = actType::None;
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
