#ifndef LINEAR_REG_H
#define LINEAR_REG_H

typedef struct Model {
  double bias;
  double weight;
} Model;

void square_trick(Model *model, double feature, double label,
                  double learning_rate);

#endif // LINEAR_REG_H
