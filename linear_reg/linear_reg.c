#include "linear_reg.h"

void square_trick(Model *model, double temp_feature, double temp_label,
                  double learning_rate) {

  double prediction = model->bias + (model->weight * temp_feature);
  model->bias += learning_rate * (temp_label - prediction);
  model->weight += learning_rate * temp_feature * (temp_label - prediction);
}
