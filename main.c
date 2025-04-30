#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "day1.h"
#include "day2.h"
#include "day3.h"

static struct option long_options[] = {{"day", required_argument, NULL, 'd'},
                                       {"file", required_argument, NULL, 'f'},
                                       {NULL, 0, NULL, 0}};

typedef int (*solver)(char *);
static solver solvers[3][2] = {{day1_part1, day1_part2},
                               {day2_part1, day2_part2},
                               {day3_part1, day3_part2}};

int main(int argc, char *argv[]) {
  int ch;
  int day = 0;
  char *file_path = NULL;
  while ((ch = getopt_long(argc, argv, "d:f:", long_options, NULL)) != -1) {
    switch (ch) {
    case 'd':
      day = atoi(optarg);
      break;
    case 'f':
      file_path = optarg;
      break;
    }
  }
  if (day < 1 || day > 25) {
    printf("valid --day argument with value between 1 and 25 required\n");
    exit(1);
  }
  if (file_path == NULL) {
    printf("--file argument required\n");
    exit(1);
  }

  FILE *input_file = fopen(file_path, "r");
  if (input_file == NULL) {
    perror("ERROR: Cannot open file");
    exit(EXIT_FAILURE);
  }

  fseek(input_file, 0L, SEEK_END);
  long file_size = ftell(input_file);
  if (file_size == -1) {
    perror("ERROR: Cannot read file size");
    exit(EXIT_FAILURE);
  }
  rewind(input_file);

  char *buffer = aoc_malloc((file_size + 1) * sizeof(char));

  size_t read = fread(buffer, sizeof(char), file_size, input_file);
  if (read != (unsigned)file_size) {
    free(buffer);
    perror("ERROR: Error reading file");
    exit(EXIT_FAILURE);
  }

  buffer[file_size] = '\0';
  fclose(input_file);

  int result1 = solvers[day - 1][0](buffer);
  int result2 = solvers[day - 1][1](buffer);

  printf("part 1 result: %d\n", result1);
  printf("part 2 result: %d\n", result2);

  free(buffer);
  exit(0);
}
