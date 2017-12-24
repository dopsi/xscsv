#include "tinycsv.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }

    tinycsv_document_t *doc = tinycsv_open(argv[1], '\t');
    
    if (!doc) {
        return -1;
    }

    if (tinycsv_lines(doc) != 2) {
        return 1;
    }
    
    tinycsv_close(doc);

    return 0;
}
