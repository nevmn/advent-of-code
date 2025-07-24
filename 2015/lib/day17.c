#include "common.h"
#include "day17.h"

#include <stdlib.h>

#define LITERS_TOTAL 150

typedef struct {
  int count;
  int *containers;
} Containers;

static void get_containers(const char *input, Containers *containers) {
  int lines = 0;
  const char *tmp = (char *) input;
  while (*tmp) {
    if (*tmp == '\n') {
      lines++;
    }
    tmp++;
  }
  if (*(tmp - 1) != '\n') {
    lines++;
  }
  containers->count = lines;

  char *line = NULL;
  size_t len = 0;
  size_t pos = 0;
  containers->containers = aoc_malloc(lines* sizeof(int));

  while ((pos = get_next_line(input, pos, &line, &len)) > 0) {
    containers->containers[--lines] = atoi(line);
  }

  free(line);
}

static void find_combinations_counts(Containers *containers, const int index, const int current_sum,
                                     const int containers_used, int *counts) {
  if (current_sum == LITERS_TOTAL) {
    counts[containers_used]++;
    return;
  }
  if (current_sum > LITERS_TOTAL || index >= containers->count) {
    return;
  }

  find_combinations_counts(containers, index + 1, current_sum + containers->containers[index], containers_used + 1,
                           counts);
  find_combinations_counts(containers, index + 1, current_sum, containers_used, counts);
}


Result day17_part1(const char *input) {
  Containers containers;
  get_containers(input, &containers);

  int *counts = calloc(containers.count + 1, sizeof(int));
  find_combinations_counts(&containers, 0, 0, 0, counts);

  int result = 0;
  for (int i = 0; i <= containers.count; i++) {
    result += counts[i];
  }

  free(counts);
  free(containers.containers);

  return result_int(result);
}

Result day17_part2(const char *input) {
  Containers containers;
  get_containers(input, &containers);

  int *counts = calloc(containers.count + 1, sizeof(int));
  find_combinations_counts(&containers, 0, 0, 0, counts);

  int result = 0;
  for (int i = 0; i <= containers.count; i++) {
    if (counts[i] > 0) {
      result = counts[i];
      break;
    }
  }

  free(counts);
  free(containers.containers);

  return result_int(result);
}
