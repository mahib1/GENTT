#include "classes2.hpp"
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

Activity_t::~Activity_t() {
  debugActivity();
  printf("Freeing this one ^\n");
  lb;
}


template  Activity_t::Activity_t(WORK, uint8_t, uint8_t);
template Activity_t::Activity_t(FREE, uint8_t, uint8_t); 
template Activity_t::Activity_t(SLEEP, uint8_t, uint8_t);
