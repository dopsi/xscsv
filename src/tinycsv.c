/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Simon Doppler
 *
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the 
 * "Software"), to deal in the Software without restriction, including 
 * without limitation the rights to use, copy, modify, merge, publish, 
 * distribute, sublicense, and/or sell copies of the Software, and to 
 * permit persons to whom the Software is furnished to do so, subject to 
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **/
#include "tinycsv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TINYCSV_INTERNAL_BUFFER 1024

struct line_content {
    size_t len;
    char **elements;
};

struct tinycsv_document {
    size_t lines;
    size_t columns;
    struct line_content **lines_array;
    char separator;
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

// Source: https://stackoverflow.com/questions/122616/
// Note: This function returns a pointer to a substring of the original string.
// If the given string was allocated dynamically, the caller must not overwrite
// that pointer with the returned value, since the original pointer must be
// deallocated using the same allocator with which it was allocated.  The return
// value must NOT be deallocated using free() etc.
static char *trimwhitespace(char *str) {
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)    // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end+1) = 0;

    return str;
}

static struct line_content* process_line(char *raw_line, char separator) {
    size_t cnt = 0;
    size_t pch_len;
    char *pch = NULL;

    struct line_content *l = malloc(sizeof(struct line_content));

    if (!l) {
        return NULL;
    }

    char sep[2];
    sprintf(sep, "%c", separator);

    l->len = _strcharcount(raw_line, separator) + 1;
    l->elements = calloc(l->len, sizeof(char*));
    
    if (!l->elements) {
        free(l);
        return NULL;
    }

    pch = strtok(raw_line, sep);

    while (pch != NULL) {
        //if (pch[pch_len-1] == '\n') {
        //    pch[pch_len-1] = '\0';
        //    pch_len--;
        //}
        pch = trimwhitespace(pch);
        pch_len = strlen(pch);

        l->elements[cnt] = calloc(pch_len+1, sizeof(char));
        strcpy(l->elements[cnt], pch);
        cnt ++;
        pch = strtok (NULL, sep);
    }

    return l;
}

tinycsv_document_t* tinycsv_open(const char *filename, char separator) {
    if (!filename) {
        return NULL;
    }

    tinycsv_document_t *doc = NULL;
    FILE *f = NULL;
    f = fopen(filename, "r");
    if (!f) {
        return NULL;
    }
    doc = tinycsv_read(f, separator);
    fclose(f);

    return doc;
}

tinycsv_document_t* tinycsv_read(FILE *file, char separator) {
    if (!file) {
        return NULL;
    }

    tinycsv_document_t *doc = tinycsv_new(separator);

    if (!doc) {
        return NULL;
    }

    struct line_content **new_lines_array = NULL;
    char line_buffer[TINYCSV_INTERNAL_BUFFER] = { '\0' };

    while (fgets(line_buffer, TINYCSV_INTERNAL_BUFFER, file)) {
        new_lines_array = realloc(doc->lines_array, (doc->lines+1) * sizeof(struct line_content));

        //TODO improve failure handling
        if (!new_lines_array) {
            continue;
        }
        
        doc->lines_array = new_lines_array;
        doc->lines_array[doc->lines] = process_line(line_buffer, doc->separator);

        if (doc->lines_array[doc->lines]->len > doc->columns) {
            doc->columns = doc->lines_array[doc->lines]->len;
        }
        
        doc->lines++;
    }

    return doc;
}

tinycsv_document_t* tinycsv_new(char separator) {
    tinycsv_document_t *doc = malloc(sizeof(tinycsv_document_t));

    if (!doc) {
        return NULL;
    }

    doc->lines = 0;
    doc->columns = 0;
    doc->lines_array = NULL;

    if (!separator) {
            doc->separator = ',';
    } else {
            doc->separator = separator;
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

size_t tinycsv_columns_in_line(tinycsv_document_t *doc, size_t line) {
    if (!doc) {
        return 0;
    }

    if (line < doc->lines && doc->lines_array[line]) {
        return doc->lines_array[line]->len;
    }

    return 0;
}

const char* tinycsv_get_content(tinycsv_document_t *doc, size_t y, size_t x) {
    if (!doc) {
        return NULL;
    }

    if (y < doc->lines && doc->lines_array[y] && x < doc->lines_array[y]->len) {
        return doc->lines_array[y]->elements[x];
    }

    return NULL;
}

const char* tinycsv_set_content(tinycsv_document_t *doc, size_t y, size_t x, const char *new_content) {
    if (!doc || !new_content) {
        return NULL;
    }

    if (y >= doc->lines) {
        struct line_content **new_lines_array = NULL;
        new_lines_array = realloc(doc->lines_array, (y+1)*sizeof(struct line_content*));
        if (!new_lines_array) {
            return NULL;
        }

        doc->lines_array = new_lines_array;

        size_t i;
        for (i = doc->lines; i < y+1; ++i) {
            doc->lines_array[i] = NULL;
        }

        doc->lines = y+1;
    }

    if (! doc->lines_array[y] ) {
        doc->lines_array[y] = malloc(sizeof(struct line_content));
        doc->lines_array[y]->len = 0;
        doc->lines_array[y]->elements = NULL;
    }

    if (x >= doc->lines_array[y]->len) {
        // TODO add cells
        char **new_elements = NULL;
        new_elements = realloc(doc->lines_array[y]->elements, (x+1)*sizeof(char*));

        if (!new_elements) {
            return NULL;
        }

        doc->lines_array[y]->elements = new_elements;
        size_t i;
        for (i = doc->lines_array[y]->len; i < x+1; ++i) {
            doc->lines_array[y]->elements[i] = NULL;
        }

        doc->lines_array[y]->len = x+1;
        if (doc->columns < x+1) {
            doc->columns = x+1;
        }
    }
    size_t new_content_len = strlen(new_content);

    if (doc->lines_array[y]->elements[x]) {
        free(doc->lines_array[y]->elements[x]);
        doc->lines_array[y]->elements[x] = NULL;
    }

    doc->lines_array[y]->elements[x] = calloc(new_content_len+1, sizeof(char));
    strcpy(doc->lines_array[y]->elements[x], new_content);

    return doc->lines_array[y]->elements[x];
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
