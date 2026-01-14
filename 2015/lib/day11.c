#include "common.h"
#include "day11.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static void increment(char *password, int place) {
  if (place < 0) {
    return;
  }
  password[place] = (char) (password[place] + 1);
  if (password[place] > 'z') {
    password[place] = 'a';
    increment(password, place - 1);
  }
}

static bool no_banned(const char *password) {
  for (size_t i = 0; i < strlen(password); ++i) {
    if (password[i] == 'i' || password[i] == 'o' || password[i] == 'l') {
      return false;
    }
  }

  return true;
}

static bool has_two_double(const char *password) {
  for (size_t i = 0; i < strlen(password) - 1; ++i) {
    if (password[i] == password[i + 1]) {
      for (size_t j = i + 2; j < strlen(password) - 1; ++j) {
        if (password[j] == password[j + 1] && password[i] != password[j]) {
          return true;
        }
      }
    }
  }

  return false;
}

static bool has_alphabetical_sequence(const char *password) {
  for (size_t i = 0; i < strlen(password) - 2; ++i) {
    if (password[i + 1] == password[i] + 1 && password[i + 2] == password[i] + 2) {
      return true;
    }
  }

  return false;
}

Result day11_part1(const char *input) {
  char password[strlen(input) + 1];
  strncpy(password, input, strlen(input) + 1);

  while (!no_banned(password) || !has_two_double(password) || !has_alphabetical_sequence(password)) {
    increment(password, (int) strlen(password) - 1);
  }

  char *result = aoc_malloc(strlen(password) + 1);
  strncpy(result, password, strlen(password) + 1);

  return result_str(result);
}

Result day11_part2(const char *input) {
  const Result res = day11_part1(input);
  char s[strlen(res.value.s)];
  strncpy(s, res.value.s, strlen(res.value.s) + 1);
  increment(s, (int) strlen(s) - 1);

  free((void *) res.value.s);

  return day11_part1(s);
}
