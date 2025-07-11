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

static struct option long_options[] = {
  {"day", required_argument, NULL, 'd'},
  {"file", required_argument, NULL, 'f'},
  {NULL, 0, NULL, 0}
};

typedef int (*solver)(const char *);

static solver solvers[][2] = {
  {day01_part1, day01_part2}, {day02_part1, day02_part2},
  {day03_part1, day03_part2}, {day04_part1, day04_part2},
  {day05_part1, day05_part2}, {day06_part1, day06_part2},
  {day07_part1, day07_part2}, {day08_part1, day08_part2},
  {day09_part1, day09_part2}, {day10_part1, day10_part2},
};

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

  const int result1 = solvers[day - 1][0](data);
  const int result2 = solvers[day - 1][1](data);

  printf("part 1 result: %d\n", result1);
  printf("part 2 result: %d\n", result2);

  free((void *) data);
  exit(EXIT_SUCCESS);
}
