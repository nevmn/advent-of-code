#ifndef AOC_DAY2_H
#define AOC_DAY2_H

int day2_part1(char *input);
int day2_part2(char *input);

static inline int min2(int a, int b) { return a > b ? b : a; }

static inline int min3(int a, int b, int c) { return min2(min2(a, b), c); }

static inline int compare(const void *a, const void *b) {
  int int_a = *((int *)a);
  int int_b = *((int *)b);

  if (int_a == int_b) {
    return 0;
  } else if (int_a < int_b) {
    return -1;
  } else {
    return 1;
  }
}

#endif // !AOC_DAY2_H
