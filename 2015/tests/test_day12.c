#include <assert.h>
#include <stdlib.h>

#include "common.h"
#include "day12.h"

void test_day12_part1() {
  const char *data = read_file("../input/day12.txt");
  // assert(day12_part1("[1,2,3]").value.n == 6);
  // assert(day12_part1("{\"a\":2,\"b\":4}").value.n == 6);
  // assert(day12_part1("{\"a\":[-1,1]}").value.n == 0);
  // assert(day12_part1("[-1,{\"a\":1}]").value.n == 0);
  assert(day12_part1(data).value.n == 191164);
}

void test_day12_part2() {
  const char *data = read_file("../input/day12.txt");
  // assert(day12_part2("[1,{\"c\":\"red\",\"b\":2},3]").value.n == 4);
  // assert(day12_part2("{\"d\":\"red\",\"e\":[1,2,3,4],\"f\":5}").value.n == 0);
  // assert(day12_part2("[1,\"red\",5]").value.n == 6);
  assert(day12_part2(data).value.n == 87842);
}

int main() {
  test_day12_part1();
  test_day12_part2();

  exit(EXIT_SUCCESS);
}
