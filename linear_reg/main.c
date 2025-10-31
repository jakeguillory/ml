#include "linear_reg.h"
#include "io.h"
#include "random.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {

  // Seed generator for random functions
  random_init();

  // Handle arguments and files

  Args args;
  if (!parse_args(argc, argv, &args)) {
      fprintf(stderr, "Usage: %s [-i input] [-o output] [-e epochs] [-l learning_rate]\n", argv[0]);
  }

  FILE *in = open_input_or_stdin(args.input_path);
  FILE *out = open_output_or_stdout(args.output_path);

  if (!in || !out) {
      fprintf(stderr, "error opening files.\n");
  }


  // Take in data and put into arrays
  int num_lines;
  fscanf(in, "%d", &num_lines);

  double features[num_lines];
  double labels[num_lines];

  for (int i = 0; i < num_lines; i++)
    fscanf(in, "%lf %lf", &features[i], &labels[i]);

  // Initialize Model
  Model model = {.bias = 1.0, .weight = 1.0};

  // Train model
  train(&model, features, labels, num_lines, args.learning_rate, args.epochs);

  // Print results
  fprintf(out, "Model Bias: %f\nModel Weight: %f\n", model.bias, model.weight);

  safe_close(in);
  safe_close(out);

  return 0;
}
