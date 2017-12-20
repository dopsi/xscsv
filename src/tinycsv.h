#ifndef _TINYCSV_H
#define _TINYCSV_H

#include <stddef.h>
#include <stdio.h>

typedef struct tinycsv_document tinycsv_document_t;

tinycsv_document_t* tinycsv_open(const char *filename);
tinycsv_document_t* tinycsv_read(FILE *file);
size_t tinycsv_lines(tinycsv_document_t *doc);
size_t tinycsv_columns(tinycsv_document_t *doc);
const char* tinycsv_get_content(tinycsv_document_t *doc, size_t x, size_t y);
void tinycsv_close(tinycsv_document_t *doc);
#endif // _TINYCSV_H
