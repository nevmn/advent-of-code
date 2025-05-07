#include <stdio.h>
#include <stdlib.h>

#include "common.h"

const char *read_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("ERROR: Cannot open file");
    exit(EXIT_FAILURE);
  }

  fseek(file, 0L, SEEK_END);
  long file_size = ftell(file);
  if (file_size == -1) {
    perror("ERROR: Cannot read file size");
    exit(EXIT_FAILURE);
  }
  rewind(file);

  char *buffer = aoc_malloc((file_size + 1) * sizeof(char));

  size_t read_size = fread(buffer, sizeof(char), file_size, file);
  if (read_size != (unsigned)file_size) {
    free(buffer);
    perror("ERROR: Error reading file");
    exit(EXIT_FAILURE);
  }

  buffer[file_size] = '\0';
  fclose(file);

  return buffer;
}