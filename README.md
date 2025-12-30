# Wordle Solver

**Author:** Ron Konchitsky

## Introduction

This project is a Wordle solver implemented in C. The solver uses simple heuristic based scoring to rank guesses based on letter frequency across the remaining valid words. After each guess, the candidate set is filtered using Wordle's feedback (gray, yellow, and green), and the process repeats until the word is solved or no guesses remain.

The goal of this project is to build a clean solver from scratch and explore how constraint based filtering and heuristic scoring interact.

## Letter and Word Scoring

### int score_letter(char letter, char **vocabulary, size_t num_words)

This function iterates through the current vocabulary and counts how many times a given letter appears across all remaining words. The resulting count serves as a heuristic measure of how informative that letter is at the current stage of the game.

### int score_word(char *word, int *letter_scores)

This function assigns a score to a word by summing the precomputed scores of its letters. The `letter_scores` array maps each character (`a`–`z`) to its frequency based score. Words with higher total scores are considered better guesses because they are expected to eliminate more words on average.

## Vocabulary Filtering

After each guess, the solver applies Wordle feedback to eliminate invalid words from the vocabulary. Words that are filtered out are freed and replaced with `NULL` in the vocabulary array. Each filtering function returns the number of words removed.

### size_t filter_vocabulary_gray(char letter, char **vocabulary, size_t num_words)

This function removes any word that contains the specified letter. It corresponds to Wordle’s gray feedback, indicating that the letter does not appear anywhere in the target word.

### size_t filter_vocabulary_yellow(char letter, int position, char **vocabulary, size_t num_words)

This function removes any word that either does not contain the specified letter or contains it at the given position. This is Wordle’s yellow feedback: the letter must appear in the word, but not in the indicated position.

### size_t filter_vocabulary_green(char letter, int position, char **vocabulary, size_t num_words)

This function removes any word that does not have the specified letter at the given position. This corresponds to Wordle’s green feedback, where both the letter and its position are known to be correct.

## Design Decisions

This solver uses a frequency based heuristics; its scoring approach is simple and easy to reason about.

The vocabulary is stored as a mutable array of strings, where eliminated words are freed and replaced with `NULL`. This design keeps indexing stable across filtering operations and avoids unnecessary memory movement, at the cost of occasionally iterating over empty slots.

Filtering logic is implemented as separate composable functions for gray, yellow, and green feedback. This mirrors the way Wordle constraints are applied and makes it easier to reason about correctness when multiple constraints are combined.

## Testing Notes

At the current stage, these functions are tested by manually stepping through example Wordle scenarios and verifying that the vocabulary is filtered as expected after each operation. This approach helped validate correctness early on while developing the filtering logic.

As the project evolves, this testing strategy will be expanded to include more systematic and automated tests, particularly for edge cases such as overlapping constraints and repeated letters.
