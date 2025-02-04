#include "../headers/classes.hpp"
#include <iostream>
#include <memory>

// Assuming necessary headers and namespaces are already included

int main() {
  printf("Started!\n");
  printf("no error till line %d\n", __LINE__);
  // Create some sample tasks and courses
  String courseName = "Math101";
  String taskName = "Homework";
  String sleepName = "Sleep";

  // Create instances of structures
  UniCourse_t course = {
      courseName,
      {},
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
  WORK workCourse = {0, course};           // Wrapping course as WORK
  WORK workTask = {0, task};               // Wrapping task as WORK
  SLEEP sleepStruct = {sleep};             // Wrapping sleep as SLEEP
  FREE freeBreak = {breakTime, 2, "Free"}; // Wrapping break as FREE
  FREE freeNone = {none, 2, "Free"};       // Wrapping none as FREE
  printf("act_t defined\n");
  printf("no error till line %d\n", __LINE__);

  // Create activities by passing the wrapped objects
  Activity_t courseActivity(workCourse, 0, 3);
  Activity_t taskActivity(workTask, 4, 6);    
  Activity_t sleepActivity(sleepStruct, 7, 8);
  Activity_t breakActivity(freeBreak, 9, 10); 
  Activity_t noneActivity(freeNone, 11, 12);  
  printf("no error till line %d\n", __LINE__);

  // Create a timetable and insert activities
  TimeTable_t timeTable;
  timeTable.insert(&courseActivity);
  timeTable.insert(&taskActivity);
  timeTable.insert(&sleepActivity);
  timeTable.insert(&breakActivity);
  timeTable.insert(&noneActivity);
  printf("Reached here!\n");

  // Debug the timetable to print the scheduled activities
  timeTable.debug();

  None_t n1;
  printf("%s\n", n1.name.get());

  return 0;
}
