#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <stddef.h>

typedef struct Model {
  double bias;
  double weight_a;
  double weight_b;
} Model;

void perceptron_trick(Model *model, double feature_a, double feature_b,
                      int label, double learning_rate);

void train(Model *model, double *features_a, double *features_b, int *labels,
           int num_lines, double learning_rate, int epochs);

#endif // PERCEPTRON_H
