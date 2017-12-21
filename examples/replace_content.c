#include "tinycsv.h"

#include <stdio.h>

int main(int argc, char **argv) {
    printf("tinycsv replace_content\n");

    if (argc < 2) {
        return 1;
    }

    tinycsv_document_t *doc = tinycsv_open(argv[1]);
    
    // TODO check for valid document

    size_t x, y, max_x, max_y;
    max_x = tinycsv_columns(doc);
    max_y = tinycsv_lines(doc);

    for (y = 0; y < max_y; ++y) {
        for (x = 0; x < max_x; ++x) {
            printf("%s,", tinycsv_get_content(doc, x, y));
        }
        printf("\n");
    }

    tinycsv_set_content(doc, 0, 0, "Bonjour, Monde!");

    for (y = 0; y < max_y; ++y) {
        for (x = 0; x < max_x; ++x) {
            printf("%s,", tinycsv_get_content(doc, x, y));
        }
        printf("\n");
    }

    tinycsv_close(doc);

    return 0;
}

