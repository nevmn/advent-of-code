#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "day11.h"

void test_day11_part1() {
  const char *data = read_file("../input/day11.txt");
  assert(strcmp(day11_part1("abcdefgh").value.s, "abcdffaa") == 0);
  assert(strcmp(day11_part1("ghijklmn").value.s, "ghjaabcc") == 0);
  assert(strcmp(day11_part1(data).value.s, "hepxxyzz") == 0);
}

void test_day11_part2() {
  const char *data = read_file("../input/day11.txt");
  assert(strcmp(day11_part2(data).value.s, "heqaabcc") == 0);
}

int main() {
  test_day11_part1();
  test_day11_part2();

  exit(EXIT_SUCCESS);
}
