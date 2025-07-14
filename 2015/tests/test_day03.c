#include "common.h"
#include "day03.h"

#include <assert.h>
#include <stdlib.h>

void test_day03_part1() {
    const char *data = read_file("../input/day03.txt");
    assert(day03_part1(">").n == 2);
    assert(day03_part1("^>v<").n == 4);
    assert(day03_part1("^v^v^v^v^v").n == 2);
    assert(day03_part1(data).n == 2592);
    free((void *) data);
}

void test_day03_part2() {
    const char *data = read_file("../input/day03.txt");
    assert(day03_part2("^v").n == 3);
    assert(day03_part2("^>v<").n == 3);
    assert(day03_part2("^v^v^v^v^v").n == 11);
    assert(day03_part2(data).n == 2360);
    free((void *) data);
}

int main() {
    test_day03_part1();
    test_day03_part2();

    exit(EXIT_SUCCESS);
}
