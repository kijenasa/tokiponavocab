#include <stdlib.h>
#include "config.h"
#include "language.h"

int main(int argc, char *argv[]) {
    load_language(LANGUAGE);
    unload_language();

    return EXIT_SUCCESS;
}
