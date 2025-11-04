#include "log_reg.h"
#include "random.h"
#include <math.h> // exp() log()
#include <stddef.h>
#include <stdio.h>



double score(Model *model, double temp_feature_a, double temp_feature_b) {
  return model->weight_a * temp_feature_a + model->weight_b * temp_feature_b +
         model->bias;
}

double sigmoid(double score) { return ( 1.0 / (1.0 + exp(-score)) ); }

double prediction(Model *model, double temp_feature_a, double temp_feature_b) {
  return sigmoid(score(model, temp_feature_a, temp_feature_b));
}

double log_loss(Model *model, double temp_feature_a, double temp_feature_b,
             int temp_label) {
  double pred = prediction(model, temp_feature_a, temp_feature_b);
  return (-temp_label * log(pred)) - ((1 - temp_label) * log(1 - pred));
}

void logistic_trick(Model *model, double temp_feature_a,
                      double temp_feature_b, int temp_label,
                      double learning_rate) {
  double pred = prediction(model, temp_feature_a, temp_feature_b);
  model->bias += learning_rate * (temp_label - pred);
  model->weight_a += learning_rate * temp_feature_a * (temp_label - pred);
  model->weight_b += learning_rate * temp_feature_b * (temp_label - pred);
}

void train(Model *model, double *features_a, double *features_b, int *labels,
           int num_lines, double learning_rate, int epochs) {
  for (int i = 0; i < epochs; i++) {
    // pick random number that falls in feature & label size
    int random_int = generate_random_int(0, (num_lines - 1));
    // assign temporary feature and temporary label
    double temp_feature_a = features_a[random_int];
    double temp_feature_b = features_b[random_int];
    int temp_label = labels[random_int];
    // use logistic_trick function to move line closer to temporary point
    logistic_trick(model, temp_feature_a, temp_feature_b, temp_label,
                     learning_rate);
    // Uncomment below to print progress
    printf("int: %d, temp_feature_a: %lf, temp_feature_b: %lf, temp_label: %d, "
           "bias: %lf, weight_a: %lf, weight_b: %lf\n",
           random_int, temp_feature_a, temp_feature_b, temp_label, model->bias,
           model->weight_a, model->weight_b);
    // Uncomment below to watch progress
    //sleep(1);
  }
}
