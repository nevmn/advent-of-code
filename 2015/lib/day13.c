#include "common.h"
#include "day13.h"

#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *name;
  char *nameTo;
  int relationship;
} Person;

typedef struct {
  char *name;
} Name;

static const char regex_pattern[] =
    "([a-zA-Z]*) would (gain|lose) ([0-9]*) happiness units by sitting next to ([a-zA-Z]*).";

static void fill_persons(AocArray *persons, const char *input) {
  regex_t regex;
  regmatch_t matches[5];
  if (regcomp(&regex, regex_pattern, REG_EXTENDED) != 0) {
    fprintf(stderr, "Failed to compile regex\n");
    exit(EXIT_FAILURE);
  }

  char *line = NULL;
  size_t line_size = 0;
  size_t pos = 0;
  while ((pos = get_next_line(input, pos, &line, &line_size)) > 0) {
    if (regexec(&regex, line, 5, matches, 0) == 0) {
      char name[matches[1].rm_eo - matches[1].rm_so + 1];
      strncpy(name, line + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
      name[matches[1].rm_eo - matches[1].rm_so] = '\0';

      char sign[matches[2].rm_eo - matches[2].rm_so + 1];
      strncpy(sign, line + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
      sign[matches[2].rm_eo - matches[2].rm_so] = '\0';

      char relationship[matches[3].rm_eo - matches[3].rm_so + 1];
      strncpy(relationship, line + matches[3].rm_so, matches[3].rm_eo - matches[3].rm_so);
      relationship[matches[3].rm_eo - matches[3].rm_so] = '\0';

      char nameTo[matches[4].rm_eo - matches[4].rm_so + 1];
      strncpy(nameTo, line + matches[4].rm_so, matches[4].rm_eo - matches[4].rm_so);
      nameTo[matches[4].rm_eo - matches[4].rm_so] = '\0';

      Person p;
      p.name = aoc_malloc((strlen(name) + 1)*sizeof(char));
      p.nameTo = aoc_malloc((strlen(nameTo) + 1)*sizeof(char));
      strcpy(p.name, name);
      strcpy(p.nameTo, nameTo);
      if (strcmp(sign, "gain") == 0) {
        p.relationship = atoi(relationship);
      } else {
        p.relationship = -atoi(relationship);
      }

      aoc_array_append(persons, &p);
    }
  }

  regfree(&regex);
  free(line);
}

static void insert_name(AocArray *names, const char *name) {
  for (int i = 0; i < names->size; ++i) {
    const Name *n = aoc_array_get(names, i);
    if (n != NULL && strcmp(n->name, name) == 0) {
      return;
    }
  }

  Name new_name;
  new_name.name = aoc_malloc((strlen(name) + 1)*sizeof(char));
  strcpy(new_name.name, name);
  aoc_array_append(names, &new_name);
}

static void fill_names(AocArray *names, const AocArray *persons) {
  for (int i = 0; i < persons->size; ++i) {
    const Person *p = aoc_array_get(persons, i);
    insert_name(names, p->name);
    insert_name(names, p->nameTo);
  }
}

static int find_relationship(const AocArray *persons, const char *name1, const char *name2) {
  for (int i = 0; i < persons->size; ++i) {
    const Person *p = aoc_array_get(persons, i);
    if (strcmp(p->name, name1) == 0 && strcmp(p->nameTo, name2) == 0) {
      return p->relationship;
    }
  }
  return 0;
}

static void fill_matrix(const AocArray *persons, const AocArray *names, int **matrix) {
  for (int i = 0; i < names->size; ++i) {
    for (int j = 0; j < names->size; ++j) {
      if (i == j) {
        matrix[i][j] = 0;
        continue;
      }

      const Name *name1 = aoc_array_get(names, i);
      const Name *name2 = aoc_array_get(names, j);

      int happiness1 = find_relationship(persons, name1->name, name2->name);
      int happiness2 = find_relationship(persons, name2->name, name1->name);

      matrix[i][j] = happiness1 + happiness2;
    }
  }
}

static int find_optimal_arrangement(const AocArray *names, int **matrix, const bool without_me) {
  int *indices = aoc_malloc(names->size * sizeof(int));
  for (int i = 0; i < names->size; ++i) {
    indices[i] = i;
  }

  int min_happiness = INT_MIN;
  int max_happiness = INT_MIN;

  permute(indices, 0, (int) names->size - 1, matrix, &min_happiness, &max_happiness, without_me);

  free(indices);
  return max_happiness;
}

static void free_names(AocArray *names) {
  for (size_t i = 0; i < names->size; ++i) {
    Name *n = aoc_array_get(names, i);
    free(n->name);
  }
  aoc_array_free(names);
}

static void free_persons(AocArray *persons) {
  for (size_t i = 0; i < persons->size; ++i) {
    const Person *p = aoc_array_get(persons, i);
    free(p->name);
    free(p->nameTo);
  }
  aoc_array_free(persons);
}

static Result solve_day13(const char *input, const bool without_me) {
  AocArray *persons = aoc_array_init(20, sizeof(Person));
  fill_persons(persons, input);

  AocArray *names = aoc_array_init(20, sizeof(Name));
  fill_names(names, persons);

  int **matrix = aoc_malloc(names->size * sizeof(int*));
  for (int i = 0; i < names->size; ++i) {
    matrix[i] = aoc_malloc(names->size * sizeof(int));
  }
  fill_matrix(persons, names, matrix);

  const int max_happiness = find_optimal_arrangement(names, matrix, without_me);

  for (int i = 0; i < names->size; ++i) {
    free(matrix[i]);
  }
  free(matrix);
  free_names(names);
  free_persons(persons);

  return result_int(max_happiness);
}

Result day13_part1(const char *input) {
  return solve_day13(input, true);
}

Result day13_part2(const char *input) {
  return solve_day13(input, false);
}