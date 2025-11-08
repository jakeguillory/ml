#include <ctype.h>

void to_lowercase(char *str) {
  for (int i = 0; str[i]; i++)
    str[i] = tolower((unsigned char)str[i]);
}
