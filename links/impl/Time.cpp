#include "classes2.hpp"

uint8_t Time::TimeToIdx(const std::string &time1) noexcept {
  if (time1.length() != 4)
    return ERROR_CONVERT_IDX;
  std::vector<uint8_t> legalMins = {0, 15, 30, 45};
  uint8_t hrs = std::stol(time1.substr(0, 2));
  uint8_t mins = std::stol(time1.substr(2, 2));
  if (mins >= 60 || hrs >= 24)
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
  uint8_t hrs = 0, mins = 0;
  while (idx >= 4) {
    hrs++;
    idx -= 4;
  }
  mins += idx * 15;
  std::string s_hrs = (hrs < 10 ? "0" : "") + std::to_string(hrs);
  std::string s_mins = (mins == 0 ? "00" : std::to_string(mins));
  static std::string timeStr;
  timeStr = s_hrs + s_mins;
  return timeStr.c_str();
}

