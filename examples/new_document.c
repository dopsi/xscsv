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

int main(int argc, char **argv) {
    printf("tinycsv new_document\n");

    tinycsv_document_t *doc = tinycsv_new(0x0);
    
    // TODO check for valid document

    size_t x, y, max_x, max_y;
    max_x = tinycsv_columns(doc);
    max_y = tinycsv_lines(doc);

    printf("== DOCUMENT ==\n");

    for (y = 0; y < max_y; ++y) {
        for (x = 0; x < max_x; ++x) {
            printf("%s,", tinycsv_get_content(doc, y, x));
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
            printf("%s,", tinycsv_get_content(doc, y, x));
        }
        printf("\n");
    }

    printf("== END DOCUMENT ==\n");

    tinycsv_close(doc);

    return 0;
}

