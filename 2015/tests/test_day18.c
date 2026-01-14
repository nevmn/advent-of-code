#include "common.h"
#include "day18.h"

#include <assert.h>
#include <stdlib.h>

static const char *input =
    ".#.#.#\n"
    "...##.\n"
    "#....#\n"
    "..#...\n"
    "#.#..#\n"
    "####..";

void test_day18_part1() {
  const char *data = read_file("../input/day18.txt");
  // assert(day18_part1(input).value.n == 4);
  assert(day18_part1(data).value.n == 1061);
  free((void *) data);
}

void test_day18_part2() {
  const char *data = read_file("../input/day18.txt");
  assert(day18_part2(data).value.n == 1006);
  free((void *) data);
}

int main() {
  test_day18_part1();
  test_day18_part2();

  exit(EXIT_SUCCESS);
}
