#include "common.h"
#include "day5.h"

#include <assert.h>
#include <stdlib.h>

void test_day5_part1() {
    assert(day5_part1("ugknbfddgicrmopn") == 1);
    assert(day5_part1("aaa") == 1);
    assert(day5_part1("jchzalrnumimnmhp") == 0);
    assert(day5_part1("haegwjzuvuyypxyu") == 0);
    assert(day5_part1("dvszwmarrgswjxmb") == 0);
    const char *data = read_file("../input/day5.txt");
    assert(day5_part1(data) == 258);
    free((void *) data);
}

void test_day5_part2() {
    assert(day5_part2("qjhvhtzxzqqjkmpb") == 1);
    assert(day5_part2("xxyxx") == 1);
    assert(day5_part2("uurcxstgmygtbstg") == 0);
    assert(day5_part2("ieodomkazucvgmuy") == 0);
    const char *data = read_file("../input/day5.txt");
    assert(day5_part2(data) == 53);
    free((void *) data);
}

int main() {
    test_day5_part1();
    test_day5_part2();

    exit(EXIT_SUCCESS);
}
