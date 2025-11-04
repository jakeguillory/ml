#include "lin_reg.h"
#include "random.h"
#include <stddef.h>
#include <stdio.h>

void square_trick(Model *model, double temp_feature, double temp_label,
                  double learning_rate) {

  double prediction = model->bias + (model->weight * temp_feature);
  model->bias += learning_rate * (temp_label - prediction);
  model->weight += learning_rate * temp_feature * (temp_label - prediction);
}

void train(Model *model, double *features, double *labels, int num_lines,
           double learning_rate, int epochs) {
  for (int i = 0; i < epochs; i++) {
    // pick random number that falls in feature & label size
    int random_int = generate_random_int(0, (num_lines - 1));
    // assign temporary feature and temporary label
    double temp_feature = features[random_int];
    double temp_label = labels[random_int];
    // use square_trick function to move line closer to temporary point
    square_trick(model, temp_feature, temp_label, learning_rate);
    // Uncommet below to print progress
    printf(
        "int: %d, temp_feature: %lf, temp_label: %lf, bias: %lf, weight: %lf\n",
        random_int, temp_feature, temp_label, model->bias, model->weight);
    // Uncomment below to watch progress
    // sleep(1);
  }
}
