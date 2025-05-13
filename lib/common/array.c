#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

AocArray *aoc_array_init(const size_t capacity, const size_t item_size) {
  AocArray *array = aoc_malloc(sizeof(AocArray));

  array->size = 0;
  array->capacity = capacity;
  array->item_size = item_size;;
  array->data = aoc_malloc(capacity * sizeof(void *));

  return array;
}

void aoc_array_append(AocArray *array, const void *item) {
  if (array->size == array->capacity) {
    array->capacity *= 2;
    array->data = aoc_realloc(array->data, array->capacity * sizeof(void *));
  }

  array->data[array->size] = aoc_malloc(array->item_size);
  memcpy(array->data[array->size], item, array->item_size);
  array->size++;
}

void *aoc_array_get(const AocArray *array, const size_t index) {
  assert(index < array->size);

  return array->data[index];
}

void aoc_array_free(AocArray *array) {
  for (size_t i = 0; i < array->size; i++) {
    free(array->data[i]);
  }
  free(array->data);
  free(array);
}
