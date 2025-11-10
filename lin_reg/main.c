#include "io.h"
#include "lin_reg.h"
#include "random.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  // Seed generator for random functions
  random_init();

  Args args;

  if (!parse_args(argc, argv, &args)) {
    fprintf(stderr,
            "Usage: %s [-i input] [-o output] [-e epochs] [-l learning_rate]\n",
            argv[0]);
    return EXIT_FAILURE;
  }

  FILE *in = open_input_or_stdin(args.input_path);
  FILE *out = open_output_or_stdout(args.output_path);

  if (!in || !out) {
    fprintf(stderr, "Error: Could not open input or output.\n");
    return EXIT_FAILURE;
  }

  // Handle input data
  int num_lines;
  if (fscanf(in, "%d", &num_lines) !=1) {
      fprintf(stderr, "Error: Failed to read number of input lines. \n");
      safe_close(in);
      safe_close(out);
      return EXIT_FAILURE;
  }

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
