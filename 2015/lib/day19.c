#include "common.h"
#include "day19.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *from;
  char *to;
} Replacement;

static void fill_replacements(AocArray *replacements, char *molecule, const char *input, bool reverse) {
  char *line = NULL;
  size_t line_size = 0;
  size_t pos = 0;

  char from[100];
  char to[100];
  while ((pos = get_next_line(input, pos, &line, &line_size)) > 0) {
    if (strlen(line) == 0) {
      get_next_line(input, pos, &line, &line_size);
      strcpy(molecule, line);
      molecule[strlen(line)] = '\0';
      break;
    }
    Replacement replacement = {0};
    const int parsed_count = sscanf(line, "%2s => %10s", from, to);
    assert(parsed_count == 2);
    replacement.to = aoc_malloc((strlen(to) + 1)*sizeof(char));
    replacement.from = aoc_malloc((strlen(from) + 1)*sizeof(char));
    strcpy(replacement.to, to);
    strcpy(replacement.from, from);
    replacement.to[strlen(to)] = '\0';
    replacement.from[strlen(from)] = '\0';
    if (reverse) {
      char *tmp = replacement.from;
      replacement.from = replacement.to;
      replacement.to = tmp;
    }
    aoc_array_append(replacements, &replacement);
  }

  free(line);
}

static void free_replacements(AocArray *replacements) {
  for (int i = 0; i < replacements->size; i++) {
    Replacement *replacement = aoc_array_get(replacements, i);
    free(replacement->from);
    free(replacement->to);
  }
  aoc_array_free(replacements);
}

static void apply_replacement(const Replacement *replacement, AocArray *new_molecules, const char *molecule) {
  const char *pos = molecule;
  const size_t from_len = strlen(replacement->from);
  const size_t to_len = strlen(replacement->to);
  const size_t mol_len = strlen(molecule);

  while ((pos = strstr(pos, replacement->from)) != NULL) {
    char *new_molecule = aoc_malloc((mol_len - from_len + to_len + 1) * sizeof(char));
    const int index = (int)(pos - molecule);
    sprintf(new_molecule, "%.*s%s%s", index, molecule, replacement->to, pos + from_len);
    aoc_array_append(new_molecules, &new_molecule);

    pos++;
  }
}

static void shuffle_replacements(const AocArray *replacements) {
  for (int i = 0; i < replacements->size; i++) {
    int j = (int) (rand() % replacements->size);
    Replacement *a = aoc_array_get(replacements, i);
    Replacement *b = aoc_array_get(replacements, j);
    const Replacement tmp = *a;
    *a = *b;
    *b = tmp;
  }
}

static int compare_strings(const void *a, const void *b) {
  const char **str_a = (const char **) a;
  const char **str_b = (const char **) b;
  return strcmp(*str_a, *str_b);
}

Result day19_part1(const char *input) {
  char molecule[1000];
  AocArray *replacements = aoc_array_init(10, sizeof(Replacement));
  fill_replacements(replacements, molecule, input, false);

  AocArray *new_molecules = aoc_array_init(10, sizeof(char *));

  for (int i = 0; i < replacements->size; i++) {
    const Replacement *replacement = aoc_array_get(replacements, i);
    apply_replacement(replacement, new_molecules, molecule);
  }

  qsort(new_molecules->data, new_molecules->size, sizeof(char *), compare_strings);

  int count = 0;
  if (new_molecules->size > 0) {
    count = 1;
    for (size_t i = 1; i < new_molecules->size; i++) {
      char **prev = aoc_array_get(new_molecules, i - 1);
      char **curr = aoc_array_get(new_molecules, i);
      if (strcmp(*prev, *curr) != 0) {
        count++;
      }
    }
  }

  for (size_t i = 0; i < new_molecules->size; i++) {
    char **s = aoc_array_get(new_molecules, i);
    free(*s);
  }
  aoc_array_free(new_molecules);
  free_replacements(replacements);

  return result_int(count);
}

Result day19_part2(const char *input) {
  char molecule[1000];
  AocArray *replacements = aoc_array_init(10, sizeof(Replacement));
  fill_replacements(replacements, molecule, input, true);

  char *current_molecule = aoc_malloc(strlen(molecule) + 1);
  strcpy(current_molecule, molecule);

  int steps = 0;
  srand(321);

  while (strcmp(current_molecule, "e") != 0) {
    bool changed = false;
    for (int i = 0; i < replacements->size; i++) {
      const Replacement *rep = aoc_array_get(replacements, i);
      const char *pos = strstr(current_molecule, rep->from);
      if (pos) {
        const size_t idx = pos - current_molecule;
        const size_t len_from = strlen(rep->from);
        const size_t len_to = strlen(rep->to);
        const size_t current_len = strlen(current_molecule);

        memmove(current_molecule + idx + len_to, current_molecule + idx + len_from, current_len - (idx + len_from) + 1);
        memcpy(current_molecule + idx, rep->to, len_to);

        steps++;
        changed = true;
        break;
      }
    }

    if (!changed) {
      free(current_molecule);
      current_molecule = aoc_malloc(strlen(molecule) + 1);
      strcpy(current_molecule, molecule);
      steps = 0;
      shuffle_replacements(replacements);
    }
  }

  free(current_molecule);
  free_replacements(replacements);

  return result_int(steps);
}