# tinycsv

## Usage

All functions and type definitions are located in @ref tinycsv.h

```c
#include <tinycsv.h>
```

A document (which is nothing but a pointer to a @ref tinycsv_document_t structure)
is opened with @ref tinycsv_open.

```c
const char filename[] = "example.csv";
tinycsv_document_t *doc = tinycsv_open(filename);
```

If you already have a `FILE*` pointer, this file can be read with
@ref tinycsv_read.

```c
tinycsv_document_t *doc = tinycsv_read(file_pointer);
```

From this point, both pointer a functionnaly equals.

To close the document properly, @ref tinycsv_close is used

```c
tinycsv_close(doc);
doc = NULL;
```

For more example programs, see the `examples/` directory.
