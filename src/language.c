#include "language.h"
#include <json-c/json_object.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

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
    struct json_object *json_entry;
    for(int i = 0; i < language_entry_list_len; i++) {
        struct json_object *json_entry = json_object_array_get_idx(parsed_json, i);
        json_object_object_get_ex(json_entry, "word", &json_word);
        json_object_object_get_ex(json_entry, "definition", &json_definition);

        const char *word = json_object_get_string(json_word);
        const char *definition = json_object_get_string(json_definition);

        int entry_word_len = strlen(word);
        entry.word = malloc(entry_word_len);
        memcpy(entry.word, word, entry_word_len);

        int entry_definition_len = strlen(definition);
        entry.definition = malloc(entry_definition_len);
        memcpy(entry.definition, definition, entry_definition_len);

        language_entry_list[i] = entry;
    }

    json_object_put(parsed_json);

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

char *get_word(int index);
char *get_index(int index);
