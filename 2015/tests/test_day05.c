#include "common.h"
#include "day05.h"

#include <assert.h>
#include <stdlib.h>

void test_day05_part1() {
  const char *data = read_file("../input/day05.txt");
  assert(day05_part1("ugknbfddgicrmopn").value.n == 1);
  assert(day05_part1("aaa").value.n == 1);
  assert(day05_part1("jchzalrnumimnmhp").value.n == 0);
  assert(day05_part1("haegwjzuvuyypxyu").value.n == 0);
  assert(day05_part1("dvszwmarrgswjxmb").value.n == 0);
  assert(day05_part1(data).value.n == 258);
  free((void *) data);
}

void test_day05_part2() {
  const char *data = read_file("../input/day05.txt");
  assert(day05_part2("qjhvhtzxzqqjkmpb").value.n == 1);
  assert(day05_part2("xxyxx").value.n == 1);
  assert(day05_part2("uurcxstgmygtbstg").value.n == 0);
  assert(day05_part2("ieodomkazucvgmuy").value.n == 0);
  assert(day05_part2(data).value.n == 53);
  free((void *) data);
}

int main() {
  test_day05_part1();
  test_day05_part2();

  exit(EXIT_SUCCESS);
}
