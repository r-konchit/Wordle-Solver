
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "search_util.h"

int main(void) {
  char words[10][6] = {"stalk", "scrap", "hello", "batch", "motif",
                       "tense", "ultra", "vital", "ether", "nadir"};

  // make a dynamically allocated vocabulary
  // free elements of it when necessary.
  char **vocabulary = calloc(10, sizeof(char *));
  for (int i = 0; i < 10; i++) {
    vocabulary[i] = strdup(words[i]);
  }
  size_t num_words = 10;


    int letter_scores[26] = {0};
    for (char c = 'a'; c <= 'z'; c++) {
        letter_scores[c - 'a'] = score_letter(c, vocabulary, num_words);
    }

    // find the score for "hello"
    int actual_score = score_word("hello", letter_scores);

    // Expected score based on how many words contain each unique letter
    int expected_score = letter_scores['h' - 'a']
                        + letter_scores['e' - 'a']
                        + letter_scores['l' - 'a']
                        + letter_scores['o' - 'a'];

    printf("Test score_word(\"hello\"): Expected = %d, Got = %d\n",
           expected_score, actual_score);


  // score_letter


   int result = score_letter('a', vocabulary, num_words);
   printf("Test score_letter('a'): Expected 6, Got %d\n", result);

   result = score_letter('x', vocabulary, num_words);
   printf("Test score_letter('x'): Expected 0, Got %d\n", result);




  // filter_vocabulary_green

    size_t removed = filter_vocabulary_green('s', 0, vocabulary, num_words);

    // 8/10 letters dont start with an s
    size_t expected_removed = 8;

    printf("Test filter_vocabulary_green('s'): Expected = %zu, Got = %zu\n",
           expected_removed, removed);

  // filter_vocabulary_yellow

    removed = filter_vocabulary_yellow('e', 0, vocabulary, num_words);

    expected_removed = 0;

    printf("Test filter_vocabulary_yellow('e'): Expected = %zu, Got = %zu\n",
           expected_removed, removed);

  //

  // filter_vocabulary_gray
 removed = filter_vocabulary_gray('t', vocabulary, num_words);

  // Expected: Words with 't' ("stalk", "batch", "tense", "ultra", "vital", "ether") should be removed
  expected_removed = 6;

  printf("Test filter_vocabulary_gray('t'): Expected = %zu, Got = %zu\n",
         expected_removed, removed);

  free_vocabulary(vocabulary, num_words);

  return 0;
}
