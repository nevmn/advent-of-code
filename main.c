#include "common.h"
#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"
#include "day5.h"
#include "day6.h"
#include "day7.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

static struct option long_options[] = {
  {"day", required_argument, NULL, 'd'},
  {"file", required_argument, NULL, 'f'},
  {NULL, 0, NULL, 0}
};

typedef int (*solver)(const char *);

static solver solvers[7][2] = {
  {day1_part1, day1_part2}, {day2_part1, day2_part2},
  {day3_part1, day3_part2}, {day4_part1, day4_part2},
  {day5_part1, day5_part2}, {day6_part1, day6_part2},
  {day7_part1, day7_part2}
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
