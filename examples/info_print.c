#include "tinycsv.h"

#include <stdio.h>

int main(int argc, char **argv) {
    printf("tinycsv info print\n");

    if (argc < 2) {
        return 1;
    }

    tinycsv_document_t *doc = tinycsv_open(argv[1]);
    // TODO check for valid document

    printf("Document data\n");
    printf("  ->lines = %u\n", tinycsv_lines(doc));
    printf("  ->columns = %u\n", tinycsv_columns(doc));
    tinycsv_close(doc);

    return 0;
}
