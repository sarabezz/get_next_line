# GET_NEXT_LINE

A C function that reads a file descriptor line by line, one call at a time.


## About

In C, reading line by line from a file descriptor is not straightforward - `read()` has no concept of lines, only bytes. Get_next_line solves this by reading in chunks of `BUFFER_SIZE` and keeping track what has been read between calls using a static buffer.


## Functions

