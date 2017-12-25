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
#include "xscsv.h"

#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }

    xscsv_document_t *doc = xscsv_open(argv[1], '\t');
    
    if (!doc) {
        return -1;
    }

    if (strcmp(xscsv_get_content(doc, 0, 0), "Hello World!")) {
        return 1;
    }
    
    if (strcmp(xscsv_get_content(doc, 0, 1), "1")) {
        return 2;
    }
    
    if (strcmp(xscsv_get_content(doc, 0, 2), "1.25")) {
        return 3;
    }
    
    if (strcmp(xscsv_get_content(doc, 1, 0), "12")) {
        return 11;
    }
    
    if (strcmp(xscsv_get_content(doc, 1, 1), "24")) {
        return 12;
    }
    
    if (strcmp(xscsv_get_content(doc, 1, 2), "36")) {
        return 13;
    }
    
    xscsv_close(doc);

    return 0;
}
