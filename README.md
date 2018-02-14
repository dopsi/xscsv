# xscsv

[![Build Status](https://travis-ci.org/dopsi/xscsv.svg?branch=master)](https://travis-ci.org/dopsi/xscsv)

## Usage

All functions and type definitions are located in @ref xscsv.h

```c
#include <xscsv.h>
```

A document (which is nothing but a pointer to a @ref xscsv_document_t structure)
is opened with @ref xscsv_open. The `'\0'` parameter 

```c
const char filename[] = "example.csv";
xscsv_document_t *doc = xscsv_open(filename, '\0', '"');
```

If you already have a `FILE*` pointer, this file can be read with
@ref xscsv_read.

```c
xscsv_document_t *doc = xscsv_read(file_pointer, '\0', '"');
```

To create an empty document, use @ref xscsv_new.

```c
xscsv_document_t *doc = xscsv_new('\0', '"');
```

From this point, all three pointers are functionnaly equal.

To access document properties, use @ref xscsv_lines,
@ref xscsv_columns or @xscsv_columns_in_line.

```c
size_t lines_in_document = xscsv_lines(doc);
size_t max_columns_in_document = xscsv_columns(doc);
size_t columns_in_first_line = xscsv_columns_in_line(doc, 0);
```

To close the document properly, @ref xscsv_close is used

```c
xscsv_close(doc);
doc = NULL;
```

For more example programs, see the `examples/` directory.
