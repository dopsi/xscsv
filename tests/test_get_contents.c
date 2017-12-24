#include "tinycsv.h"

#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }

    tinycsv_document_t *doc = tinycsv_open(argv[1], 0x0);
    
    if (!doc) {
        return -1;
    }

    if (strcmp(tinycsv_get_content(doc, 0, 0), "Hello World!")) {
        return 1;
    }
    
    if (strcmp(tinycsv_get_content(doc, 0, 1), "1")) {
        return 2;
    }
    
    if (strcmp(tinycsv_get_content(doc, 0, 2), "1.25")) {
        return 3;
    }
    
    if (strcmp(tinycsv_get_content(doc, 1, 0), "12")) {
        return 11;
    }
    
    if (strcmp(tinycsv_get_content(doc, 1, 1), "24")) {
        return 12;
    }
    
    if (strcmp(tinycsv_get_content(doc, 1, 2), "36")) {
        return 13;
    }
    
    tinycsv_close(doc);

    return 0;
}
