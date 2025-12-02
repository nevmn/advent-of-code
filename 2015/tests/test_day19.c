#include "common.h"
#include "day19.h"

#include <assert.h>
#include <stdlib.h>

void test_day19_part1() {
  const char *data = read_file("../input/day19.txt");
  assert(day19_part1(data).n == 509);
  free((void *) data);
}

void test_day19_part2() {
  const char *data = read_file("../input/day19.txt");
  assert(day19_part2(data).n == 195);
  free((void *) data);
}

int main() {
  test_day19_part1();
  test_day19_part2();

  exit(EXIT_SUCCESS);
}
