#include "common.h"
#include "day20.h"

#include <assert.h>
#include <stdlib.h>

void test_day20_part1() {
  const char *data = read_file("../input/day20.txt");
  assert(day20_part1(data).n == 786240);
  free((void *) data);
}

void test_day20_part2() {
  const char *data = read_file("../input/day20.txt");
  assert(day20_part2(data).n == 831600);
  free((void *) data);
}

int main() {
  test_day20_part1();
  test_day20_part2();

  exit(EXIT_SUCCESS);
}
