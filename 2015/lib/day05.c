#include "common.h"
#include "day05.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static bool has_three_vowels(const char *str) {
  int vowels = 0;
  while (*str != '\0') {
    if (*str == 'a' || *str == 'e' || *str == 'i' || *str == 'o' ||
        *str == 'u') {
      vowels++;
    }
    if (vowels >= 3) {
      return true;
    }
    str++;
  }
  return false;
}

static bool has_pair(const char *str) {
  while (*(str + 1) != '\0') {
    if (*str == *(str + 1)) {
      return true;
    }
    str++;
  }
  return false;
}

static char *bad_strings[4] = {"ab", "cd", "pq", "xy"};

static bool no_bad_strings(const char *str) {
  for (int i = 0; i < 4; i++) {
    if (strstr(str, bad_strings[i]) != NULL) {
      return false;
    }
  }
  return true;
}

Result day05_part1(const char *input) {
  int nice_strings = 0;
  char *line = NULL;
  size_t line_size = 0;
  size_t pos = 0;

  while ((pos = get_next_line(input, pos, &line, &line_size)) > 0) {
    if (has_three_vowels(line) && has_pair(line) && no_bad_strings(line)) {
      nice_strings++;
    }
  }

  free(line);

  return result_int(nice_strings);
}

static bool has_double_pair_no_overlapping(const char *str) {
  const size_t len = strlen(str);
  for (size_t i = 0; i < len - 1; i++) {
    const char pair[2] = {str[i], str[i + 1]};

    for (size_t j = i + 2; j < len - 1; j++) {
      if (str[j] == pair[0] && str[j + 1] == pair[1]) {
        return true;
      }
    }
  }

  return false;
}

static bool has_letter_repeat_with_one_between(const char *str) {
  const size_t len = strlen(str);
  for (size_t i = 0; i < len - 2; i++) {
    if (str[i] == str[i + 2]) {
      return true;
    }
  }

  return false;
}

Result day05_part2(const char *input) {
  int nice_strings = 0;
  char *line = NULL;
  size_t line_size = 0;
  size_t pos = 0;

  while ((pos = get_next_line(input, pos, &line, &line_size)) > 0) {
    if (has_double_pair_no_overlapping(line) &&
        has_letter_repeat_with_one_between(line)) {
      nice_strings++;
    }
  }

  free(line);

  return result_int(nice_strings);
}
