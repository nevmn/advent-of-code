#include "common.h"
#include "day10.h"

#include <assert.h>
#include <stdlib.h>

void test_day10_part1() {
  const char *data = read_file("../input/day10.txt");
  // assert(day10_part1("211") == 4);
  // assert(day10_part1("1") == 2);
  // assert(day10_part1("11") == 2);
  // assert(day10_part1("21") == 4);
  // assert(day10_part1("1211") == 6);
  // assert(day10_part1("111221") == 6);
  assert(day10_part1(data) == 492982);
}

void test_day10_part2() {
  const char *data = read_file("../input/day10.txt");
  assert(day10_part2(data) == 6989950);
}

int main() {
  test_day10_part1();
  test_day10_part2();

  exit(EXIT_SUCCESS);
}
