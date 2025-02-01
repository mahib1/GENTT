#pragma once

#include <stdint.h>
#include <string>
#include <variant>
#include <vector>

typedef enum {
  mon = 0,
  tue = 1,
  wed = 2,
  thu = 3,
  fri = 4,
  sat = 5,
  sun = 6
} dayName_t;

enum actType { UniCourse = 1, Break = 2, Sleep = 3, Mand = 4, None = 0 };
enum placeHolder { pl };

struct uniCourse_t {
  uint16_t CourseID;
  std::string name;
  std::vector<std::vector<std::pair<uint8_t, uint8_t>>> Schedule;
  uint16_t LecHrs;
  uint16_t assignmentCnt;
  uint16_t lecCnt;
  uint8_t tracker;

private:
  uint16_t AID = actType::UniCourse;

public:
  uniCourse_t()
      : CourseID(000), name("Placeholder Course"), Schedule({}), LecHrs(0),
        assignmentCnt(0), lecCnt(0), tracker(1){};

  uniCourse_t(uint16_t CID, std::string n,
              std::vector<std::vector<std::pair<uint8_t, uint8_t>>> sched,
              uint16_t lecHrs, uint16_t assignCnt, uint16_t lecCnt,
              uint8_t track)
      : CourseID(CID), name(std::move(n)), Schedule(std::move(sched)),
        LecHrs(lecHrs), assignmentCnt(assignCnt), lecCnt(lecCnt),
        tracker(track) {}

  ~uniCourse_t() = default;
};

struct break_t {
  uint16_t hrs;

private:
  uint16_t AID = actType::Break;

public:
  break_t() : hrs(0) {};
  break_t(uint16_t h) : hrs(h) {}
  ~break_t() = default;
};

struct sleep_t {
  uint16_t hrs;
  uint16_t clusterSize;

private:
  uint16_t AID = actType::Sleep;

public:
  sleep_t() : hrs(8), clusterSize(6){};
  sleep_t(uint16_t h, uint16_t cSize) : hrs(h), clusterSize(cSize) {}
  ~sleep_t() = default;
};

struct mand_t {
  uint16_t taskID;
  uint16_t hrs;
  std::string name;
  uint16_t clusterSize;

private:
  uint16_t AID = actType::Mand;

public:
  mand_t()
      : taskID(0), hrs(0), name("Placeholder Mandatory Activity"),
        clusterSize(0){};
  mand_t(uint16_t TID, uint16_t h, std::string n, uint16_t cSize)
      : taskID(TID), hrs(h), name(std::move(n)), clusterSize(cSize) {}
  ~mand_t() = default;
};

struct none_t {
  uint16_t hrs;

public:
  none_t() : hrs(0) {};
  none_t(uint16_t h) : hrs(h) {}
  ~none_t() = default;
};

using act_t = std::variant<uniCourse_t, break_t, sleep_t, mand_t, none_t>;
