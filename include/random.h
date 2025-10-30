#ifndef RANDOM_H
#define RANDOM_H

// Initializes the random number generator with a seed
// Include this once before generating random numbers
void random_init(void);

// Generates a random integer from min to max
int generate_random_int(int min, int max);

// Generates a random double from 0 1
double generate_random_double(void);

#endif // RANDOM_H
