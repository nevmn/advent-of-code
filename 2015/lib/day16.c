#include "common.h"
#include "day16.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int number;
  int children;
  int cats;
  int samoyeds;
  int pomeranians;
  int akitas;
  int vizslas;
  int goldfish;
  int trees;
  int cars;
  int perfumes;
} Sue;

static const char *regex_pattern = "Sue ([0-9]+): ([a-z]+): ([0-9]+), ([a-z]+): ([0-9]+), ([a-z]+): ([0-9]+)";

static const Sue sue_template = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

static const Sue target_sue = {
  .children = 2,
  .cats = 7,
  .samoyeds = 2,
  .pomeranians = 3,
  .akitas = 0,
  .vizslas = 0,
  .goldfish = 5,
  .trees = 3,
  .cars = 2,
  .perfumes = 1,
};

static void fill_sue(Sue *sue, const char *prop, const char *value) {
  if (strcmp(prop, "children") == 0) {
    sue->children = atoi(value);
  } else if (strcmp(prop, "cats") == 0) {
    sue->cats = atoi(value);
  } else if (strcmp(prop, "samoyeds") == 0) {
    sue->samoyeds = atoi(value);
  } else if (strcmp(prop, "pomeranians") == 0) {
    sue->pomeranians = atoi(value);
  } else if (strcmp(prop, "akitas") == 0) {
    sue->akitas = atoi(value);
  } else if (strcmp(prop, "vizslas") == 0) {
    sue->vizslas = atoi(value);
  } else if (strcmp(prop, "goldfish") == 0) {
    sue->goldfish = atoi(value);
  } else if (strcmp(prop, "trees") == 0) {
    sue->trees = atoi(value);
  } else if (strcmp(prop, "cars") == 0) {
    sue->cars = atoi(value);
  } else if (strcmp(prop, "perfumes") == 0) {
    sue->perfumes = atoi(value);
  }
}

static void fill_sues(const char *input, AocArray *sues) {
  regex_t regex;
  regmatch_t matches[8];
  if (regcomp(&regex, regex_pattern, REG_EXTENDED) != 0) {
    fprintf(stderr, "Failed to compile regex\n");
    exit(EXIT_FAILURE);
  }

  char *line = NULL;
  size_t line_size = 0;
  size_t pos = 0;
  while ((pos = get_next_line(input, pos, &line, &line_size)) > 0) {
    if (regexec(&regex, line, 8, matches, 0) == 0) {
      Sue sue = sue_template;
      sue.number = atoi(line + matches[1].rm_so);

      char prop1[matches[2].rm_eo - matches[2].rm_so + 1];
      strncpy(prop1, line + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
      prop1[matches[2].rm_eo - matches[2].rm_so] = '\0';

      char value1[matches[3].rm_eo - matches[3].rm_so + 1];
      strncpy(value1, line + matches[3].rm_so, matches[3].rm_eo - matches[3].rm_so);
      value1[matches[3].rm_eo - matches[3].rm_so] = '\0';

      char prop2[matches[4].rm_eo - matches[4].rm_so + 1];
      strncpy(prop2, line + matches[4].rm_so, matches[4].rm_eo - matches[4].rm_so);
      prop2[matches[4].rm_eo - matches[4].rm_so] = '\0';

      char value2[matches[5].rm_eo - matches[5].rm_so + 1];
      strncpy(value2, line + matches[5].rm_so, matches[5].rm_eo - matches[5].rm_so);
      value2[matches[5].rm_eo - matches[5].rm_so] = '\0';

      char prop3[matches[6].rm_eo - matches[6].rm_so + 1];
      strncpy(prop3, line + matches[6].rm_so, matches[6].rm_eo - matches[6].rm_so);
      prop3[matches[6].rm_eo - matches[6].rm_so] = '\0';

      char value3[matches[7].rm_eo - matches[7].rm_so + 1];
      strncpy(value3, line + matches[7].rm_so, matches[7].rm_eo - matches[7].rm_so);
      value3[matches[7].rm_eo - matches[7].rm_so] = '\0';

      fill_sue(&sue, prop1, value1);
      fill_sue(&sue, prop2, value2);
      fill_sue(&sue, prop3, value3);

      aoc_array_append(sues, &sue);
    }
  }

  free(line);
  regfree(&regex);
}

static int find_sue(const AocArray *sues, bool part_two) {
  for (int i = 0; i < sues->size; ++i) {
    bool maybe_found = true;
    const Sue *sue = aoc_array_get(sues, i);
    if (sue->children > -1) {
      maybe_found = sue->children == target_sue.children;
    }
    if (sue->cats > -1) {
      if (part_two) maybe_found = maybe_found && sue->cats > target_sue.cats;
      else maybe_found = maybe_found && sue->cats == target_sue.cats;
    }
    if (sue->samoyeds > -1) {
      maybe_found = maybe_found && sue->samoyeds == target_sue.samoyeds;
    }
    if (sue->pomeranians > -1) {
      if (part_two) maybe_found = maybe_found && sue->pomeranians < target_sue.pomeranians;
      else maybe_found = maybe_found && sue->pomeranians == target_sue.pomeranians;
    }
    if (sue->akitas > -1) {
      maybe_found = maybe_found && sue->akitas == target_sue.akitas;
    }
    if (sue->vizslas > -1) {
      maybe_found = maybe_found && sue->vizslas == target_sue.vizslas;
    }
    if (sue->goldfish > -1) {
      if (part_two) maybe_found = maybe_found && sue->goldfish < target_sue.goldfish;
      else maybe_found = maybe_found && sue->goldfish == target_sue.goldfish;
    }
    if (sue->trees > -1) {
      if (part_two) maybe_found = maybe_found && sue->trees > target_sue.trees;
      else maybe_found = maybe_found && sue->trees == target_sue.trees;
    }
    if (sue->cars > -1) {
      maybe_found = maybe_found && sue->cars == target_sue.cars;
    }
    if (sue->perfumes > -1) {
      maybe_found = maybe_found && sue->perfumes == target_sue.perfumes;
    }
    if (maybe_found) {
      return sue->number;
    }
  }

  return 0;
}

Result day16_part1(const char *input) {
  AocArray *sues = aoc_array_init(20, sizeof(Sue));
  fill_sues(input, sues);
  int result = find_sue(sues, false);

  aoc_array_free(sues);

  return result_int(result);
}

Result day16_part2(const char *input) {
  AocArray *sues = aoc_array_init(20, sizeof(Sue));
  fill_sues(input, sues);
  int result = find_sue(sues, true);

  aoc_array_free(sues);

  return result_int(result);
}
