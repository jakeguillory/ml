#ifndef NAIVE_H
#define NAIVE_H

typedef struct {

  char *word;     // Maybe create a String Type?
  int spam_count; // How many times this word appears in a spam email
  int ham_count;  // How many times this word appears in a ham email

} Word_Count;

#endif // NAIVE_H
