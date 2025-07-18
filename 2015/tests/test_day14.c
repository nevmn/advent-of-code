#include <assert.h>
#include <stdlib.h>

#include "common.h"
#include "day14.h"

void test_day14_part1() {
  const char *data = read_file("../input/day14.txt");
  assert(day14_part1(data).n == 2640);
}

void test_day14_part2() {
  const char *data = read_file("../input/day13.txt");
  assert(day14_part2(data).n == 0);
}

int main() {
  test_day14_part1();
  test_day14_part2();

  exit(EXIT_SUCCESS);
}
