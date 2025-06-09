#include "common.h"
#include "day7.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_day7_part1() {
  const char *data = read_file("../input/day7.txt");
  assert(day7_part1(data) == 3176);
  free((void *) data);
}

void test_day7_part2() {
  const char *data = read_file("../input/day7.txt");
  assert(day7_part2(data) == 14710);
  free((void *) data);
}

int main() {
  test_day7_part1();
  test_day7_part2();

  exit(EXIT_SUCCESS);
}
