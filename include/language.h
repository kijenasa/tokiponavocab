#ifndef LANGUAGE_H
#define LANGUAGE_H

enum status {
    LEARNED,
    LEARNING,
    UNLEARNED,
};

struct language_entry {
    enum status status;
    char *word;
    char *definition;
    int streak;
    int index; // The words index in the active array, -1 it its not in it.
};

int load_language(char *dir);
void unload_language();

struct language_entry *get_type(enum status type);

void print_word(struct language_entry *word);

#endif
