# tinycsv

## Usage

All functions and type definitions are located in @ref tinycsv.h

```c
#include <tinycsv.h>
```

A document (which is nothing but a pointer to a @ref tinycsv_document_t structure)
is opened with @ref tinycsv_open. The `'\0'` parameter 

```c
const char filename[] = "example.csv";
tinycsv_document_t *doc = tinycsv_open(filename, '\0');
```

If you already have a `FILE*` pointer, this file can be read with
@ref tinycsv_read.

```c
tinycsv_document_t *doc = tinycsv_read(file_pointer, '\0');
```

To create an empty document, use @ref tinycsv_new.

```c
tinycsv_document_t *doc = tinycsv_new('\0');
```

From this point, all three pointers are functionnaly equal.

To access document properties, use @ref tinycsv_lines,
@ref tinycsv_columns or @tinycsv_columns_in_line.

```c
size_t lines_in_document = tinycsv_lines(doc);
size_t max_columns_in_document = tinycsv_columns(doc);
size_t columns_in_first_line = tinycsv_columns_in_line(doc, 0);
```

To close the document properly, @ref tinycsv_close is used

```c
tinycsv_close(doc);
doc = NULL;
```

For more example programs, see the `examples/` directory.
