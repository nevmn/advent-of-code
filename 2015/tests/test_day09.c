#include "common.h"
#include "day09.h"

#include <assert.h>
#include <stdlib.h>

void test_day09_part1() {
  const char *data = read_file("../input/day09.txt");
  assert(day09_part1("London to Dublin = 464\nLondon to Belfast = 518\nDublin to Belfast = 141") == 0);
  free((void *) data);
}

void test_day09_part2() {
  const char *data = read_file("../input/day09.txt");
  free((void *) data);
}

int main() {
  test_day09_part1();
  test_day09_part2();

  exit(EXIT_SUCCESS);
}
