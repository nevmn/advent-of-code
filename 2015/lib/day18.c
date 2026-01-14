#include "common.h"
#include "day18.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define GRID_SIZE 100
#define STEPS 100

typedef struct {
  int x;
  int y;
  bool status;
} Light;

static Light *grid;

static void init_grid(const char *input) {
  grid = aoc_malloc(GRID_SIZE * GRID_SIZE * sizeof(Light));

  char *line = NULL;
  size_t line_size = 0;
  size_t pos = 0;

  for (int i = 0; i < GRID_SIZE; i++) {
    pos = get_next_line(input, pos, &line, &line_size);

    for (int j = 0; j < GRID_SIZE; j++) {
      bool status = false;
      if (line[j] == '#') status = true;
      grid[i * GRID_SIZE + j] = (Light){i, j, status};
    }
  }

  free(line);
}

static void free_grid() {
  free(grid);
}

static void make_step(bool corners_stuck) {
  Light *new_grid = aoc_malloc(GRID_SIZE * GRID_SIZE * sizeof(Light));

  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      if (corners_stuck && (
            (i == 0 && j == 0) ||
            (i == 0 && j == GRID_SIZE - 1) ||
            (i == GRID_SIZE - 1 && j == 0) ||
            (i == GRID_SIZE - 1 && j == GRID_SIZE - 1)
          )) {
        new_grid[i * GRID_SIZE + j] = (Light){i, j, true};
        continue;
      }

      const Light *light = &grid[i * GRID_SIZE + j];
      int neighbors = 0;
      for (int x = i - 1; x <= i + 1; x++) {
        for (int y = j - 1; y <= j + 1; y++) {
          if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && !(x == i && y == j)) {
            neighbors += grid[x * GRID_SIZE + y].status;
          }
        }
      }
      bool new_status = neighbors == 3 || (light->status && neighbors == 2);
      new_grid[i * GRID_SIZE + j] = (Light){i, j, new_status};
    }
  }

  free(grid);
  grid = new_grid;
}


Result day18_part1(const char *input) {
  init_grid(input);

  for (int i = 0; i < STEPS; i++) {
    make_step(false);
  }

  int result = 0;
  for (int i = 0; i < GRID_SIZE * GRID_SIZE; i++) {
    result += grid[i].status;
  }

  free_grid();

  return result_int(result);
}

Result day18_part2(const char *input) {
  init_grid(input);

  grid[0].status = true;
  grid[GRID_SIZE - 1].status = true;
  grid[(GRID_SIZE - 1) * GRID_SIZE].status = true;
  grid[GRID_SIZE * GRID_SIZE - 1].status = true;

  for (int i = 0; i < STEPS; i++) {
    make_step(true);
  }

  int result = 0;
  for (int i = 0; i < GRID_SIZE * GRID_SIZE; i++) {
    result += grid[i].status;
  }

  free_grid();

  return result_int(result);
}
