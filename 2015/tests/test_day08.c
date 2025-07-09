#include "common.h"
#include "day08.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_day08_part1() {
  const char *data = read_file("../input/day08.txt");
  assert(day08_part1("\"\"\n" "\"abc\"\n" "\"aaa\\\"aaa\"\n" "\"\\x27\"") == 12);
  assert(day08_part1(data) == 1342);
  free((void *) data);
}

void test_day08_part2() {
  const char *data = read_file("../input/day08.txt");
  assert(day08_part2("\"\"\n" "\"abc\"\n" "\"aaa\\\"aaa\"\n" "\"\\x27\"") == 19);
  assert(day08_part2(data) == 2074);
  free((void *) data);
}

int main() {
  test_day08_part1();
  test_day08_part2();

  exit(EXIT_SUCCESS);
}
