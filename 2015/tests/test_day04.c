#include "common.h"
#include "day04.h"

#include <assert.h>
#include <stdlib.h>

void test_day04_part1() {
  const char *data = read_file("../input/day04.txt");
  assert(day04_part1("abcdef").value.n == 609043);
  assert(day04_part1("pqrstuv").value.n == 1048970);
  // assert(day04_part1(data).value.n == 346386);
  free((void *) data);
}

void test_day04_part2() {
  // const char *data = read_file("../input/day04.txt");
  // assert(day04_part2(data).value.n == 9958218);
  // free((void *) data);
}

int main() {
  test_day04_part1();
  test_day04_part2();

  exit(EXIT_SUCCESS);
}
