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

  for (int i = 0; i < EPOCHS; i++) {

    // pick random number that falls in feature & label size
    int random_int = generate_random_int(0, (num_lines - 1));
    // assign temporary feature and temporary label
    double temp_feature = features[random_int];
    double temp_label = labels[random_int];
    // use square_trick function to move line closer to temporary point
    square_trick(&model, temp_feature, temp_label, LEARNING_RATE);
    printf(
        "int: %d, temp_feture: %lf, temp_label: %lf, bias: %lf, weight: %lf\n",
        random_int, temp_feature, temp_label, model.bias, model.weight);
    // Uncomment below to watch progress
    // sleep(1);
  }

  // Uncomment below for printing input data
  for (int i = 0; i < num_lines; i++)
    printf("Feature: %lf  Label: %lf\n", features[i], labels[i]);

  printf("Model Bias: %f\nModel Weight: %f\n", model.bias, model.weight);

  return 0;
}
