#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool read_doubles(FILE *fp, double *buf, int n) {

  for (int i = 0; i < n; i++) {
    if (fscanf(fp, "%lf", &buf[i]) != 1)
      return false;
  }
  return true;
}

bool parse_args(int argc, char **argv, Args *args) {
  // Defaults
  args->input_path = NULL;
  args->output_path = NULL;
  args->epochs = 1000;
  args->learning_rate = 0.01;
  args->string = NULL;

  for (int i = 1; i < argc; i++) {
    if ((strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) &&
        i + 1 < argc) {
      args->input_path = argv[++i];
    } else if ((strcmp(argv[i], "-o") == 0 ||
                strcmp(argv[i], "--output") == 0) &&
               i + 1 < argc) {
      args->output_path = argv[++i];
    } else if ((strcmp(argv[i], "-e") == 0 ||
                strcmp(argv[i], "--epochs") == 0) &&
               i + 1 < argc) {
      args->epochs = atoi(argv[++i]);
    } else if ((strcmp(argv[i], "-s") == 0 ||
                strcmp(argv[i], "--string") == 0) &&
               i + 1 < argc) {
      args->string = argv[++i];
    } else if ((strcmp(argv[i], "-l") == 0 ||
                strcmp(argv[i], "--learning_rate") == 0) &&
               i + 1 < argc) {
      args->learning_rate = atof(argv[++i]);
    } else {
      fprintf(stderr, "Unknown option: %s\n", argv[i]);
      return false;
    }
  }

  return true;
}

FILE *open_input_or_stdin(const char *path) {
  return path ? fopen(path, "r") : stdin;
}

FILE *open_output_or_stdout(const char *path) {
  return path ? fopen(path, "w") : stdout;
}

void safe_close(FILE *fp) {
  if (fp && (fp != stdin) && (fp != stdout))
    fclose(fp);
}
