# Overview

`get_next_line` is a function that returns a line read from a file descriptor. A "line" is a succession of characters that end with `\n` (newline) or with End Of File (EOF). The function allows reading from multiple file descriptors without losing the reading thread of each file descriptor or returning a wrong line.

## Features

- Read from multiple file descriptors simultaneously
- Handles different buffer sizes through the `BUFFER_SIZE` define
- Memory efficient with proper allocation and deallocation
- Handles errors gracefully
- Can read both files and standard input

## Function Prototype

```c
char *get_next_line(int fd);
```

## Parameters

- `fd`: The file descriptor to read from (0 for standard input)

## Return Value

- Returns the line that was read (including the terminating `\n` character if present)
- Returns NULL if there is nothing else to read or if an error occurred

## Compilation

The function can be compiled with any buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c
```

## Usage Example

```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Functions

The project includes several utility functions:

- `ft_strlen`: Calculate string length
- `ft_strcpy`: Copy strings
- `ft_strdup`: Duplicate strings
- `find_newline`: Find newline character in buffer
- `append_to_buffer`: Append read content to existing buffer
- `get_line`: Extract a line from buffer
- `handle_eof`: Handle end of file condition

## Technical Details

- Static buffer size can be defined at compilation with `-D BUFFER_SIZE=n`
- Supports up to 1024 file descriptors simultaneously
- No memory leaks
- Handles error cases (invalid fd, reading errors, memory allocation failures)

## Requirements

- C compiler (gcc/clang)
- Standard C library
- UNIX/Linux environment (for file operations)

## License

This project is part of 42 school curriculum.
