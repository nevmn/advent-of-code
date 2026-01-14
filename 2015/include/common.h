#ifndef AOC_COMMON_H
#define AOC_COMMON_H

// @formatter:off

#include <stdbool.h>
#include <stddef.h>

typedef enum {
  RESULT_TYPE_INT,
  RESULT_TYPE_STRING
} ResultType;

typedef struct {
  ResultType type;

  union {
    int n;
    const char *s;
  } value;
} Result;

typedef struct {
  size_t size;
  size_t capacity;
  size_t item_size;
  void *data;
} AocArray;

// see alloc.c
void *_aoc_malloc(size_t size, const char *file, int line);
void *_aoc_realloc(void *ptr, size_t size, const char *file, int line);
void *_aoc_calloc(size_t num, size_t size, const char *file, int line);

#define aoc_malloc(size) _aoc_malloc(size, __FILE__, __LINE__)
#define aoc_realloc(pointer, size) \
  _aoc_realloc(pointer, size, __FILE__, __LINE__)
#define aoc_calloc(num, size) _aoc_calloc(num, size, __FILE__, __LINE__)

// see io.c
const char *read_file(const char *filename);
size_t get_next_line(const char *input, size_t position, char **buffer, size_t *buffer_size);

// see misc.c
int min2(int a, int b);
int min3(int a, int b, int c);
int compare(const void *a, const void *b);
Result result_int(int result);
Result result_str(const char *result);
void permute(int *indices, int start, int end, int **matrix, int *min, int *max, bool circular);

// see array.c
AocArray *aoc_array_init(size_t capacity, size_t item_size);
void aoc_array_append(AocArray *array, const void *item);
void *aoc_array_get(const AocArray *array, size_t index);
void aoc_array_reset(AocArray *array);
void aoc_array_free(AocArray *array);

#endif // !AOC_COMMON_H
