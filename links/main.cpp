#include <cstdint>
#include <string>
#include <vector>
#include "../headers/types.hpp"

#define ERROR_CONVERT_IDX 96


int main(int argc, char *argv[]) {
  if (argc != 2)
    return -1;

  Time t1; 

  std::string time1 = argv[1];

  uint8_t idx = t1.TimeToIdx(time1);

  printf("the index of time %s is : %d\n", time1.c_str(), idx);

  printf("The Time associated with index %d is : %s", idx,
         t1.IdxToTime(idx).c_str());

  return 0;
}
