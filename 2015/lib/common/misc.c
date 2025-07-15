#include "common.h"

#include <stdbool.h>
#include <stddef.h>

inline int min2(const int a, const int b) { return a > b ? b : a; }

inline int min3(const int a, const int b, const int c) {
  return min2(min2(a, b), c);
}

inline int compare(const void *a, const void *b) {
  const int int_a = *(int *) a;
  const int int_b = *(int *) b;

  if (int_a == int_b) {
    return 0;
  }
  if (int_a < int_b) {
    return -1;
  }

  return 1;
}

Result result_int(int result) {
  Result r;
  r.n = result;
  r.s = NULL;
  return r;
}

Result result_str(const char *result) {
  Result r;
  r.s = result;
  r.n = 0;
  return r;
}

void swap(int *a, int *b) {
  const int tmp = *a;
  *a = *b;
  *b = tmp;
}

void permute(int *indices, const int start, const int end, int **matrix, int *min, int *max, const bool circular) { // NOLINT(*-no-recursion)
  if (start == end) {
    int total = 0;

    if (circular) {
      for (int i = 0; i <= end; ++i) {
        int next = (i + 1) % (end + 1);
        total += matrix[indices[i]][indices[next]];
      }
    } else {
      for (int i = 0; i < end; ++i) {
        total += matrix[indices[i]][indices[i + 1]];
      }
    }

    if (total < *min) {
      *min = total;
    }

    if (total > *max) {
      *max = total;
    }

    return;
  }

  for (int i = start; i <= end; ++i) {
    swap(&indices[start], &indices[i]);
    permute(indices, start + 1, end, matrix, min, max, circular);
    swap(&indices[start], &indices[i]);
  }
}
