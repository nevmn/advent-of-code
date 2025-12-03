#include "day20.h"
#include "common.h"

#include <stdlib.h>

static unsigned int solve(const char *input, const int multiplier, const int limit_per_elf) {
  const unsigned int number = atoi(input);
  const unsigned int limit = number / 10;
  unsigned int *presents = aoc_calloc(limit, sizeof(unsigned int));

  for (unsigned int elf = 1; elf <= limit; elf++) {
    unsigned int given = multiplier * elf;
    if (limit_per_elf > 0) {
      for (int i = 1; i <= limit_per_elf; i++) {
        const unsigned int house = elf * i;
        if (house > limit) break;
        presents[house] += given;
      }
    } else {
      for (unsigned int house = elf; house <= limit; house += elf) {
        presents[house] += given;
      }
    }
  }

  unsigned int result = 0;
  for (unsigned int house = 1; house <= limit; ++house) {
    if (presents[house] >= number) {
      result = house;
      break;
    }
  }

  free(presents);

  return result;
}

Result day20_part1(const char *input) {
  return result_int((int) solve(input, 10, 0));
}

Result day20_part2(const char *input) {
  return result_int((int) solve(input, 11, 50));
}
