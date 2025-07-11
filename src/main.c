#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "config.h"
#include "language.h"
#include "repetition.h"
#include "interface.h"

int main(int argc, char *argv[]) {
    char *lang_buf;
    char *lang_name;
    int size;
    if(argc == 1) {
        lang_name = DEFAULT_LANGUAGE;
    } else {
        lang_name = argv[1];
    }

    size = strlen(LANGUAGE_DIR) + strlen(lang_name) + strlen(".json") + 1;
    lang_buf = malloc(size);
    snprintf(lang_buf, size, "%s%s.json", LANGUAGE_DIR, lang_name);
    printf("Training %s\n", lang_buf);

    struct timeval t;
    gettimeofday(&t, NULL);
    srand(t.tv_usec * t.tv_sec);

    load_language(lang_buf);
    init_repitition();
    open_interface();
    
    unload_language();

    return EXIT_SUCCESS;
}
