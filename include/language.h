#ifndef LANGUAGE_H
#define LANGUAGE_H

struct language_entry {
    struct language_entry *next;
    struct language_entry *previous;
    char *word;
    char *definition;
};

int load_language(char *dir);
void unload_language();

char *get_word(int index);
char *get_index(int index);

#endif
