#include "day01.h"

int day01_part1(const char *input) {
  int floor = 0;

  while (*input) {
    if (*input == '(') {
      floor++;
    } else if (*input == ')') {
      floor--;
    }
    input++;
  }

  return floor;
}

int day01_part2(const char *input) {
  int basement_index = 0;
  int floor = 0;

  while (*input) {
    basement_index++;
    if (*input == '(') {
      floor++;
    } else if (*input == ')') {
      floor--;
    }
    if (floor == -1) {
      break;
    }
    input++;
  }

  return basement_index;
}
