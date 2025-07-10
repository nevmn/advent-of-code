#include "common.h"
#include "day04.h"

#include <md5.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *str;
  char *hash;
} StrAndHash;

static void init_buffers(StrAndHash *buffers) {
  buffers->str = aoc_malloc(100 * sizeof(char));
  buffers->hash = aoc_malloc(MD5_DIGEST_STRING_LENGTH * sizeof(char));
}

static void free_buffers(const StrAndHash *buffers) {
  free(buffers->hash);
  free(buffers->str);
}

static int find_hash(const char *input, const StrAndHash *buffers, const int zeroes) {
  char zeroe_str[zeroes + 1];
  for (int i = 0; i < zeroes; i++) {
    strcpy(zeroe_str + i, "0");
  }
  zeroe_str[zeroes] = '\0';

  int i = 0;

  do {
    i++;
    snprintf(buffers->str, 100, "%s%d", input, i);

    MD5Data((const uint8_t *) buffers->str, strlen(buffers->str), buffers->hash);
  } while (memcmp(buffers->hash, zeroe_str, zeroes) != 0);

  return i;
}

int day04_part1(const char *input) {
  StrAndHash buffers;

  init_buffers(&buffers);

  const int result = find_hash(input, &buffers, 5);

  free_buffers(&buffers);

  return result;
}

int day04_part2(const char *input) {
  StrAndHash buffers;

  init_buffers(&buffers);

  const int result = find_hash(input, &buffers, 6);

  free_buffers(&buffers);

  return result;
}
