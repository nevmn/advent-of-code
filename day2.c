#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day2.h"

int **boxes;

int fill_boxes(char *input) {
  int i = 0;
  char *input2 = input;
  do {
    i++;
    input2 = strchr(input2, '\n') + 1;
  } while (*input2 != '\0');

  boxes = (int **)malloc(i * sizeof(int *));
  for (int j = 0; j < i; j++) {
    boxes[j] = (int *)malloc(3 * sizeof(int));
  }

  int l, w, h;
  i = 0;
  input2 = input;
  do {
    sscanf(input2, "%dx%dx%d", &l, &w, &h);
    boxes[i][0] = l;
    boxes[i][1] = w;
    boxes[i][2] = h;
    i++;
    input2 = strchr(input2, '\n') + 1;
  } while (*input2 != '\0');

  return i;
}

void free_boxes(int len) {
  for (int i = 0; i < len; i++) {
    free(boxes[i]);
  }
  free(boxes);
}

int day2_part1(char *input) {
  int len = fill_boxes(input);
  int result = 0;
  for (int i = 0; i < len; i++) {
    int a = boxes[i][0];
    int b = boxes[i][1];
    int c = boxes[i][2];
    int l = a * b;
    int w = a * c;
    int h = b * c;
    result += 2 * (l + w + h) + min3(l, w, h);
  }

  free_boxes(len);
  return result;
}

int day2_part2(char *input) {
  int len = fill_boxes(input);
  int result = 0;
  for (int i = 0; i < len; i++) {
    qsort(boxes[i], 3, sizeof(int), compare);
    int a = boxes[i][0];
    int b = boxes[i][1];
    int c = boxes[i][2];
    result += 2 * (a + b) + a * b * c;
  }

  free_boxes(len);
  return result;
}
