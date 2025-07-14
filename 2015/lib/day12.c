#include <jq.h>

#include "common.h"
#include "day12.h"

#include <stdlib.h>

typedef struct {
  double *numbers;
  size_t count;
  size_t capacity;
} Numbers;

void extract_number(Numbers *numbers, const char * input, const char *filter) {
  jq_state *jq = jq_init();
  jq_compile(jq, filter);

  const jv json_input = jv_parse(input);
  jq_start(jq, json_input, 0);

  jv result;
  while (jv_is_valid(result = jq_next(jq))) {
    if (jv_get_kind(result) == JV_KIND_NUMBER) {
      const double num = jv_number_value(result);
      if (numbers->count == numbers->capacity) {
        numbers->capacity *= 2;
        numbers->numbers = aoc_realloc(numbers->numbers, numbers->capacity * sizeof(double));
      }
      numbers->numbers[numbers->count++] = num;
    }
    jv_free(result);
  }

  jv_free(json_input);
  jq_teardown(&jq);
}

Result day12_part1(const char *input) {
  Numbers numbers = {0};
  numbers.capacity = 1000;
  numbers.numbers = aoc_malloc(numbers.capacity * sizeof(double));

  const char filter[] = ".. | numbers";

  extract_number(&numbers, input, filter);

  int result = 0;
  for (size_t i = 0; i < numbers.count; ++i) {
    result += (int) numbers.numbers[i];
  }

  free(numbers.numbers);

  return result_int(result);
}

Result day12_part2(const char *input) {
  Numbers numbers = {0};
  numbers.capacity = 1000;
  numbers.numbers = aoc_malloc(numbers.capacity * sizeof(double));

  const char filter[] = "def sum_without_red:\n"
  "if type == \"number\" then .\n"
  "elif type == \"array\" then map(sum_without_red) | add\n"
  "elif type == \"object\" then\n"
    "if any(.[]; . == \"red\") then 0\n"
    "else map_values(sum_without_red) | add\n"
    "end\n"
  "else 0\n"
  "end;\n"
"sum_without_red";

  extract_number(&numbers, input, filter);

  int result = 0;
  for (size_t i = 0; i < numbers.count; ++i) {
    result += (int) numbers.numbers[i];
  }

  free(numbers.numbers);

  return result_int(result);
}
