#include "common.h"
#include "day14.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *name;
  int speed;
  int fly_time;
  int rest_time;
  int distance;
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

static int get_distance(const Horse *horse) {
  int time = 2503;
  int distance = 0;
  bool resting = false;
  while (time > 0) {
    if (resting) {
      time -= horse->rest_time;
      resting = false;
    } else {
      if (time < horse->fly_time) {
        distance += time * horse->speed;
        break;
      }
      distance += horse->speed * horse->fly_time;
      time -= horse->fly_time;
      resting = true;
    }
  }

  return distance;
}

Result day14_part1(const char *input) {
  AocArray *horses = aoc_array_init(10, sizeof(Horse));

  parse_horses(horses, input);

  int result = 0;

  for (int i = 0; i < horses->size; i++) {
    const int distance = get_distance(aoc_array_get(horses, i));
    if (distance > result) {
      result = distance;
    }
  }

  free_horses(horses);

  return result_int(result);
}

Result day14_part2(const char *input) {
  return result_int(0);
}
