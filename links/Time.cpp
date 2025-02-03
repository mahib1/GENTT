#include "../headers/types.hpp"

#define ERROR_CONVERT_IDX 96

uint8_t Time::TimeToIdx(const std::string &time1) const noexcept {
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

std::string Time::IdxToTime(uint8_t idx) const noexcept {
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

  std::string t = s_hrs + s_mins;

  return t;
}
