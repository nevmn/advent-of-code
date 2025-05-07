#include "common.h"
#include "day2.h"

#include <assert.h>
#include <stdlib.h>

void test_day2_part1() {
    assert(day2_part1("2x3x4") == 58);
    assert(day2_part1("1x1x10") == 43);
    const char *data = read_file("../input/day2.txt");
    assert(day2_part1(data) == 1588178);
    free((void *) data);
}

void test_day2_part2() {
    assert(day2_part2("2x3x4") == 34);
    assert(day2_part2("1x1x10") == 14);
    const char *data = read_file("../input/day2.txt");
    assert(day2_part2(data) == 3783758);
    free((void *) data);
}

int main() {
    test_day2_part1();
    test_day2_part2();

    exit(EXIT_SUCCESS);
}
