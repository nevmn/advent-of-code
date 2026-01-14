#include "common.h"
#include "day06.h"

#include <assert.h>
#include <stdlib.h>

void test_day06_part1() {
  const char *data = read_file("../input/day06.txt");
  assert(day06_part1("turn on 0,0 through 999,999").value.n == 1000 * 1000);
  assert(day06_part1(data).value.n == 543903);
  free((void *) data);
}

void test_day06_part2() {
  const char *data = read_file("../input/day06.txt");
  assert(day06_part2("turn on 0,0 through 0,0").value.n == 1);
  assert(day06_part2("toggle 0,0 through 999,999").value.n == 2000000);
  assert(day06_part2(data).value.n == 14687245);
  free((void *) data);
}

int main() {
  test_day06_part1();
  test_day06_part2();

  exit(EXIT_SUCCESS);
}
