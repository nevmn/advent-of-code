#include "common.h"
#include "day01.h"

#include <assert.h>
#include <stdlib.h>

void test_day01_part1() {
  const char *data = read_file("../input/day01.txt");
  assert(day01_part1("(())").n == 0);
  assert(day01_part1("()()").n == 0);
  assert(day01_part1("(((").n == 3);
  assert(day01_part1("(()(()(").n == 3);
  assert(day01_part1("))(((((").n == 3);
  assert(day01_part1("())").n == -1);
  assert(day01_part1("))(").n == -1);
  assert(day01_part1(")))").n == -3);
  assert(day01_part1(")())())").n == -3);
  assert(day01_part1(data).n == 280);
  free((void *)data);
}

void test_day01_part2() {
  const char *data = read_file("../input/day01.txt");
  assert(day01_part2(")").n == 1);
  assert(day01_part2("()())").n == 5);
  assert(day01_part2(data).n == 1797);
  free((void *)data);
}

int main() {
  test_day01_part1();
  test_day01_part2();

  exit(EXIT_SUCCESS);
}