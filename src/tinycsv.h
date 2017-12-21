#ifndef _TINYCSV_H
#define _TINYCSV_H

#include <stddef.h>
#include <stdio.h>

/**
 * @brief TinyCSV document handle
 *
 * For creation, use @ref tinycsv_open or @ref tinycsv_read.
 * This pointer must be destroyed using @ref tinycsv_close.
 **/
typedef struct tinycsv_document tinycsv_document_t;

/**
 * @brief Open a file giving it's filename
 *
 * @param filename Name of the file to be opened
 *
 * If filename is NULL, the returned document will be a NULL-pointer.
 *
 * @return a @ref tinycsv_document_t pointer, NULL on failure
 **/
tinycsv_document_t* tinycsv_open(const char *filename);

/**
 * @brief Read a file from a FILE pointer
 *
 * @param file FILE pointer
 *
 * If file is NULL, the returned document will be a NULL-pointer.
 *
 * @return a @ref tinycsv_document_t pointer, NULL on failure
 **/
tinycsv_document_t* tinycsv_read(FILE *file);

/**
 * @brief Obtain the number of lines in the document
 *
 * @param doc a @ref tinycsv_document_t pointer
 *
 * @return the number of lines in the document, 0 if doc is a NULL-pointer
 **/
size_t tinycsv_lines(tinycsv_document_t *doc);

/**
 * @brief Obtain the number of columns in the document
 *
 * @param doc a @ref tinycsv_document_t pointer
 *
 * @return the number of columns in the document, 0 if doc is a NULL-pointer
 **/
size_t tinycsv_columns(tinycsv_document_t *doc);

/**
 * @brief Get the document cell content
 *
 * @param doc a @ref tinycsv_document_t pointer
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
const char* tinycsv_get_content(tinycsv_document_t *doc, size_t x, size_t y);

/**
 * @brief Insert content into a @ref tinycsv_document_t
 *
 * @param doc the document
 * @param x the horizontal coordinate of the cell
 * @param y the vertical coordinate of the cell
 * @param new_content new content to be written
 *
 * @return a pointer to the new content, NULL otherwise
 */
const char* tinycsv_set_content(tinycsv_document_t *doc, size_t x, size_t y, const char *new_content);

/**
 * @brief Destroy a @ref tinycsv_document_t object
 *
 * @param doc a @ref tinycsv_document_t
 *
 * If doc is a NULL pointer, nothing happens.
 */
void tinycsv_close(tinycsv_document_t *doc);
#endif // _TINYCSV_H
