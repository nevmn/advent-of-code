#include <assert.h>
#include <stdlib.h>

#include "common.h"
#include "day17.h"

void test_day17_part1() {
  const char *data = read_file("../input/day17.txt");
  assert(day17_part1(data).n == 1304);
}

void test_day17_part2() {
  const char *data = read_file("../input/day17.txt");
  assert(day17_part2(data).n == 18);
}

int main() {
  test_day17_part1();
  test_day17_part2();

  exit(EXIT_SUCCESS);
}
