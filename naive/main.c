#include "io.h"
#include "naive.h"
#include "random.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {


  // Handle arguments and files
  Args args;
  if (!parse_args(argc, argv, &args)) {
    fprintf(stderr,
            "Usage: %s [-i input] [-o output]\n",
            argv[0]);
  }

  FILE *in = open_input_or_stdin(args.input_path);
  FILE *out = open_output_or_stdout(args.output_path);

  if (!in || !out) {
    fprintf(stderr, "error opening files.\n");
  }

  // Take in data, process, and put into some form of dictionary
  // TODO
  int num_lines;
  fscanf(in, "%d", &num_lines);

  // Make one of these a dictionary structure
  double features[num_lines][/* dictionary of word counts */];
  int labels[num_lines];

  for (int i = 0; i < num_lines; i++)
    fscanf(in, "What form do we take in?", ??); 

  // Initialize Model; An array of structs with the word and the count of spam and hams?
  // TODO
  Word_Count model[] = ;

  // Train model
  // TODO
  train(&model)

  // Print results
  // TODO

  safe_close(in);
  safe_close(out);

  return 0;
}
