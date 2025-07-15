#include <assert.h>
#include <stdlib.h>

#include "common.h"
#include "day13.h"

void test_day13_part1() {
  const char *data = read_file("../input/day13.txt");
  assert(day13_part1(data).n == 733);
}

void test_day13_part2() {
  const char *data = read_file("../input/day13.txt");
  assert(day13_part2(data).n == 725);
}

int main() {
  test_day13_part1();
  test_day13_part2();

  exit(EXIT_SUCCESS);
}
