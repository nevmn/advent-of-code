#include "common.h"
#include "day05.h"

#include <assert.h>
#include <stdlib.h>

void test_day05_part1() {
    const char *data = read_file("../input/day05.txt");
    assert(day05_part1("ugknbfddgicrmopn") == 1);
    assert(day05_part1("aaa") == 1);
    assert(day05_part1("jchzalrnumimnmhp") == 0);
    assert(day05_part1("haegwjzuvuyypxyu") == 0);
    assert(day05_part1("dvszwmarrgswjxmb") == 0);
    assert(day05_part1(data) == 258);
    free((void *) data);
}

void test_day05_part2() {
    const char *data = read_file("../input/day05.txt");
    assert(day05_part2("qjhvhtzxzqqjkmpb") == 1);
    assert(day05_part2("xxyxx") == 1);
    assert(day05_part2("uurcxstgmygtbstg") == 0);
    assert(day05_part2("ieodomkazucvgmuy") == 0);
    assert(day05_part2(data) == 53);
    free((void *) data);
}

int main() {
    test_day05_part1();
    test_day05_part2();

    exit(EXIT_SUCCESS);
}
