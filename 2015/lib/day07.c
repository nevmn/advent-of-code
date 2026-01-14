#include <assert.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "common.h"
#include "day07.h"

typedef struct Wire {
  unsigned short value;
  bool resolved;
  char *name;
} Wire;

enum Gate {
  Null,
  And,
  Or,
  LShift,
  RShift,
  Not,
};

typedef struct Instruction {
  enum Gate gate;
  char *input1;
  char *input2;
  char *output;
} Instruction;

static const char *regex_pattern = "([a-z0-9]*) *([A-Z]*) *([a-z0-9]*) -> ([a-z0-9]+)";

static Wire *find_wire(const AocArray *wires, const char *name) {
  for (size_t i = 0; i < wires->size; i++) {
    Wire *wire = aoc_array_get(wires, i);
    if (wire->name != NULL && strcmp(wire->name, name) == 0) {
      return wire;
    }
  }

  return NULL;
}

static Wire *get_or_create_wire(AocArray *wires, const char *name) {
  Wire *wire = find_wire(wires, name);
  if (wire != NULL) return wire;

  Wire new_wire = {0};
  new_wire.name = aoc_malloc((strlen(name) + 1) * sizeof(char));
  strcpy(new_wire.name, name);
  new_wire.resolved = false;

  aoc_array_append(wires, &new_wire);

  return find_wire(wires, name);
}

static bool is_number(const char *str) {
  if (str == NULL || *str == '\0') return false;

  while (*str) {
    if (!isdigit(*str)) return false;
    str++;
  }

  return true;
}

static unsigned short evaluate_wire(AocArray *wires, AocArray *instructions, const char *wire_name);

static unsigned short get_input_value(AocArray *wires, AocArray *instructions, const char *input) {
  if (is_number(input)) {
    return (unsigned short) atoi(input);
  }

  return evaluate_wire(wires, instructions, input);
}

static Instruction *find_instruction_for_wire(const AocArray *instructions, const char *wire_name) {
  for (size_t i = 0; i < instructions->size; i++) {
    Instruction *instruction = aoc_array_get(instructions, i);
    if (strcmp(instruction->output, wire_name) == 0) {
      return instruction;
    }
  }
  return NULL;
}

static unsigned short evaluate_wire(AocArray *wires, AocArray *instructions, const char *wire_name) {
  if (is_number(wire_name)) {
    return (unsigned short) atoi(wire_name);
  }

  Wire *wire = find_wire(wires, wire_name);
  if (wire != NULL && wire->resolved) {
    return wire->value;
  }

  const Instruction *instruction = find_instruction_for_wire(instructions, wire_name);
  if (instruction == NULL) {
    return 0;
  }

  unsigned short result;

  const unsigned short first_input_value = get_input_value(wires, instructions, instruction->input1);
  const unsigned short second_input_value = get_input_value(wires, instructions, instruction->input2);
  switch (instruction->gate) {
    case Null:
      result = first_input_value;
      break;
    case And:
      result = first_input_value & second_input_value;
      break;
    case Or:
      result = first_input_value | second_input_value;
      break;
    case LShift:
      result = first_input_value << second_input_value;
      break;
    case RShift:
      result = first_input_value >> second_input_value;
      break;
    case Not:
      result = ~second_input_value;
      break;
    default:
      fprintf(stderr, "Unknown gate type for wire %s\n", wire_name);
      exit(EXIT_FAILURE);
  }

  wire = get_or_create_wire(wires, wire_name);
  wire->value = result;
  wire->resolved = true;

  return result;
}

static void fill_instructions(AocArray *instructions, const char *input) {
  regex_t regex;
  regmatch_t matches[5];
  if (regcomp(&regex, regex_pattern, REG_EXTENDED) != 0) {
    fprintf(stderr, "Failed to compile regex\n");
    exit(EXIT_FAILURE);
  }

  char *line = NULL;
  size_t line_size = 0;
  size_t pos = 0;
  while ((pos = get_next_line(input, pos, &line, &line_size)) > 0) {
    if (regexec(&regex, line, 5, matches, 0) == 0) {
      char command[matches[2].rm_eo - matches[2].rm_so + 1];
      strncpy(command, line + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
      command[matches[2].rm_eo - matches[2].rm_so] = '\0';

      char input1[matches[1].rm_eo - matches[1].rm_so + 1];
      strncpy(input1, line + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
      input1[matches[1].rm_eo - matches[1].rm_so] = '\0';

      char input2[matches[3].rm_eo - matches[3].rm_so + 1];
      strncpy(input2, line + matches[3].rm_so, matches[3].rm_eo - matches[3].rm_so);
      input2[matches[3].rm_eo - matches[3].rm_so] = '\0';

      char output[matches[4].rm_eo - matches[4].rm_so + 1];
      strncpy(output, line + matches[4].rm_so, matches[4].rm_eo - matches[4].rm_so);
      output[matches[4].rm_eo - matches[4].rm_so] = '\0';

      enum Gate gate = Null;
      if (strcmp(command, "AND") == 0) {
        gate = And;
      } else if (strcmp(command, "OR") == 0) {
        gate = Or;
      } else if (strcmp(command, "LSHIFT") == 0) {
        gate = LShift;
      } else if (strcmp(command, "RSHIFT") == 0) {
        gate = RShift;
      } else if (strcmp(command, "NOT") == 0) {
        gate = Not;
      }

      Instruction instruction;
      instruction.gate = gate;
      instruction.input1 = aoc_malloc((strlen(input1) + 1) * sizeof(char));
      instruction.input2 = aoc_malloc((strlen(input2) + 1) * sizeof(char));
      instruction.output = aoc_malloc((strlen(output) + 1) * sizeof(char));
      strcpy(instruction.input1, input1);
      strcpy(instruction.input2, input2);
      strcpy(instruction.output, output);

      aoc_array_append(instructions, &instruction);
    }
  }

  regfree(&regex);
  free(line);
}

static void free_wires_and_instructions(AocArray *wires, AocArray *instructions) {
  for (size_t i = 0; i < wires->size; i++) {
    const Wire *wire = aoc_array_get(wires, i);
    free(wire->name);
  }

  for (size_t i = 0; i < instructions->size; i++) {
    const Instruction *instruction = aoc_array_get(instructions, i);
    free(instruction->input1);
    free(instruction->input2);
    free(instruction->output);
  }

  aoc_array_free(wires);
  aoc_array_free(instructions);
}

Result day07_part1(const char *input) {
  AocArray *instructions = aoc_array_init(10, sizeof(Instruction));
  AocArray *wires = aoc_array_init(10, sizeof(Wire));

  fill_instructions(instructions, input);
  const unsigned short result = evaluate_wire(wires, instructions, "a");

  free_wires_and_instructions(wires, instructions);

  return result_int(result);
}

Result day07_part2(const char *input) {
  AocArray *instructions = aoc_array_init(10, sizeof(Instruction));
  AocArray *wires = aoc_array_init(10, sizeof(Wire));

  fill_instructions(instructions, input);
  unsigned short result = evaluate_wire(wires, instructions, "a");

  Wire *wire_b = find_wire(wires, "b");
  assert(wire_b != NULL);
  wire_b->value = result;
  for (int i = 0; i < wires->size; ++i) {
    Wire *wire = aoc_array_get(wires, i);
    wire->resolved = false;
  }
  wire_b->resolved = true;

  result = evaluate_wire(wires, instructions, "a");

  free_wires_and_instructions(wires, instructions);

  return result_int(result);
}
