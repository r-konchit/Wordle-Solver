#include "search_util.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function should loop over the vocabulary (which contains num_words
// entries) and return the number of words in which that particular letter
// occurs
int score_letter(char letter, char **vocabulary, size_t num_words) {
  int c = 0;
  for (size_t i = 0; i < num_words; i++){
    if (vocabulary[i] == NULL) continue;
     for(int j = 0; j < (int)strlen(vocabulary[i]); j++){
        if (letter == vocabulary[i][j]){
          c++;
          break;
        }
     }
  }
  return c;
}

bool in(char letter, char *letters){
 for (int i = 0; i < (int)strlen(letters); i++){
   if (letter == letters[i]) return true;
 }
 return false;
}

// Calculate the score for a given word, where the letter_scores array has
// already been filled out and is guaranteed to be of length 26. Slot 0
// contains the score for 'a',  slot 25 contains the score for 'z'.
// The score for a word is the sum of all of the letter scores, *for unique
// letters*.  if the letter 'e' occurs three times, it only contributes to the
// score once.
int score_word(char *word, int *letter_scores) {
  int sum = 0;
  int letters_count = 0;
  char letters[26] = {0};
  for (int i = 0; i < (int)strlen(word); i++){
   // if this is the first time the letter is there: sum its value
   // in will add a new letter if its not in the letters string
   if (!in(word[i], letters)){
     sum += letter_scores[(word[i] - 97)];
     letters[letters_count++] = word[i];
    }
  }
  return sum;
}

// Returns the optimum guess, based on heuristic.
// free strings; theyre allocated once
char *get_guess(char **vocabulary, size_t num_words) {
  int letter_scores[26];

  for (int i = 0; i < 26; i++) {
    letter_scores[i] = score_letter('a' + i, vocabulary, num_words);
  }

  char *best_guess = NULL;
  int best_score = 0;
  int score = 0;
  for (size_t i = 0; i < num_words; i++) {
    if (vocabulary[i] == NULL) {
      continue;
    }
    score = score_word(vocabulary[i], letter_scores);
    if (score > best_score) {
      best_guess = vocabulary[i];
      best_score = score;
    }
  }
  return best_guess ? strdup(best_guess) : NULL;
}

// This function will filter down the vocabulary based on the knowledge that the
// specified letter DOESNT OCCUR in the secret word; for any of the words
// in the vocabulary that do contain that letter, free their pointers and set
// the corresponding slot to null
// returns the number of words that have been filtered from the vocabulary.
size_t filter_vocabulary_gray(char letter, char **vocabulary,
                              size_t num_words) {
  size_t c = 0;
  for (size_t i = 0; i < num_words; i++){
     char *word = vocabulary[i];
     bool deleteword = false;

     if (word != NULL){
       for (int j = 0; j < (int)strlen(word); j++){
          // removes a word if it contains the letter
          if (letter == word[j]){
            deleteword = true;
            break;
          }
       }
       
       if (deleteword){
          free(vocabulary[i]);
          vocabulary[i] = NULL;
          word = NULL;
          c++;
      }
    }
  }
  return c;
}

// filter down the vocabulary based on the knowledge that the
// specified letter occurs in the word, *but not at this particular position*.
// remove any words that either don't contain the letter at all
// returns the number of words that have been filtered from the vocabulary
size_t filter_vocabulary_yellow(char letter, int position, char **vocabulary,
                                size_t num_words) {
  int c = 0;
  for (size_t i = 0; i < num_words; i++){
    char *word = vocabulary[i];
    bool deleteword = false;
    int inner_counter = 0;
    if (word != NULL){
      for (int j = 0; j < (int)strlen(word); j++){

        if (letter != word[j]) inner_counter++;
        if ((letter == word[j] && position == j) || inner_counter == 5){
          deleteword = true;
          break;
        }
      }
    }
    if (deleteword){
      free(vocabulary[i]);
      vocabulary[i] = NULL;
      c++;
    }
  }
  return c;
}

// filters down the vocabulary based on the knowledge that the
// specified letter *definitely* occurs as the specified position. removes any
// word that does not contain, for the specified position, the specified letter
// Returns the number of words that have been filtered from the vocabulary
size_t filter_vocabulary_green(char letter, int position, char **vocabulary,
                               size_t num_words) {

  int c = 0;
  for (size_t i = 0; i < num_words; i++){
    char *word = vocabulary[i];
    bool deleteword = false;
    if (word == NULL || word[position] != letter){
        deleteword = true;
    }
    if (deleteword){
      free(vocabulary[i]);
      vocabulary[i] = NULL;
      c++;
    }
  }
  return c;
}

// frees each of the strings in vocab, AND the pointer vocab
// itself (which points to an array of char *)
void free_vocabulary(char **vocabulary, size_t num_words) {
  for (size_t i = 0; i < num_words; i++) {
    free(vocabulary[i]);
  }
  free(vocabulary);
}
