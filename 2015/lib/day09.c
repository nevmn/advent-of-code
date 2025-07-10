#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#include "common.h"
#include "day09.h"

typedef struct {
  char *city1;
  char *city2;
  int length;
} Node;

typedef struct {
  char *name;
} City;

static const char *regex_pattern = "([a-zA-Z]*) to ([a-zA-Z]*) = ([0-9]*)";

static int find_length(const AocArray *graph, const char *city1, const char *city2) {
  for (int i = 0; i < graph->size; ++i) {
    const Node *c = aoc_array_get(graph, i);
    if (c != NULL
        && ((strcmp(city1, c->city1) == 0 && strcmp(city2, c->city2) == 0)
            || (strcmp(city1, c->city2) == 0 && strcmp(city2, c->city1) == 0))
    ) {
      return c->length;
    }
  }

  return 0;
}

static size_t get_city_index(AocArray *cities, const char *city) {
  for (size_t i = 0; i < cities->size; ++i) {
    const City *elem = aoc_array_get(cities, i);
    if (elem != NULL && strcmp(elem->name, city) == 0) {
      return i;
    }
  }

  City new_city;
  new_city.name = aoc_malloc((strlen(city) + 1)*sizeof(char));
  strcpy(new_city.name, city);
  aoc_array_append(cities, &new_city);

  return cities->size - 1;
}

static void fill_graph(AocArray *graph, const char *input) {
  regex_t regex;
  regmatch_t matches[4];
  if (regcomp(&regex, regex_pattern, REG_EXTENDED) != 0) {
    fprintf(stderr, "Failed to compile regex\n");
    exit(EXIT_FAILURE);
  }

  char *line = NULL;
  size_t line_size = 0;
  size_t pos = 0;
  while ((pos = get_next_line(input, pos, &line, &line_size)) > 0) {
    if (regexec(&regex, line, 4, matches, 0) == 0) {
      char city1[matches[1].rm_eo - matches[1].rm_so + 1];
      strncpy(city1, line + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
      city1[matches[1].rm_eo - matches[1].rm_so] = '\0';

      char city2[matches[2].rm_eo - matches[2].rm_so + 1];
      strncpy(city2, line + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
      city2[matches[2].rm_eo - matches[2].rm_so] = '\0';

      char length[matches[3].rm_eo - matches[3].rm_so + 1];
      strncpy(length, line + matches[3].rm_so, matches[3].rm_eo - matches[3].rm_so);
      length[matches[3].rm_eo - matches[3].rm_so] = '\0';

      Node c;
      c.length = atoi(length);
      c.city1 = aoc_malloc((strlen(city1) + 1)*sizeof(char));
      c.city2 = aoc_malloc((strlen(city2) + 1)*sizeof(char));
      strcpy(c.city1, city1);
      strcpy(c.city2, city2);

      aoc_array_append(graph, &c);
    }
  }

  regfree(&regex);
  free(line);
}

static void free_graph(AocArray *graph) {
  for (size_t i = 0; i < graph->size; ++i) {
    const Node *c = aoc_array_get(graph, i);
    free(c->city1);
    free(c->city2);
  }
  aoc_array_free(graph);
}

static void fill_cities(const AocArray *graph, AocArray *cities) {
  for (int i = 0; i < graph->size; ++i) {
    const Node *c = aoc_array_get(graph, i);
    get_city_index(cities, c->city1);
    get_city_index(cities, c->city2);
  }
}

static void fill_matrix(const AocArray *graph, const AocArray *cities, int **matrix) {
  for (int i = 0; i < cities->size; ++i) {
    for (int j = 0; j < cities->size; ++j) {
      if (i == j) {
        matrix[i][j] = 0;
        continue;
      }

      const City *city1 = aoc_array_get(cities, i);
      const City *city2 = aoc_array_get(cities, j);
      const int length = find_length(graph, city1->name, city2->name);
      matrix[i][j] = length;
    }
  }
}


int day09_part1(const char *input) {
  AocArray *graph = aoc_array_init(5, sizeof(Node));
  fill_graph(graph, input);

  AocArray *cities = aoc_array_init(10, sizeof(City));
  fill_cities(graph, cities);

  int **matrix = aoc_malloc(cities->size * sizeof(int*));
  for (int i = 0; i < cities->size; ++i) {
    matrix[i] = aoc_malloc(cities->size * sizeof(int));
  }
  fill_matrix(graph, cities, matrix);

  bool *visited = aoc_calloc(cities->size, sizeof(bool));
  int min_path = INT_MAX;

  for (size_t start = 0; start < cities->size; start++) {
    memset(visited, 0, cities->size * sizeof(bool));
    visited[start] = true;
    int current_path = 0;
    int count = 1;
    int pos = (int) start;

    while (count < cities->size) {
      int next = -1;
      int min_dist = INT_MAX;

      for (size_t i = 0; i < cities->size; i++) {
        if (!visited[i] && matrix[pos][i] > 0 && matrix[pos][i] < min_dist) {
          min_dist = matrix[pos][i];
          next = (int) i;
        }
      }

      visited[next] = true;
      current_path += min_dist;
      pos = next;
      count++;
    }

    if (current_path < min_path) {
      min_path = current_path;
    }
  }

  free(visited);

  for (int i = 0; i < cities->size; ++i) {
    free(matrix[i]);
  }
  free(matrix);
  aoc_array_free(cities);
  free_graph(graph);

  return min_path;
}

int day09_part2(const char *input) {
  return 0;
}
