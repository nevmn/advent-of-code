#include <assert.h>
#include <stdlib.h>

#include "common.h"
#include "day15.h"

static const char *input =
    "Butterscotch: capacity -1, durability -2, flavor 6, texture 3, calories 8\n"
    "Cinnamon: capacity 2, durability 3, flavor -2, texture -1, calories 3";

void test_day15_part1() {
  const char *data = read_file("../input/day15.txt");
  assert(day15_part1(input).n == 62842880);
  assert(day15_part1(data).n == 13882464);
}

void test_day15_part2() {
  const char *data = read_file("../input/day15.txt");
  assert(day15_part2(input).n == 57600000);
  assert(day15_part2(data).n == 11171160);
}

int main() {
  test_day15_part1();
  test_day15_part2();

  exit(EXIT_SUCCESS);
}
