#include "classes2.hpp"
#include <iostream>
#include <memory>

int main() {
  printf("Started!\n");

  String courseName = "Math101";
  String taskName = "Homework";
  String sleepName = "Sleep";

  uniCourse_t course = {courseName, {{{0, 4}, {6, 8}}}, 2, 1, 1};
  Mand_t task = {taskName, 2, 1};
  Sleep_t sleep = {8, 6};
  Break_t breakTime = {1, 1};
  None_t none;
  
  WORK workCourse = {.work_t = course};
  WORK workTask = {.work_t = task};
  SLEEP sleepStruct = {sleep};
  FREE freeBreak = {breakTime, 2, "Free"};
  FREE freeNone = {none, 2, "Free"};
  
  
  auto courseActivity = std::make_shared<Activity_t>(workCourse, 0, 4);
  auto taskActivity = std::make_shared<Activity_t>(workTask, 4, 6);
  auto sleepActivity = std::make_shared<Activity_t>(sleepStruct, 7, 8);
  auto breakActivity = std::make_shared<Activity_t>(freeBreak, 9, 10);
  auto noneActivity = std::make_shared<Activity_t>(freeNone, 11, 12);

  TimeTable_t timeTable;
  timeTable.insert(courseActivity);
  timeTable.insert(taskActivity);
  timeTable.insert(breakActivity);
  timeTable.insert(noneActivity);

  timeTable.debug();
  timeTable.devDebug();

  std::cin.get();
  return 0;
}
