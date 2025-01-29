#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "day1.h"
#include "day2.h"

static struct option long_options[] = {{"day", required_argument, NULL, 'd'},
                                       {"file", required_argument, NULL, 'f'},
                                       {NULL, 0, NULL, 0}};

typedef int (*solver)(char *);
static solver solvers[2][2] = {{day1_part1, day1_part2},
                               {day2_part1, day2_part2}};

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
  if (!input_file) {
    perror("ERROR: Cannot open file");
    exit(1);
  }

  fseek(input_file, 0L, SEEK_END);
  long file_size = ftell(input_file);
  if (file_size == -1L) {
    perror("ERROR: Cannot read file size");
    exit(1);
  }
  rewind(input_file);

  char *input = (char *)malloc((file_size + 1) * sizeof(char));
  fread(input, sizeof(char), file_size, input_file);
  if (ferror(input_file) != 0) {
    fputs("ERROR: Cannot read file", stderr);
  } else {
    input[file_size] = '\0';
  }

  int result1 = solvers[day - 1][0](input);
  int result2 = solvers[day - 1][1](input);

  printf("part 1 result: %d\n", result1);
  printf("part 2 result: %d\n", result2);

  free(input);
  fclose(input_file);
  exit(0);
}
