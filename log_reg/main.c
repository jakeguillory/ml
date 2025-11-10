#include "io.h"
#include "log_reg.h"
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

  double features_a[num_lines];
  double features_b[num_lines];
  int labels[num_lines];

  for (int i = 0; i < num_lines; i++)
    fscanf(in, "%lf %lf %d", &features_a[i], &features_b[i], &labels[i]);

  // Initialize Model
  Model model = {.bias = 1.0, .weight_a = 1.0, .weight_b = 1.0};

  // Train model
  train(&model, features_a, features_b, labels, num_lines, args.learning_rate,
        args.epochs);

  // Print results
  fprintf(out, "Model Bias: %f\nModel Weight_A: %f\nModel Weight_B: %f\n",
          model.bias, model.weight_a, model.weight_b);

  safe_close(in);
  safe_close(out);

  return 0;
}
