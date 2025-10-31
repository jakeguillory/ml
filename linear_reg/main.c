#include "linear_reg.h"
#include "random.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define EPOCHS 1000
#define LEARNING_RATE 0.01

int main(int argc, char *argv[]) {

  // Seed generator for random functions
  random_init();

  // Initialize Model
  Model model = {.bias = 1.0, .weight = 1.0};

  // Take in data from standard input and put into arrays
  int num_lines;
  scanf("%d", &num_lines);
  double features[num_lines];
  double labels[num_lines];

  for (int i = 0; i < num_lines; i++)
    scanf("%lf %lf", &features[i], &labels[i]);

  train(&model, features, labels, num_lines, LEARNING_RATE, EPOCHS);

  // Uncomment below for printing input data
  // for (int i = 0; i < num_lines; i++)
  //   printf("Feature: %lf  Label: %lf\n", features[i], labels[i]);

  printf("Model Bias: %f\nModel Weight: %f\n", model.bias, model.weight);

  return 0;
}
