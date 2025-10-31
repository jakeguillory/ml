#ifndef LINEAR_REG_H
#define LINEAR_REG_H

#include <stddef.h>

typedef struct Model {
  double bias;
  double weight;
} Model;

void square_trick(Model *model, double feature, double label,
                  double learning_rate);

void train(Model *model, double *features, double *labels, int num_lines,
           double learning_rate, int epochs);

#endif // LINEAR_REG_H
