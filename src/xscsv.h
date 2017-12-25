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
#ifndef _XSCSV_H
#define _XSCSV_H

#include <stddef.h>
#include <stdio.h>

/**
 * @brief TinyCSV document handle
 *
 * For creation, use @ref xscsv_open or @ref xscsv_read.
 * This pointer must be destroyed using @ref xscsv_close.
 **/
typedef struct xscsv_document xscsv_document_t;

/**
 * @brief Open a file giving it's filename
 *
 * @param filename Name of the file to be opened
 * @param separator Field separator
 *
 * If filename is NULL, the returned document will be a NULL-pointer.
 *
 * @return a @ref xscsv_document_t pointer, NULL on failure
 **/
xscsv_document_t* xscsv_open(const char *filename, char separator);

/**
 * @brief Read a file from a FILE pointer
 *
 * @param file FILE pointer
 * @param separator Field separator
 *
 * If file is NULL, the returned document will be a NULL-pointer.
 *
 * @return a @ref xscsv_document_t pointer, NULL on failure
 **/
xscsv_document_t* xscsv_read(FILE *file, char separator);

/**
 * @brief Create a new empty @ref xscsv_document_t
 *
 * @param separator Field separator
 *
 * @return a @ref xscsv_document_t pointer, NULL on failure
 **/
xscsv_document_t* xscsv_new(char separator);

/**
 * @brief Obtain the number of lines in the document
 *
 * @param doc a @ref xscsv_document_t pointer
 *
 * @return the number of lines in the document, 0 if doc is a NULL-pointer
 **/
size_t xscsv_lines(xscsv_document_t *doc);

/**
 * @brief Obtain the number of columns in the document
 *
 * @param doc a @ref xscsv_document_t pointer
 *
 * @return the number of columns in the document, 0 if doc is a NULL-pointer
 **/
size_t xscsv_columns(xscsv_document_t *doc);

/**
 * @brief Get the number of columns in a given line
 *
 * @param doc a @ref xscsv_document_t pointer
 * @param line the queried line
 *
 * @return the number of elements in the line, 0 in case of error
 */
size_t xscsv_columns_in_line(xscsv_document_t *doc, size_t line);

/**
 * @brief Get the document cell content
 *
 * @param doc a @ref xscsv_document_t pointer
 * @param x the horizontal coordinate of the cell
 * @param y the vertical coordinate of the cell
 *
 * x and y coordinates start at 0 and increase towards the bottom for y or right for x.
 *
 * If the cell is not present in the document, the function will return NULL.
 *
 * If doc is NULL, the return value will be NULL.
 *
 * @return a pointer on the content, NULL in case of failure
 */
const char* xscsv_get_content(xscsv_document_t *doc, size_t y, size_t x);

/**
 * @brief Insert content into a @ref xscsv_document_t
 *
 * @param doc the document
 * @param x the horizontal coordinate of the cell
 * @param y the vertical coordinate of the cell
 * @param new_content new content to be written
 *
 * @return a pointer to the new content, NULL otherwise
 */
const char* xscsv_set_content(xscsv_document_t *doc, size_t y, size_t x, const char *new_content);

/**
 * @brief Destroy a @ref xscsv_document_t object
 *
 * @param doc a @ref xscsv_document_t
 *
 * If doc is a NULL pointer, nothing happens.
 */
void xscsv_close(xscsv_document_t *doc);
#endif // _XSCSV_H
