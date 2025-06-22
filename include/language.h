#ifndef LANGUAGE_H
#define LANGUAGE_H

int load_language(char *dir);
void unload_language();

char *get_word(int index);
char *get_index(int index);

#endif
