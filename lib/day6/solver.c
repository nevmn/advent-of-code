#include "common.h"
#include "day6.h"

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  int x;
  int y;
  bool status;
} Light;

Light *grid;

void init_grid() {
  grid = aoc_malloc(1000 * 1000 * sizeof(Light));

  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      grid[i * 1000 + j] = (Light){i, j, false};
    }
  }
}

void free_grid() { free(grid); }

int day6_part1(const char *input) {
  init_grid();

  free_grid();
  return 0;
}

int day6_part2(const char *input) {
  //
  return 0;
}
