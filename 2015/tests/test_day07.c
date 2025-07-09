#include "common.h"
#include "day07.h"

#include <assert.h>
#include <stdlib.h>

void test_day07_part1() {
  const char *data = read_file("../input/day07.txt");
  assert(day07_part1(data) == 3176);
  free((void *) data);
}

void test_day07_part2() {
  const char *data = read_file("../input/day07.txt");
  assert(day07_part2(data) == 14710);
  free((void *) data);
}

int main() {
  test_day07_part1();
  test_day07_part2();

  exit(EXIT_SUCCESS);
}
