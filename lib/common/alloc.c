#include <stdio.h>
#include <stdlib.h>

#include "common.h"

void *_aoc_malloc(const size_t size, const char *file, const int line) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    fprintf(stderr, "ERROR: Failed to allocate %zu bytes at %s:%d\n", size,
            file, line);
    exit(EXIT_FAILURE);
  }

  return ptr;
}

void *_aoc_realloc(void *ptr, const size_t size, const char *file, const int line) {
  void *new_ptr = realloc(ptr, size);
  if (new_ptr == NULL && size != 0) {
    fprintf(stderr, "ERROR: Failed to realloc to %zu bytes at %s:%d\n", size,
            file, line);
    exit(EXIT_FAILURE);
  }

  return new_ptr;
}

void *_aoc_calloc(size_t num, size_t size, const char *file, const int line) {
  void *ptr = calloc(num, size);
  if (ptr == NULL) {
    fprintf(stderr, "ERROR: Failed to allocate %zu bytes at %s:%d\n", size,
            file, line);
    exit(EXIT_FAILURE);
  }

  return ptr;
}
