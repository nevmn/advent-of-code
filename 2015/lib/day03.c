#include "common.h"
#include "day03.h"

#include <string.h>
#include <stdbool.h>

typedef struct {
  int x;
  int y;
} Position;

static bool house_visited(const Position *pos, const AocArray *houses) {
  for (size_t i = 0; i < houses->size; i++) {
    const Position *house = aoc_array_get(houses, i);
    if (house->x == pos->x && house->y == pos->y) {
      return true;
    }
  }
  return false;
}

int day03_part1(const char *input) {
  AocArray *houses = aoc_array_init(1000, sizeof(Position));

  Position current = {0, 0};
  aoc_array_append(houses, &current);

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

    if (!house_visited(&current, houses)) {
      aoc_array_append(houses, &current);
    }
    input++;
  }

  const int result = (int) houses->size;

  aoc_array_free(houses);
  return result;
}

int day03_part2(const char *input) {
  AocArray *houses = aoc_array_init(1000, sizeof(Position));

  Position santa = {0, 0};
  Position robot = {0, 0};
  aoc_array_append(houses, &santa);

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
    if (!house_visited(current, houses)) {
      aoc_array_append(houses, current);
    }
  }

  const int result = (int) houses->size;

  aoc_array_free(houses);
  return result;
}
