#include "common.h"
#include "day15.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPOONS_COUNT 100
#define CALORIES_LIMIT 500

typedef struct {
  int capacity;
  int durability;
  int flavor;
  int texture;
  int calories;
} Ingredient;

typedef struct {
  int *amount;
  int ingredients_count;
  int total_spoons;
} Distribution;

static void parse_ingredient(const char *input, AocArray *ingredients) {
  char *line = NULL;
  size_t line_size = 0;
  size_t pos = 0;

  while ((pos = get_next_line(input, pos, &line, &line_size)) > 0) {
    const char *tmp = strchr(line, ':');
    Ingredient ingredient = {0};
    const int parsed_count = sscanf(tmp, ": capacity %d, durability %d, flavor %d, texture %d, calories %d",
                                    &ingredient.capacity,
                                    &ingredient.durability,
                                    &ingredient.flavor,
                                    &ingredient.texture,
                                    &ingredient.calories);
    assert(parsed_count == 5);
    aoc_array_append(ingredients, &ingredient);
  }

  free(line);
}

static Distribution *init_distribution(const int ingredients_count) {
  Distribution *dist = aoc_malloc(sizeof(Distribution));
  dist->amount = aoc_calloc(ingredients_count, sizeof(int));
  dist->ingredients_count = ingredients_count;
  dist->total_spoons = SPOONS_COUNT;
  dist->amount[ingredients_count - 1] = SPOONS_COUNT;
  return dist;
}

static bool next_distribution(const Distribution *dist) {
  int i = dist->ingredients_count - 2;
  
  while (i >= 0) {
    int current_sum = 0;
    for (int j = 0; j <= i; j++) {
      current_sum += dist->amount[j];
    }
    
    if (current_sum < dist->total_spoons) {
      dist->amount[i]++;
      
      int remaining = dist->total_spoons;
      for (int j = 0; j <= i; j++) {
        remaining -= dist->amount[j];
      }
      
      for (int j = i + 1; j < dist->ingredients_count - 1; j++) {
        dist->amount[j] = 0;
      }
      dist->amount[dist->ingredients_count - 1] = remaining;
      
      return true;
    }
    
    dist->amount[i] = 0;
    i--;
  }
  
  return false;
}

static int calculate_score(const AocArray *ingredients, const Distribution *dist) {
  int capacity = 0, durability = 0, flavor = 0, texture = 0;

  for (int i = 0; i < ingredients->size; i++) {
    const Ingredient *ingredient = aoc_array_get(ingredients, i);
    const int amount = dist->amount[i];

    capacity += ingredient->capacity * amount;
    durability += ingredient->durability * amount;
    flavor += ingredient->flavor * amount;
    texture += ingredient->texture * amount;
  }

  if (capacity < 0) capacity = 0;
  if (durability < 0) durability = 0;
  if (flavor < 0) flavor = 0;
  if (texture < 0) texture = 0;

  return capacity * durability * flavor * texture;
}

static int calculate_calories(const AocArray *ingredients, const Distribution *dist) {
  int calories = 0;
  for (int i = 0; i < ingredients->size; i++) {
    const Ingredient *ingredient = aoc_array_get(ingredients, i);
    calories += ingredient->calories * dist->amount[i];
  }
  return calories;
}

static int find_max_score(const char *input, const bool check_calories) {
  AocArray *ingredients = aoc_array_init(5, sizeof(Ingredient));
  parse_ingredient(input, ingredients);

  Distribution *dist = init_distribution((int) ingredients->size);
  int max_score = 0;

  do {
    if (!check_calories || calculate_calories(ingredients, dist) == CALORIES_LIMIT) {
      const int score = calculate_score(ingredients, dist);
      if (score > max_score) {
        max_score = score;
      }
    }
  } while (next_distribution(dist));

  free(dist->amount);
  free(dist);
  aoc_array_free(ingredients);

  return max_score;
}

Result day15_part1(const char *input) {
  return result_int(find_max_score(input, false));
}

Result day15_part2(const char *input) {
  return result_int(find_max_score(input, true));
}