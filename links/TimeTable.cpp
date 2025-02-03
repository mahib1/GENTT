#include "../headers/classes.hpp"
#include <cstdint>


void TimeTable_t::displayTimeTable() {
  /* I Have an array where each element is an Activity type thing*/

  //lets start at 12:00 AM 
  //first debug 12:00 AM Activity

  uint8_t i = 0;
  while(i < _TimeArray.size()) {
    uint8_t nextActivityIndex = _TimeArray[i] -> debugActivity(i);
    i = nextActivityIndex;
  }
}

