#include <assert.h>
#include <stdlib.h>

#include "common.h"
#include "day16.h"

void test_day16_part1() {
  const char *data = read_file("../input/day16.txt");
  assert(day16_part1(data).n == 103);
}

void test_day16_part2() {
  const char *data = read_file("../input/day16.txt");
  assert(day16_part2(data).n == 405);
}

int main() {
  test_day16_part1();
  test_day16_part2();

  exit(EXIT_SUCCESS);
}
