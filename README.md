# GET_NEXT_LINE

A C function that reads a file descriptor line by line, one call at a time.


## About

In C, reading line by line from a file descriptor is not straightforward - `read()` has no concept of lines, only bytes. Get_next_line solves this by reading in chunks of `BUFFER_SIZE` and keeping track what has been read between calls using a static buffer.
It uses custom utility functions insted of the standard C library.


## Functions

### Internal functions
| Function | Description |
|----------|-------------|
| `join_buffer` | Joins the newly read chunk onto the accumulated buffer and frees the old one |
| `read_buffer` | Reads from the fd in chunks of _BUFFER_SIZE_, accumulating data until EOF |
| `get_line` | Extracts the current line from the buffer up to and including \n |
| `separate` | Trims the returned line from the buffer, keeping the remainder for next call |

### Main function
| `get_next_line` | Returns the next line from a file descriptor |


## Usage

```bash
git clone https://github.com/sarabezz/get_next_line.git
cd get_next_line
```

Include the header in your file:

```c
#include "get_next_line.h"
```

Compile it with your project:

```bash
gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c your_file.c -o your_program
```

To use a custom `BUFFER_SIZE`:

```bash
gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c your_file.c -D BUFFER_SIZE=64 -o your_program
```


## Key concepts:
- `read()`has no concept of iles -- it only read raw bytes
- Buffered reading with configurable chunk size via BUFFER_SIZE
- Careful memory management with `malloc` and `free` to avoid leaks
- Acummulating data between calls using static buffer


## Project info 

| | |
|---|---|
| Language | C |
| School | 42 Madrid |
| Status | ✅ Completed |
