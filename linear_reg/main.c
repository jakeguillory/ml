#include "linear_reg.h"
#include "io.h"
#include "random.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define EPOCHS 1000
#define LEARNING_RATE 0.01


int main(int argc, char *argv[]) {

  // Seed generator for random functions
  random_init();

  // Handle arguments and files
  const char *input_path = NULL;
  const char *output_path = NULL;
  parse_args(argc, argv, &input_path, &output_path);

  FILE *in = open_input_or_stdin(input_path);
  FILE *out = open_output_or_stdout(output_path);


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
  train(&model, features, labels, num_lines, LEARNING_RATE, EPOCHS);

  // Uncomment below for printing input data
  // for (int i = 0; i < num_lines; i++)
  //   printf("Feature: %lf  Label: %lf\n", features[i], labels[i]);

  fprintf(out, "Model Bias: %f\nModel Weight: %f\n", model.bias, model.weight);

  safe_close(in);
  safe_close(out);

  return 0;
}
