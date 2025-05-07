#include <stdbool.h>
#include <string.h>

#include "day5.h"

#include "common.h"

int MAX_LINE_SIZE = 20;

char *get_next_line(char **input, char *buf) {
  if (**input == '\0') {
    return NULL;
  }

  char *input2 = *input;
  int line_size = 0;
  while (input2[line_size] != '\n' && input2[line_size] != '\0') {
    line_size++;
  }

  if (line_size > MAX_LINE_SIZE) {
    MAX_LINE_SIZE = line_size + 1;
    buf = aoc_realloc(buf, MAX_LINE_SIZE);
  }
  memcpy(buf, *input, line_size);
  buf[line_size] = '\0';

  *input = input2 + line_size + (input2[line_size] == '\n' ? 1 : 0);

  return buf;
}

bool has_three_vowels(char *str) {
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

bool has_pair(char *str) {
  while (*(str + 1) != '\0') {
    if (*str == *(str + 1)) {
      return true;
    }
    str++;
  }
  return false;
}

char *bad_strings[4] = {"ab", "cd", "pq", "xy"};
bool no_bad_strings(char *str) {
  for (int i = 0; i < 4; i++) {
    if (strstr(str, bad_strings[i]) != NULL) {
      return false;
    }
  }
  return true;
}

int day5_part1(char *input) {
  int nice_strings = 0;
  char *current_input = input;
  char *line = aoc_malloc(MAX_LINE_SIZE * sizeof(char));

  while (get_next_line(&current_input, line) != NULL) {
    if (has_three_vowels(line) && has_pair(line) && no_bad_strings(line)) {
      nice_strings++;
    }
  }

  free(line);

  return nice_strings;
}

bool has_double_pair_no_overlapping(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len - 1; i++) {
    char pair[2] = {str[i], str[i + 1]};

    for (int j = i + 2; j < len - 1; j++) {
      if (str[j] == pair[0] && str[j + 1] == pair[1]) {
        return true;
      }
    }
  }

  return false;
}

bool has_letter_repeat_with_one_between(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len - 2; i++) {
    if (str[i] == str[i + 2]) {
      return true;
    }
  }

  return false;
}
int day5_part2(char *input) {
  int nice_strings = 0;
  char *current_input = input;
  char *line = aoc_malloc(MAX_LINE_SIZE * sizeof(char));

  while (get_next_line(&current_input, line) != NULL) {
    if (has_double_pair_no_overlapping(line) &&
        has_letter_repeat_with_one_between(line)) {
      nice_strings++;
    }
  }

  free(line);

  return nice_strings;
}
