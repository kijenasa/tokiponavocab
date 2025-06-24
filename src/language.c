#include "language.h"
#include <json-c/json_object.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

struct language_entry *language_entry_list;

static void register_language_entry(struct language_entry entry) {
    struct language_entry *head_entry = malloc(sizeof(struct language_entry));

    memcpy(head_entry, &entry, sizeof(struct language_entry));
    head_entry->next = NULL;
    head_entry->previous = NULL;

    if(language_entry_list == NULL) {
        language_entry_list = head_entry;
    } else {
        struct language_entry *index_entry = language_entry_list;
        while(index_entry->next != NULL)
            index_entry = index_entry->next;

        index_entry->next = head_entry;
        head_entry->previous = index_entry;
    }

}

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

    int language_len = json_object_array_length(parsed_json);

    struct language_entry entry;
    struct json_object *json_entry;
    for(int i = 0; i < language_len; i++) {
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

        register_language_entry(entry);
    }

    json_object_put(parsed_json);

    return 0;
}

void unload_language();

char *get_word(int index);
char *get_index(int index);
