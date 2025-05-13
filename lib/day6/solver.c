#include <assert.h>

#include "common.h"
#include "day6.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int x;
  int y;
  bool status;
  int brightness;
} Light;

Light *grid;

void init_grid() {
  grid = aoc_malloc(1000 * 1000 * sizeof(Light));

  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      grid[i * 1000 + j] = (Light){i, j, false, 0};
    }
  }
}

void free_grid() {
  free(grid);
}

enum Command {
  TurnOn,
  TurnOff,
  Toggle,
};

typedef struct {
  int x1;
  int y1;
  int x2;
  int y2;
  enum Command cmd;
} Command;

void run_command(const Command cmd) {
  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      if (i >= cmd.x1 && i <= cmd.x2 && j >= cmd.y1 && j <= cmd.y2) {
        Light *light = &grid[i * 1000 + j];
        switch (cmd.cmd) {
          case TurnOn:
            light->status = true;
            light->brightness++;
            break;
          case TurnOff:
            light->status = false;
            if (light->brightness > 0) light->brightness--;
            break;
          case Toggle:
            light->status = !light->status;
            light->brightness += 2;
            break;
        }
      }
    }
  }
}

Command parse_command(const char *line) {
  Command cmd = (Command){0, 0, 0, 0};
  if (strstr(line, "turn on")) {
    cmd.cmd = TurnOn;
  } else if (strstr(line, "turn off")) {
    cmd.cmd = TurnOff;
  } else {
    cmd.cmd = Toggle;
  }
  int parsed_count = sscanf(line, "%*[^0-9]%d,%d through %d,%d", &cmd.x1, &cmd.y1, &cmd.x2, &cmd.y2);
  assert(parsed_count == 4);

  return cmd;
}

int day6_part1(const char *input) {
  init_grid();

  char *line = NULL;
  size_t line_size = 0;
  size_t pos = 0;

  while ((pos = get_next_line(input, pos, &line, &line_size)) > 0) {
    run_command(parse_command(line));
  }

  int lit_count = 0;
  for (int i = 0; i < 1000 * 1000; i++) {
    if (grid[i].status) lit_count++;
  }

  free(line);
  free_grid();

  return lit_count;
}

int day6_part2(const char *input) {
  init_grid();

  char *line = NULL;
  size_t line_size = 0;
  size_t pos = 0;

  while ((pos = get_next_line(input, pos, &line, &line_size)) > 0) {
    run_command(parse_command(line));
  }

  int total_brightness = 0;
  for (int i = 0; i < 1000 * 1000; i++) {
    total_brightness += grid[i].brightness;
  }

  free(line);
  free_grid();

  return total_brightness;
}
