#include "language.h"
#include <json-c/json_object.h>
#include <json-c/json_tokener.h>
#include <json-c/printbuf.h>
#include <stdlib.h>
#include <stdio.h>
#include <json-c/json.h>

char ***language;

int load_language(char *dir) {
    FILE *fp;
    struct json_object *parsed_json;
    struct json_object *word;
    struct json_object *definition;

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
    json_object_object_get_ex(parsed_json, "word", &word);
    json_object_object_get_ex(parsed_json, "definition", &definition);

    printf("%d\n", json_object_array_length(parsed_json));

    json_object_put(parsed_json);

    return 0;
}

void unload_language();

char *get_word(int index);
char *get_index(int index);
