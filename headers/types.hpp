#pragma once

#include "String.hpp"
#include <vector>
#include <unordered_set>
#include <variant>

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
