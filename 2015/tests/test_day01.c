#include "common.h"
#include "day01.h"

#include <assert.h>
#include <stdlib.h>

void test_day01_part1() {
  const char *data = read_file("../input/day01.txt");
  assert(day01_part1("(())") == 0);
  assert(day01_part1("()()") == 0);
  assert(day01_part1("(((") == 3);
  assert(day01_part1("(()(()(") == 3);
  assert(day01_part1("))(((((") == 3);
  assert(day01_part1("())") == -1);
  assert(day01_part1("))(") == -1);
  assert(day01_part1(")))") == -3);
  assert(day01_part1(")())())") == -3);
  assert(day01_part1(data) == 280);
  free((void *)data);
}

void test_day01_part2() {
  const char *data = read_file("../input/day01.txt");
  assert(day01_part2(")") == 1);
  assert(day01_part2("()())") == 5);
  assert(day01_part2(data) == 1797);
  free((void *)data);
}

int main() {
  test_day01_part1();
  test_day01_part2();

  exit(EXIT_SUCCESS);
}