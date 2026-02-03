#include "common.h"
#include "day21.h"

#include <assert.h>
#include <stdlib.h>

void test_day21_part1() {
  const char *data = read_file("../input/day21.txt");
  assert(day21_part1(data).value.n == 111);
  free((void *) data);
}

void test_day21_part2() {
  const char *data = read_file("../input/day21.txt");
  assert(day21_part2(data).value.n == 188);
  free((void *) data);
}

int main() {
  test_day21_part1();
  test_day21_part2();

  exit(EXIT_SUCCESS);
}