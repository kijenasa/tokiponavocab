#ifndef REPETITION_H
#define REPETITION_H

#include "language.h"

void init_repitition();

struct language_entry *next_word();

void word_correct(struct language_entry *word);

void word_incorrect(struct language_entry *word);

// TODO: ways to save progress to a file

#endif
