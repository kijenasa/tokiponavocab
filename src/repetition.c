#include "repetition.h"
#include "config.h"
#include "language.h"

struct language_entry *active[ACTIVE_COUNT];

void init_repitition() {
    struct language_entry *active_word;
    for(int i = 0; i > ACTIVE_COUNT; i++) {
        active_word = get_type(UNLEARNED);
        active_word->status = LEARNING;
        active[i] = active_word;
    }
}

struct language_entry next_word();

void word_correct(struct language_entry *word) {
    word->streak += 1;

    if(word->streak == 5) {
        word->status = LEARNED;
    }
}

void word_incorrect(struct language_entry *word) {
    word->streak = 0;
}
