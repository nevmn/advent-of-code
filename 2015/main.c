#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "day01.h"
#include "day02.h"
#include "day03.h"
#include "day04.h"
#include "day05.h"
#include "day06.h"
#include "day07.h"
#include "day08.h"
#include "day09.h"
#include "day10.h"
#include "day11.h"
#include "day12.h"
#include "day13.h"
#include "day14.h"
#include "day15.h"
#include "day16.h"
#include "day17.h"
#include "day18.h"
#include "day19.h"
#include "day20.h"
#include "day21.h"

static struct option long_options[] = {
  {"day", required_argument, NULL, 'd'},
  {"file", required_argument, NULL, 'f'},
  {NULL, 0, NULL, 0},
};

typedef Result (*solver)(const char *);

static solver solvers[][2] = {
  {day01_part1, day01_part2}, {day02_part1, day02_part2},
  {day03_part1, day03_part2}, {day04_part1, day04_part2},
  {day05_part1, day05_part2}, {day06_part1, day06_part2},
  {day07_part1, day07_part2}, {day08_part1, day08_part2},
  {day09_part1, day09_part2}, {day10_part1, day10_part2},
  {day11_part1, day11_part2}, {day12_part1, day12_part2},
  {day13_part1, day13_part2}, {day14_part1, day14_part2},
  {day15_part1, day15_part2}, {day16_part1, day16_part2},
  {day17_part1, day17_part2}, {day18_part1, day18_part2},
  {day19_part1, day19_part2}, {day20_part1, day20_part2},
  {day21_part1, day21_part2},
};

static void print_result(const char *text, const Result result) {
  if (result.type == RESULT_TYPE_STRING) {
    printf("%s: %s\n", text, result.value.s);
  } else {
    printf("%s: %d\n", text, result.value.n);
  }
}

int main(const int argc, char *argv[]) {
  int ch;
  int day = 0;
  const char *file_path = NULL;
  while ((ch = getopt_long(argc, argv, "d:f:", long_options, NULL)) != -1) {
    switch (ch) {
      case 'd':
        day = atoi(optarg);
        break;
      case 'f':
        file_path = optarg;
        break;
      default: ;
    }
  }
  if (day < 1 || day > 25) {
    printf("valid --day argument with value between 1 and 25 required\n");
    exit(EXIT_FAILURE);
  }
  if (file_path == NULL) {
    printf("--file argument required\n");
    exit(EXIT_FAILURE);
  }

  const char *data = read_file(file_path);

  Result result1 = solvers[day - 1][0](data);
  Result result2 = solvers[day - 1][1](data);

  print_result("part 1 result", result1);
  print_result("part 2 result", result2);

  if (result1.type == RESULT_TYPE_STRING)
    free((void *) result1.value.s);
  if (result2.type == RESULT_TYPE_STRING)
    free((void *) result2.value.s);

  free((void *) data);
  exit(EXIT_SUCCESS);
}