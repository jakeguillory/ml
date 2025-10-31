#ifndef IO_H
#define IO_H

#include <stdbool.h>
#include <stdio.h>

typedef struct {
  const char *input_path;
  const char *output_path;
  int epochs;
  double learning_rate;
} Args;

bool read_doubles(FILE *fp, double *buf, int n);
bool parse_args(int argc, char **argv, Args *args);

FILE *open_input_or_stdin(const char *path);
FILE *open_output_or_stdout(const char *path);
void safe_close(FILE *fp);

#endif // IO_H
