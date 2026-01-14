#include "common.h"
#include "day02.h"

#include <assert.h>
#include <stdlib.h>

void test_day02_part1() {
  const char *data = read_file("../input/day02.txt");
  assert(day02_part1("2x3x4").value.n == 58);
  assert(day02_part1("1x1x10").value.n == 43);
  assert(day02_part1(data).value.n == 1588178);
  free((void *) data);
}

void test_day02_part2() {
  const char *data = read_file("../input/day02.txt");
  assert(day02_part2("2x3x4").value.n == 34);
  assert(day02_part2("1x1x10").value.n == 14);
  assert(day02_part2(data).value.n == 3783758);
  free((void *) data);
}

int main() {
  test_day02_part1();
  test_day02_part2();

  exit(EXIT_SUCCESS);
}
