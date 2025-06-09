#include "common.h"
#include "day1.h"

#include <assert.h>
#include <stdlib.h>

void test_day1_part1() {
  assert(day1_part1("(())") == 0);
  assert(day1_part1("()()") == 0);
  assert(day1_part1("(((") == 3);
  assert(day1_part1("(()(()(") == 3);
  assert(day1_part1("))(((((") == 3);
  assert(day1_part1("())") == -1);
  assert(day1_part1("))(") == -1);
  assert(day1_part1(")))") == -3);
  assert(day1_part1(")())())") == -3);
  const char *data = read_file("../input/day1.txt");
  assert(day1_part1(data) == 280);
  free((void *)data);
}

void test_day1_part2() {
  assert(day1_part2(")") == 1);
  assert(day1_part2("()())") == 5);
  const char *data = read_file("../input/day1.txt");
  assert(day1_part2(data) == 1797);
  free((void *)data);
}

int main() {
  test_day1_part1();
  test_day1_part2();

  exit(EXIT_SUCCESS);
}