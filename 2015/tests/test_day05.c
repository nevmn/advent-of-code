#include "common.h"
#include "day05.h"

#include <assert.h>
#include <stdlib.h>

void test_day05_part1() {
    const char *data = read_file("../input/day05.txt");
    assert(day05_part1("ugknbfddgicrmopn").n == 1);
    assert(day05_part1("aaa").n == 1);
    assert(day05_part1("jchzalrnumimnmhp").n == 0);
    assert(day05_part1("haegwjzuvuyypxyu").n == 0);
    assert(day05_part1("dvszwmarrgswjxmb").n == 0);
    assert(day05_part1(data).n == 258);
    free((void *) data);
}

void test_day05_part2() {
    const char *data = read_file("../input/day05.txt");
    assert(day05_part2("qjhvhtzxzqqjkmpb").n == 1);
    assert(day05_part2("xxyxx").n == 1);
    assert(day05_part2("uurcxstgmygtbstg").n == 0);
    assert(day05_part2("ieodomkazucvgmuy").n == 0);
    assert(day05_part2(data).n == 53);
    free((void *) data);
}

int main() {
    test_day05_part1();
    test_day05_part2();

    exit(EXIT_SUCCESS);
}
