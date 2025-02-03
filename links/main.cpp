#include "../headers/classes.hpp"
#include <iostream>
#include <memory>

// Assuming necessary headers and namespaces are already included

int main() {
    // Create some sample tasks and courses
    String courseName = "Math101";
    String taskName = "Homework";
    String sleepName = "Sleep";

    // Create instances of structures
    UniCourse_t course = {courseName, {}, 2, 1, 1};  // courseName, schedule, lecHrs, assignments, courseID
    Mand_t task = {taskName, 2, 1};  // taskName, Hrs, taskID
    Sleep_t sleep = {8, 6};  // total hours, min consecutive hours
    Break_t breakTime = {1, 1};  // Break hours, max consecutive hours
    None_t none;

    // Wrap them into WORK, SLEEP, or FREE
    WORK workCourse = {0, course};  // Wrapping course as WORK
    WORK workTask = {0, task};  // Wrapping task as WORK
    SLEEP sleepStruct = {sleep};  // Wrapping sleep as SLEEP
    FREE freeBreak = {breakTime, 2, "Free"};  // Wrapping break as FREE
    FREE freeNone = {none, 2, "Free"};  // Wrapping none as FREE

    // Create activities by passing the wrapped objects
    Activity_t courseActivity(workCourse, 0, 4);  // Start at 0, End at 4
    Activity_t taskActivity(workTask, 4, 6);  // Start at 4, End at 6
    Activity_t sleepActivity(sleepStruct, 6, 8);  // Start at 6, End at 8
    Activity_t breakActivity(freeBreak, 8, 9);  // Start at 8, End at 9
    Activity_t noneActivity(freeNone, 9, 10);  // Start at 9, End at 10

    // Create a timetable and insert activities
    TimeTable_t timeTable;
    timeTable.insert(&courseActivity);
    timeTable.insert(&taskActivity);
    timeTable.insert(&sleepActivity);
    timeTable.insert(&breakActivity);
    timeTable.insert(&noneActivity);

    // Debug the timetable to print the scheduled activities
    timeTable.debug();

    return 0;
}
