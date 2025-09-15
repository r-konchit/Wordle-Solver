# Wordle Solver

* author: *Ron Konchitsky*

## introduction

This is a solver for Wordle, which implements a simple heuristic scorer

## function 1: int score_letter(char letter, char **vocabulary, size_t num_words)

This loop through every string in vocab and returns a sum of the number of times the given letter appears in vocab

## function 2: int score_word(char *word, int *letter_scores)

The given letter_scores list maps to the score for each letter a-z. This function loops through each element in the given word, will index the ascii value of that word into the given score array, and will return the sum of all the scores.

## function 3: size_t filter_vocabulary_gray(char letter, char **vocabulary, size_t num_words)

This will iterate through the vocabulary array of strings and will check if the given letter is in the word, if it is, that word will be freed and will set that position to NULL. This will keep track of every free word and will return the amount of words freed.

## function 4: size_t filter_vocabulary_yellow(char letter, int position, char **vocabulary, size_t num_words)

Similar to the function above filter_vocabulary_gray(), the difference is that the conditions for a word to be filtered are that either the word doesn't contain the specified letter, or if it does contain that letter but at the given position.

## function 5: size_t filter_vocabulary_green(char letter, int position, char **vocabulary, size_t num_words)

This will clear any word in vocab that doesn't have that specified letter in the given position, as with the previous two filter functions, this too returns the number of freed words.

## quick note:

I will be testing each of these functions by manually writing out a solution by hand and seeing if the functions I programmed return what's expected. I will likely edit this doc with some more cleaver ways to test code, looking forward!
