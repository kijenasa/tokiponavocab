#include "interface.h"
#include "config.h"
#include "language.h"
#include "repetition.h"
#include <stdio.h>
#include <string.h>

void open_interface() {
    int loop = 1;
    struct language_entry *word;

    char input[INPUT_LEN];
    while(loop) {
        word = next_word();
        printf("%s\n", word->definition);
        puts("Enter word:");

        fgets(input, INPUT_LEN, stdin);
        input[strcspn(input, "\n")] = '\0';

        if(strcmp(input, word->word) == 0) {
            word_correct(word);
            puts("Correct!");
        } else {
            word_incorrect(word);
            printf("Incorrect! Expected: %s\n", word->word);
        }
    }
}

void close_interface();
