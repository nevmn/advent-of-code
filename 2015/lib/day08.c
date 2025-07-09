#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "day08.h"

static int memory_chars(const char *str) {
  int i = 1;
  int size = 0;

  while (str[i] != '\0' && str[i] != '"') {
    if (str[i] == '\\') {
      switch (str[i + 1]) {
        case '\\':
        case '"':
          size++;
          i += 2;
          break;
        case 'x':
          size++;
          i += 4;
          break;
        default:
          size++;
          i++;
          break;
      }
    } else {
      size++;
      i++;
    }
  }

  return size;
}

static int encoded_chars(const char *str) {
  int size = 2;

  while (*str != '\0') {
    if (*str == '\\' || *str == '"') {
      size += 2;
    } else {
      size++;
    }
    str++;
  }

  return size;
}

int day08_part1(const char *input) {
  int result = 0;
  char *line = NULL;
  size_t line_size = 0;
  size_t pos = 0;

  while ((pos = get_next_line(input, pos, &line, &line_size)) > 0) {
    result += (int) strlen(line) - memory_chars(line);
  }

  free(line);

  return result;
}

int day08_part2(const char *input) {
  int result = 0;
  char *line = NULL;
  size_t line_size = 0;
  size_t pos = 0;

  while ((pos = get_next_line(input, pos, &line, &line_size)) > 0) {
    result += encoded_chars(line) - (int) strlen(line);
  }

  free(line);

  return result;
}
