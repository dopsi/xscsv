#include "tinycsv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TINYCSV_INTERNAL_BUFFER 1024

struct line_content {
    size_t len;
    char **elements;
};

struct tinycsv_document {
    size_t lines;
    size_t columns;
    struct line_content **lines_array;
};

static size_t _strcharcount(const char *str, char c) {
    size_t cnt = 0;

    while (*str++) {
        if (*str == c) {
            cnt ++;
        }
    }
    return cnt;
}

static struct line_content* process_line(char *raw_line) {
    size_t cnt = 0;
    size_t pch_len;
    char *pch = NULL;

    struct line_content *l = malloc(sizeof(struct line_content));

    if (!l) {
        return NULL;
    }

    l->len = _strcharcount(raw_line, ',') + 1;
    l->elements = calloc(l->len, sizeof(char*));
    
    if (!l->elements) {
        free(l);
        return NULL;
    }

    pch = strtok(raw_line, ",");

    while (pch != NULL) {
        pch_len = strlen(pch);
        if (pch[pch_len-1] == '\n') {
            pch[pch_len-1] = '\0';
            pch_len--;
        }

        l->elements[cnt] = calloc(pch_len+1, sizeof(char));
        strcpy(l->elements[cnt], pch);
        cnt ++;
        pch = strtok (NULL, ",");
    }

    return l;
}

tinycsv_document_t* tinycsv_open(const char *filename) {
    tinycsv_document_t *doc = NULL;
    FILE *f = NULL;
    f = fopen(filename, "r");
    doc = tinycsv_read(f);
    fclose(f);

    return doc;
}

tinycsv_document_t* tinycsv_read(FILE *file) {
    tinycsv_document_t *doc = malloc(sizeof(tinycsv_document_t));

    struct line_content **new_lines_array = NULL;
    char line_buffer[TINYCSV_INTERNAL_BUFFER] = { '\0' };


    if (!doc) {
        return NULL;
    }

    doc->lines = 0;
    doc->columns = 0;
    doc->lines_array = NULL;

    while (fgets(line_buffer, TINYCSV_INTERNAL_BUFFER, file)) {
        new_lines_array = realloc(doc->lines_array, (doc->lines+1) * sizeof(struct line_content));

        //TODO improve failure handling
        if (!new_lines_array) {
            continue;
        }
        
        doc->lines_array = new_lines_array;
        doc->lines_array[doc->lines] = process_line(line_buffer);

        if (doc->lines_array[doc->lines]->len > doc->columns) {
            doc->columns = doc->lines_array[doc->lines]->len;
        }
        
        doc->lines++;
    }

    return doc;
}

size_t tinycsv_lines(tinycsv_document_t *doc) {
    if (doc) {
        return doc->lines;
    } else {
        return 0;
    }
}

size_t tinycsv_columns(tinycsv_document_t *doc) {
    if (doc) {
        return doc->columns;
    } else {
        return 0;
    }
}

const char* tinycsv_get_content(tinycsv_document_t *doc, size_t x, size_t y) {
    if (!doc) {
        return NULL;
    }
    if (y < doc->lines && doc->lines_array[y] && x < doc->lines_array[y]->len) {
        return doc->lines_array[y]->elements[x];
    }

    return NULL;
}

void tinycsv_close(tinycsv_document_t *doc) {
    if (! doc ) {
        return;
    }

    size_t x, y;

    for (y = 0; y < doc->lines; ++y) {
        if (doc->lines_array[y]) {
            for (x = 0; x < doc->lines_array[y]->len; ++x) {
                free(doc->lines_array[y]->elements[x]);
            }
            free(doc->lines_array[y]->elements);
            free(doc->lines_array[y]);
        }
    }

    free(doc->lines_array);
    free(doc);
}
