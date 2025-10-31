#include "io.h"
#include <stdlib.h>
#include <string.h>

bool read_doubles(FILE *fp, double *buf, int n) {

  for (int i = 0; i < n; i++) {
    if (fscanf(fp, "%lf", &buf[i]) != 1)
      return false;
  }
  return true;
}

bool parse_args(int argc, char **argv, const char **input_path,
                const char **output_path) {
  *input_path = NULL;
  *output_path = NULL;

  for (int i = 1; i < argc; i++) {
    if ((strcmp(argv[i], "-i") == 0) && ((i + 1) < argc)) {
      *input_path = argv[++i];
    } else if ((strcmp(argv[i], "-o") == 0) && ((i + 1) < argc)) {
      *output_path = argv[++i];
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
