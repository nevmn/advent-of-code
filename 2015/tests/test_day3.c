#include "common.h"
#include "day3.h"

#include <assert.h>
#include <stdlib.h>

void test_day3_part1() {
    assert(day3_part1(">") == 2);
    assert(day3_part1("^>v<") == 4);
    assert(day3_part1("^v^v^v^v^v") == 2);
    const char *data = read_file("../input/day3.txt");
    assert(day3_part1(data) == 2592);
    free((void *) data);
}

void test_day3_part2() {
    assert(day3_part2("^v") == 3);
    assert(day3_part2("^>v<") == 3);
    assert(day3_part2("^v^v^v^v^v") == 11);
    const char *data = read_file("../input/day3.txt");
    assert(day3_part2(data) == 2360);
    free((void *) data);
}

int main() {
    test_day3_part1();
    test_day3_part2();

    exit(EXIT_SUCCESS);
}
