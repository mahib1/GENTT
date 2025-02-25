#include "../headers/classes2.hpp"
#include <iostream>

// Assuming necessary headers and namespaces are already included

int main() {
  printf("Started!\n");
  printf("no error till line %d\n", __LINE__);
  // Create some sample tasks and courses
  String courseName = "Math101";
  String taskName = "Homework";
  String sleepName = "Sleep";

  // Create instances of structures
  uniCourse_t course = {
      courseName,
      {{{0, 4}, {6, 8}}},
      2,
      1,
      1}; // courseName, schedule, lecHrs, assignments, courseID
  Mand_t task = {taskName, 2, 1}; // taskName, Hrs, taskID
  Sleep_t sleep = {8, 6};         // total hours, min consecutive hours
  Break_t breakTime = {1, 1};     // Break hours, max consecutive hours
  None_t none;
  printf("Activities assignned!\n");
  printf("no error till line %d\n", __LINE__);

  // Wrap them into WORK, SLEEP, or FREE
  WORK workCourse = {.work_t = course};           // Wrapping course as WORK
  WORK workTask = {.work_t = task};               // Wrapping task as WORK
  SLEEP sleepStruct = {sleep};             // Wrapping sleep as SLEEP
  FREE freeBreak = {breakTime, 2, "Free"}; // Wrapping break as FREE
  FREE freeNone = {none, 2, "Free"};       // Wrapping none as FREE
  printf("act_t defined\n");
  printf("no error till line %d\n", __LINE__);

  // Create activities by passing the wrapped objects
  Activity_t courseActivity(workCourse, 0, 4);
  Activity_t taskActivity(workTask, 4, 6);    
  Activity_t sleepActivity(sleepStruct, 7, 8);
  Activity_t breakActivity(freeBreak, 9, 10); 
  Activity_t noneActivity(freeNone, 11, 12);  
  printf("no error till line %d\n", __LINE__);

  // Create a timetable and insert activities
  TimeTable_t timeTable;
  timeTable.debug();
  printf("Time Table init\n");
  timeTable.insert(&courseActivity);
  printf("Course insert\n");
  timeTable.insert(&taskActivity);
  printf("task insert\n");
  timeTable.insert(&breakActivity);
  printf("break insert\n");
  timeTable.insert(&noneActivity);
  printf("Reached here!\n");

  // Debug the timetable to print the scheduled activities
  // timeTable.debug();

  // None_t n1;
  // printf("%s\n", n1.name.get());

  // printf("The times are : \n");
  // for(uint8_t i = 0; i < 96; i++) {
  //   printf("%d -> %s\n", i, Time::IdxToTime(i));
  // }

  //this is not workin rn
  timeTable.debug();
  // timeTable.devDebug();

  std::cin.get();
  return 0;
}
