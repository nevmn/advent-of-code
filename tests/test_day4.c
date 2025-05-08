#include "common.h"
#include "day4.h"

#include <assert.h>
#include <stdlib.h>

void test_day4_part1() {
    assert(day4_part1("abcdef") == 609043);
    assert(day4_part1("pqrstuv") == 1048970);
    const char *data = read_file("../input/day4.txt");
    assert(day4_part1(data) == 346386);
    free((void *) data);
}

void test_day4_part2() {
    const char *data = read_file("../input/day4.txt");
    assert(day4_part2(data) == 9958218);
    free((void *) data);
}

int main() {
    test_day4_part1();
    test_day4_part2();

    exit(EXIT_SUCCESS);
}
