#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *read_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("ERROR: Cannot open file");
    exit(EXIT_FAILURE);
  }

  fseek(file, 0L, SEEK_END);
  const long file_size = ftell(file);
  if (file_size == -1) {
    perror("ERROR: Cannot read file size");
    exit(EXIT_FAILURE);
  }
  rewind(file);

  char *buffer = aoc_malloc((file_size + 1) * sizeof(char));

  const size_t read_size = fread(buffer, sizeof(char), file_size, file);
  if (read_size != (unsigned) file_size) {
    free(buffer);
    perror("ERROR: Error reading file");
    exit(EXIT_FAILURE);
  }

  buffer[file_size] = '\0';
  fclose(file);

  return buffer;
}

size_t get_next_line(const char *input, size_t position, char **buffer, size_t *buffer_size) {
  if (input == NULL || input[position] == '\0' || buffer == NULL || buffer_size == NULL) {
    return 0;
  }

  size_t len = 0;
  size_t curr_pos = position;
  while (input[curr_pos] != '\0' && input[curr_pos] != '\n') {
    len++;
    curr_pos++;
  }

  if (*buffer_size <= len) {
    char *new_buffer = aoc_realloc(*buffer, len + 1);
    *buffer = new_buffer;
    *buffer_size = len + 1;
  }

  size_t i = 0;
  while (input[position] != '\0' && input[position] != '\n') {
    (*buffer)[i++] = input[position++];
  }
  (*buffer)[i] = '\0';

  if (input[position] == '\n') {
    position++;
  }

  return position;
}
