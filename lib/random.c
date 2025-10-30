#include "../include/random.h"
#include <stdlib.h>
#include <time.h>

void random_init(void) {
  // Seed random number generator using current time
  // call once in program before calling generator functions
  srand((unsigned)time(NULL));
}

int generate_random_int(int min, int max) {

  if (max <= min)
    return min; // Should return some sort of error

  return min + rand() % (max - min + 1);
}

double generate_random_double(void) {
  return ((double)rand()) / ((double)RAND_MAX + 1.0);
}
