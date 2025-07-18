#include "common.h"
#include "day14.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SECONDS 2503
// #define MAX_SECONDS 1000

typedef struct {
  char *name;
  int speed;
  int fly_time;
  int rest_time;
  int distance;
  int score;
  bool resting;
  int until_rest;
  int until_fly;
} Horse;

static void parse_horses(AocArray *horses, const char *input) {
  char *line = NULL;
  size_t line_size = 0;
  size_t pos = 0;

  while ((pos = get_next_line(input, pos, &line, &line_size)) > 0) {
    Horse horse = {0};
    char name[100];
    const int parsed_count = sscanf(line, "%s can fly %d km/s for %d seconds, but then must rest for %d seconds",
                                    name,
                                    &horse.speed,
                                    &horse.fly_time,
                                    &horse.rest_time);
    assert(parsed_count == 4);
    horse.name = aoc_malloc((strlen(name) + 1)*sizeof(char));
    strcpy(horse.name, name);
    horse.name[strlen(name)] = '\0';
    horse.until_rest = horse.fly_time;

    aoc_array_append(horses, &horse);
  }

  free(line);
}

static void free_horses(AocArray *horses) {
  for (int i = 0; i < horses->size; i++) {
    Horse *horse = aoc_array_get(horses, i);
    free(horse->name);
  }
  aoc_array_free(horses);
}

static void tick(const AocArray *horses) {
  int max_distance = 0;
  for (int i = 0; i < horses->size; i++) {
    Horse *horse = aoc_array_get(horses, i);
    if (horse->resting) {
      horse->until_fly--;
      if (horse->until_fly == 0) {
        horse->until_rest = horse->fly_time;
        horse->until_fly = horse->rest_time;
        horse->resting = false;
      }
    } else {
      horse->until_rest--;
      if (horse->until_rest == 0) {
        horse->until_rest = horse->fly_time;
        horse->until_fly = horse->rest_time;
        horse->resting = true;
      }
      horse->distance += horse->speed;
    }
    if (horse->distance > max_distance) {
      max_distance = horse->distance;
    }
  }

  for (int i = 0; i < horses->size; ++i) {
    Horse *horse = aoc_array_get(horses, i);
    if (horse->distance == max_distance) {
      horse->score++;
    }
  }
}

typedef int (*ResultCalculator)(const Horse *);

static int calculate_distance(const Horse *horse) {
  return horse->distance;
}

static int calculate_score(const Horse *horse) {
  return horse->score;
}

static int simulate_race(const char *input, const ResultCalculator calculator) {
  AocArray *horses = aoc_array_init(10, sizeof(Horse));

  parse_horses(horses, input);

  for (int i = 0; i < MAX_SECONDS; ++i) {
    tick(horses);
  }

  int result = 0;
  for (int i = 0; i < horses->size; ++i) {
    const Horse *horse = aoc_array_get(horses, i);
    const int value = calculator(horse);
    if (value > result) {
      result = value;
    }
  }

  free_horses(horses);

  return result;
}

Result day14_part1(const char *input) {
  return result_int(simulate_race(input, calculate_distance));
}

Result day14_part2(const char *input) {
  return result_int(simulate_race(input, calculate_score));
}