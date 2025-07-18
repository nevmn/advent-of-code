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

static struct option long_options[] = {
  {"day", required_argument, NULL, 'd'},
  {"file", required_argument, NULL, 'f'},
  {NULL, 0, NULL, 0}
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
};

static void print_result(const char *text, const Result result) {
  if (result.s != NULL) {
    printf("%s: %s\n", text, result.s);
  } else {
    printf("%s: %d\n", text, result.n);
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

  if (result1.s != NULL)
    free((void *) result1.s);
  if (result2.s != NULL)
    free((void *) result2.s);

  free((void *) data);
  exit(EXIT_SUCCESS);
}
