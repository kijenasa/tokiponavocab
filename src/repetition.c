#include "repetition.h"
#include "config.h"
#include "language.h"

struct language_entry *active[ACTIVE_COUNT];
int relearn_timer = 0;

void init_repitition() {
    struct language_entry *active_word;
    for(int i = 0; i < ACTIVE_COUNT; i++) {
        active_word = get_type(UNLEARNED);
        active_word->status = LEARNING;
        active_word->index = i;
        active[i] = active_word;
    }
}

struct language_entry *next_word() {
    return get_type(LEARNING);
}

void word_correct(struct language_entry *word) {
    word->streak += 1;
    relearn_timer += 1;

    if(word->streak == 5) {
        word->status = LEARNED;

        enum status new_word_status;
        if(relearn_timer == RELEARN_FREQUENCY) {
            new_word_status = LEARNED;
        } else {
            new_word_status = UNLEARNED;
        }

        struct language_entry *new_word = get_type(new_word_status);
        new_word->status = LEARNING;

        new_word->index = word->index;
        word->index = -1;

        active[new_word->index] = new_word;
    }
}

void word_incorrect(struct language_entry *word) { word->streak = 0; }
