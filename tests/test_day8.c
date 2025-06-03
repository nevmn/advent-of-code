#include "common.h"
#include "day8.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_day8_part1() {
  const char *data = read_file("../input/day8.txt");
  assert(day8_part1("\"\"\n" "\"abc\"\n" "\"aaa\\\"aaa\"\n" "\"\\x27\"") == 12);
  assert(day8_part1(data) == 1342);
  free((void *) data);
}

void test_day8_part2() {
  const char *data = read_file("../input/day8.txt");
  assert(day8_part2("\"\"\n" "\"abc\"\n" "\"aaa\\\"aaa\"\n" "\"\\x27\"") == 19);
  assert(day8_part2(data) == 2074);
  free((void *) data);
}

int main() {
  test_day8_part1();
  test_day8_part2();

  exit(EXIT_SUCCESS);
}
