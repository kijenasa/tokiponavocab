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
