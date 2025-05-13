#include "common.h"
#include "day6.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_day6_part1() {
  assert(day6_part1("turn on 0,0 through 999,999") == 1000*1000);
  const char *data = read_file("../input/day6.txt");
  assert(day6_part1(data) == 543903);
  free((void *) data);
}

void test_day6_part2() {
  assert(day6_part2("turn on 0,0 through 0,0") == 1);
  assert(day6_part2("toggle 0,0 through 999,999") == 2000000);
  const char *data = read_file("../input/day6.txt");
  assert(day6_part2(data) == 14687245);
  free((void *) data);
}

int main() {
  test_day6_part1();
  test_day6_part2();

  exit(EXIT_SUCCESS);
}
