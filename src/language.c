#include "language.h"
#define _POSIX_C_SOURCE 200809L
#include <json-c/json_object.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
#include <time.h>

struct language_entry *language_entry_list;
int language_entry_list_len;

int load_language(char *dir) {
    FILE *fp;
    struct json_object *parsed_json;
    struct json_object *json_word;
    struct json_object *json_definition;

    fp = fopen(dir, "r");
    if(fp == NULL)
        return -1;

    fseek(fp, 0, SEEK_END);
    int buffer_len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *buffer = malloc(buffer_len + 1);

    fread(buffer, buffer_len, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);
    free(buffer);

    language_entry_list_len = json_object_array_length(parsed_json);
    language_entry_list = malloc(sizeof(struct language_entry) * language_entry_list_len);

    struct language_entry entry;
    for(int i = 0; i < language_entry_list_len; i++) {
        struct json_object *json_entry = json_object_array_get_idx(parsed_json, i);
        json_object_object_get_ex(json_entry, "word", &json_word);
        json_object_object_get_ex(json_entry, "definition", &json_definition);

        const char *word = json_object_get_string(json_word);
        const char *definition = json_object_get_string(json_definition);

        entry.word = strdup(word);
        entry.definition = strdup(definition);

        entry.status = UNLEARNED;
        entry.streak = 0;
        entry.index = -1;

        language_entry_list[i] = entry;
    }

    json_object_put(parsed_json);

    srand(time(NULL));

    return 0;
}

void unload_language() {
    struct language_entry entry;
    for(int i = 0; i < language_entry_list_len; i++) {
        entry = language_entry_list[i];
        free(entry.word);
        free(entry.definition);
    }
    free(language_entry_list);
    language_entry_list = NULL;
}

struct language_entry *get_type(enum status type) { // BAD, returns NULL when it shouldnt
    int offset = rand();
    int index;

    for(int i = 0; i < language_entry_list_len; i++) {
        index = (i + offset) % language_entry_list_len;
        if(language_entry_list[index].status == type)
            return &language_entry_list[index];
    }

    puts("NULL");
    return NULL;
}

void print_word(struct language_entry *word) {
    printf("Index: %d\nStreak: %d\n", word->index, word->streak);
    printf("%s\n%s\n", word->word, word->definition);
    switch(word->status) {
    case UNLEARNED:
        puts("UNLEARNED");
        break;
    case LEARNING:
        puts("LEARNING");
        break;
    case LEARNED:
        puts("LEARNED");
        break;
    }
}
