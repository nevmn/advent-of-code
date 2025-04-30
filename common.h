#ifndef AOC_COMMON_H
#define AOC_COMMON_H

#include <stdio.h>
#include <stdlib.h>

static void *_aoc_malloc(size_t size, const char *file, int line) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    fprintf(stderr, "ERROR: Failed to allocate %zu bytes at %s:%d\n", size,
            file, line);
    exit(EXIT_FAILURE);
  }

  return ptr;
}

static void *_aoc_realloc(void *ptr, size_t size, const char *file, int line) {
  void *new_ptr = realloc(ptr, size);
  if (new_ptr == NULL && size != 0) {
    fprintf(stderr, "ERROR: Failed to realloc to %zu bytes at %s:%d\n", size,
            file, line);
    exit(EXIT_FAILURE);
  }

  return new_ptr;
}

#define aoc_malloc(size) _aoc_malloc(size, __FILE__, __LINE__);
#define aoc_realloc(pointer, size)                                             \
  _aoc_realloc(pointer, size, __FILE__, __LINE__);

static inline int min2(int a, int b) { return a > b ? b : a; }

static inline int min3(int a, int b, int c) { return min2(min2(a, b), c); }

static inline int compare(const void *a, const void *b) {
  int int_a = *(int *)a;
  int int_b = *(int *)b;

  if (int_a == int_b) {
    return 0;
  }
  if (int_a < int_b) {
    return -1;
  }

  return 1;
}

#endif // !AOC_COMMON_H
