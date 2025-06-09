#include "common.h"

inline int min2(const int a, const int b) { return a > b ? b : a; }

inline int min3(const int a, const int b, const int c) {
  return min2(min2(a, b), c);
}

inline int compare(const void *a, const void *b) {
  const int int_a = *(int *)a;
  const int int_b = *(int *)b;

  if (int_a == int_b) {
    return 0;
  }
  if (int_a < int_b) {
    return -1;
  }

  return 1;
}
