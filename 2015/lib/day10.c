#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "day10.h"

typedef struct {
  char *data;
  size_t size;
} Result;

void create_sequence(const char *input, AocArray *result) {
  char current_ch = input[0];
  const char *tmp = (char *) input + 1;
  char ch;
  int count = 1;
  while ((ch = *tmp++) != '\0') {
    if (ch == current_ch) {
      count++;
    } else {
      const char c = (char) (count + '0');
      aoc_array_append(result, &c);
      aoc_array_append(result, &current_ch);
      current_ch = ch;
      count = 1;
    }
  }
  const char c = (char) (count + '0');
  aoc_array_append(result, &c);
  aoc_array_append(result, &current_ch);
}

int expand_sequence(const char *input, const int times) {
  AocArray *chars = aoc_array_init(10, sizeof(char));
  create_sequence(input, chars);
  Result result = {
    .data = aoc_malloc(chars->size + 1),
    .size = chars->size,
  };
  snprintf(result.data, chars->size + 1, "%s", (char *) aoc_array_get(chars, 0));

  for (int i = 0; i < times - 1; ++i) {
    aoc_array_reset(chars);
    create_sequence(result.data, chars);
    if (chars->size > result.size) {
      result.size = chars->size;
      result.data = aoc_realloc(result.data, chars->size + 1);
    }
    snprintf(result.data, chars->size + 1, "%s", (char *) aoc_array_get(chars, 0));
  }

  const int res = (int) result.size;

  aoc_array_free(chars);
  free(result.data);

  return res;
}

int day10_part1(const char *input) {
  return expand_sequence(input, 40);
}

int day10_part2(const char *input) {
  return expand_sequence(input, 50);
}
