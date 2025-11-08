#include "io.h"
#include "naive.h"
#include "random.h"
#include "strings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define MAX_WORD_LENGTH 50
#define MAX_TEST_STRING_LENGTH 4096
#define MAX_TEST_STRING_WORDS 100

int main(int argc, char *argv[]) {

  // Handle arguments and files
  Args args;
  if (!parse_args(argc, argv, &args)) {
    fprintf(stderr, "Usage: %s [-i input] [-o output] [-s string] \n", argv[0]);
  }

  FILE *in = open_input_or_stdin(args.input_path);
  FILE *out = open_output_or_stdout(args.output_path);

  if (!in || !out) {
    fprintf(stderr, "error opening files.\n");
  }

  // Take in data, process, and put into Model
  int num_lines;
  fscanf(in, "%d", &num_lines);

  // The following three arrays are the "Model"
  char dictionary_words[num_lines][MAX_WORD_LENGTH];
  int spam_count[num_lines];
  int ham_count[num_lines];

  for (int i = 0; i < num_lines; i++)
    fscanf(in, "%49s %d %d", dictionary_words[i], &spam_count[i],
           &ham_count[i]);



  // Parse test string and put words iinto test_String_words
  char *token;
  const char delimiters[] = " .,:!?\n";
  char test_string_words[MAX_TEST_STRING_WORDS][MAX_WORD_LENGTH];
  int word_count = 0;

  token = strtok(args.string, delimiters);
  while (token != NULL && word_count < MAX_TEST_STRING_WORDS) {
    to_lowercase(token);
    strncpy(test_string_words[word_count], token, MAX_WORD_LENGTH - 1);
    test_string_words[word_count][MAX_WORD_LENGTH - 1] = '\0';
    word_count++;
    token = strtok(NULL, delimiters);
  }



  // Calculate naive bayes
  double total_spam_count = 1367.0;
  double total_ham_count = 4359.0;
  double prior_spam = total_spam_count / (total_spam_count + total_ham_count);    // Should read in instead of hard coding
  double prior_ham = 1 - prior_spam;
  double spam_probability = 0.0;
  double ham_probability = 0.0;
  double alpha = 1.0; // Laplace smoothing parameter to avoid division by zero

  spam_probability += log(prior_spam);
  ham_probability += log(prior_ham);
  
  for (int word = 0; word < word_count; word++) {
      int found = 0;
      for (int i = 0; i < num_lines; i++) {
	  if (strcmp(test_string_words[word], dictionary_words[i]) ==0) {
	      double p_word_given_spam = (spam_count[i] + alpha) / (total_spam_count + alpha * num_lines);
	      double p_word_given_ham = (ham_count[i] + alpha) / (total_ham_count + alpha * num_lines);
	      spam_probability += log(p_word_given_spam);
	      ham_probability += log(p_word_given_ham);
	      found = 1;
	      break;
	  }
      }
  } 

  fprintf(stdout, "Probability of Spam: %lf\n", (spam_probability / (spam_probability + ham_probability)));

  // Print words from input string (debugging)
  //fprintf(stdout, "List of Input Test String Words: \n");
  //for (int i = 0; i < word_count; i++)
  //  fprintf(stdout, "%s\n", test_string_words[i]);

  // Print input from arrays (debugging)
  // for (int i = 0; i < num_lines; i++)
  //  fprintf(stdout, "Word: %49s  Spam Count: %d  Ham Count: %d\n",
  //  dictionary_words[i],
  //         spam_count[i], ham_count[i]);

  // Print the test string (debugging)
  // fprintf(stdout, "Test String:  %s\n", args.string);

  // Print results
  // TODO

  safe_close(in);
  safe_close(out);

  return 0;
}
