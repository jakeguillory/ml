#include "io.h"
#include "naive.h"
#include "random.h"
#include "strings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define MAX_WORD_LENGTH          50
#define MAX_TEST_STRING_LENGTH   4096
#define MAX_TEST_STRING_WORDS    100

int main(int argc, char *argv[]) {
  
  Args args;

  if (!parse_args(argc, argv, &args)) {
    fprintf(stderr, "Usage: %s [-i input] [-o output] [-s string] \n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE *in = open_input_or_stdin(args.input_path);
  FILE *out = open_output_or_stdout(args.output_path);

  if (!in || !out) {
    fprintf(stderr, "Error: Could not open input or output.\n");
    return EXIT_FAILURE;
  }

  int vocab_size;
  if (fscanf(in, "%d", &vocab_size) !=1) {
      fprintf(stderr, "Error: Failed to read vocabulary size. \n");
      safe_close(in);
      safe_close(out);
      return EXIT_FAILURE;
  }

  char dictionary[vocab_size][MAX_WORD_LENGTH];
  int spam_count[vocab_size];
  int ham_count[vocab_size];

  for (int i = 0; i < vocab_size; i++)
    fscanf(in, "%49s %d %d", dictionary[i], &spam_count[i],
           &ham_count[i]);



  // Tokenize input string
  char *token;
  const char *delimiters = " .,:!?\n";
  char test_words[MAX_TEST_STRING_WORDS][MAX_WORD_LENGTH];
  int word_count = 0;

  token = strtok(args.string, delimiters);
  while (token && word_count < MAX_TEST_STRING_WORDS) {
    to_lowercase(token);
    strncpy(test_words[word_count], token, MAX_WORD_LENGTH - 1);
    test_words[word_count][MAX_WORD_LENGTH - 1] = '\0';
    word_count++;
    token = strtok(NULL, delimiters);
  }



  // Model Numbers and Parameters
  double total_spam = 1367.0;
  double total_ham =  4359.0;
  double prior_spam = total_spam / (total_spam + total_ham);    
  double prior_ham =  1 - prior_spam;
  double alpha =      1.0; 

  // Calculate Log Probabilities
  double log_spam = log(prior_spam);
  double log_ham = log(prior_ham);
  
  for (int word = 0; word < word_count; word++) {
      for (int i = 0; i < vocab_size; i++) {
	  if (strcmp(test_words[word], dictionary[i]) ==0) {
	      double p_spam = (spam_count[i] + alpha) / (total_spam + alpha * vocab_size);
	      double p_ham = (ham_count[i] + alpha) / (total_ham + alpha * vocab_size);
	      log_spam += log(p_spam);
	      log_ham += log(p_ham);
	      break;
	  }
      }
  } 

  double spam_score = exp(log_spam);
  double ham_score = exp(log_ham);
  double spam_prob = spam_score / (spam_score + ham_score);
  
  fprintf(out, "Spam probability: %.4lf\n", spam_prob);
  fprintf(out, "Classification: %s\n", spam_prob > 0.5 ? "SPAM" : "HAM");

  safe_close(in);
  safe_close(out);

  return EXIT_SUCCESS;
}
