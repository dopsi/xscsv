#include "tinycsv.h"

#include <stdio.h>

int main(int argc, char **argv) {
    printf("tinycsv new_document\n");

    tinycsv_document_t *doc = tinycsv_new();
    
    // TODO check for valid document

    size_t x, y, max_x, max_y;
    max_x = tinycsv_columns(doc);
    max_y = tinycsv_lines(doc);

    printf("== DOCUMENT ==\n");

    for (y = 0; y < max_y; ++y) {
        for (x = 0; x < max_x; ++x) {
            printf("%s,", tinycsv_get_content(doc, x, y));
        }
        printf("\n");
    }

    printf("== END DOCUMENT ==\n");

    tinycsv_set_content(doc, 3, 2, "Bonjour, Monde!");

    printf("== DOCUMENT ==\n");
    max_x = tinycsv_columns(doc);
    max_y = tinycsv_lines(doc);

    for (y = 0; y < max_y; ++y) {
        for (x = 0; x < max_x; ++x) {
            printf("%s,", tinycsv_get_content(doc, x, y));
        }
        printf("\n");
    }

    printf("== END DOCUMENT ==\n");

    tinycsv_close(doc);

    return 0;
}

