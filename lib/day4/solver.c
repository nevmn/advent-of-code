#include "common.h"
#include "day4.h"

#include <md5.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *str;
  char *hash;
} StrAndHash;

void init_buffers(StrAndHash *buffers) {
  buffers->str = aoc_malloc(100 * sizeof(char));
  buffers->hash = aoc_malloc(MD5_DIGEST_STRING_LENGTH * sizeof(char));
}

void free_buffers(const StrAndHash *buffers) {
  free(buffers->hash);
  free(buffers->str);
}

int find_hash(const char *input, const StrAndHash *buffers, const int zeroes) {
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

int day4_part1(const char *input) {
  StrAndHash buffers;

  init_buffers(&buffers);

  int result = find_hash(input, &buffers, 5);

  free_buffers(&buffers);

  return result;
}

int day4_part2(const char *input) {
  StrAndHash buffers;

  init_buffers(&buffers);

  const int result = find_hash(input, &buffers, 6);

  free_buffers(&buffers);

  return result;
}
