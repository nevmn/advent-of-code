#include <assert.h>
#include <stdlib.h>

#include "common.h"
#include "day10.h"

void test_day10_part1() {
  const char *data = read_file("../input/day10.txt");
  assert(day10_part1(data).n == 492982);
}

void test_day10_part2() {
  const char *data = read_file("../input/day10.txt");
  assert(day10_part2(data).n == 6989950);
}

int main() {
  test_day10_part1();
  test_day10_part2();

  exit(EXIT_SUCCESS);
}
