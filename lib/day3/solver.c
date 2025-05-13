#include "common.h"
#include "day3.h"

#include <stdlib.h>
#include <string.h>

typedef struct {
  int x;
  int y;
} Position;

typedef struct {
  size_t count;
  size_t capacity;
  Position *positions;
} Houses;

Houses houses;

void init_houses() {
  houses.capacity = 1000;
  houses.positions = aoc_malloc(houses.capacity * sizeof(Position));

  houses.count = 1;
  houses.positions[0] = (Position){0, 0};
}

void free_houses() { free(houses.positions); }

void add_position(Position pos) {
  for (size_t i = 0; i < houses.count; i++) {
    if (houses.positions[i].x == pos.x && houses.positions[i].y == pos.y) {
      return;
    }
  }

  if (houses.count >= houses.capacity) {
    size_t new_capacity = houses.capacity * 2;
    houses.positions =
        aoc_realloc(houses.positions, new_capacity * sizeof(Position));
    houses.capacity = new_capacity;
  }

  houses.positions[houses.count++] = pos;
}

int day3_part1(const char *input) {
  init_houses();

  Position current = {0, 0};

  while (*input) {
    switch (*input) {
      case '^':
        current.y++;
        break;
      case '>':
        current.x++;
        break;
      case 'v':
        current.y--;
        break;
      case '<':
        current.x--;
        break;
      default:
        continue;
    }
    add_position(current);
    input++;
  }

  const int result = (int) houses.count;

  free_houses();
  return result;
}

int day3_part2(const char *input) {
  init_houses();

  Position santa = {0, 0};
  Position robot = {0, 0};

  for (size_t i = 0; i < strlen(input); i++) {
    Position *current = i % 2 == 0 ? &santa : &robot;
    switch (input[i]) {
      case '^':
        current->y++;
        break;
      case '>':
        current->x++;
        break;
      case 'v':
        current->y--;
        break;
      case '<':
        current->x--;
        break;
      default:
        continue;
    }
    add_position(*current);
  }

  const int result = (int) houses.count;

  free_houses();
  return result;
}
