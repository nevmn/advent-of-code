#include <assert.h>
#include <stdlib.h>

#include "common.h"
#include "day14.h"

static const char *input =
    "Comet can fly 14 km/s for 10 seconds, but then must rest for 127 seconds\n"
    "Dancer can fly 16 km/s for 11 seconds, but then must rest for 162 seconds";

void test_day14_part1() {
  const char *data = read_file("../input/day14.txt");
  assert(day14_part1(data).n == 2460);
}

void test_day14_part2() {
  const char *data = read_file("../input/day14.txt");
  assert(day14_part2(data).n == 1102);
}

int main() {
  // test_day14_part1();
  test_day14_part2();

  exit(EXIT_SUCCESS);
}
