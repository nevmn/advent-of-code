#include "day2.h"
#include "common.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fill_boxes(const char *input, int **boxes) {
  int count = 0;
  const char *ptr = input;
  while (ptr && *ptr) {
    count++;
    ptr = strchr(ptr, '\n');
    if (!ptr) break;
    ptr++;
  }

  if (count == 0) return 0;

  *boxes = aoc_malloc(count * 3 * sizeof(int));

  int i = 0;
  ptr = input;
  while (ptr && *ptr) {
    sscanf(ptr, "%dx%dx%d", &(*boxes)[i * 3], &(*boxes)[i * 3 + 1], &(*boxes)[i * 3 + 2]);

    i++;
    ptr = strchr(ptr, '\n');
    if (!ptr) break;
    ptr++;
  }

  return i;
}

int day2_part1(const char *input) {
  assert(input != NULL);

  int *boxes;
  const int len = fill_boxes(input, &boxes);
  int result = 0;
  for (int i = 0; i < len * 3; i += 3) {
    const int a = (&boxes[i])[0];
    const int b = (&boxes[i])[1];
    const int c = (&boxes[i])[2];
    const int l = a * b;
    const int w = a * c;
    const int h = b * c;
    result += 2 * (l + w + h) + min3(l, w, h);
  }

  free(boxes);
  return result;
}

int day2_part2(const char *input) {
  assert(input != NULL);

  int *boxes;
  const int len = fill_boxes(input, &boxes);
  int result = 0;
  for (int i = 0; i < len * 3; i += 3) {
    qsort(&boxes[i], 3, sizeof(int), compare);
    const int a = (&boxes[i])[0];
    const int b = (&boxes[i])[1];
    const int c = (&boxes[i])[2];
    result += 2 * (a + b) + a * b * c;
  }

  free(boxes);
  return result;
}
