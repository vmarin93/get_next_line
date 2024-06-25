# get_next_line
A function that creates a stream, allowing for easy line extraction from files. Written as part of the curriculum for 42 coding school.
We make use of a local static variable, which is a variable that keeps its state between function calls, like a global variable, but unlike a global variable, it retains it's scope to the function where we declare it.
Our stream must handle the reading of any number of bytes at a time and, in the bonus part of the project, it should also be able to handle reading from multiple files at the same time.
The function returns a whole line from the file that we read from. On repetead calls, it will keep returning lines until the end of file.
# Walkthrough:
- get_next_line defines a static char array buffer(to be used to store what we read from the file), a char array line(to hold the line that we extract from the buffer, and also, to temporarily hold whatever we read from the file before appending to buffer) and a ssize_t bytes_read(we use this to store the return value of the read function).
- We start by checking that the file descriptor(to be referred to as fd moving forward) is a positive value(a negative value would indicate an incorrect fd). We then check that the BUFFER_SIZE(global variable that informs how many chars we read from the file at a time) is a positive value bigger than 0. Also, we check that the file pointed at by fd can be open for reading by calling the read function, trying to read 0 bytes from the file to see if we get a negative value(which would indicate the file can't be open for reading).
- We enter a loop whose condition is a function call to find_newline(this function iterates over the buffer and looks for the '\n' char. If it finds it, it returns it's index position within the buffer, else it return -1). We expect the return of find_newline to be -1 in order to enter the loop.
- Inside the loop, we initialize the char array line by allocating BUFFER_SIZE + 1 memory for it on the heap.
- We read from the fd into line, and then we null terminate the array.
- We initialize buffer to be the return of append_to_buffer(we gonna step into this function to look at it in more detail next).
- We finish the loop by freeing the memory we allocated for the char array line.
- Once we exit the loop, we use the char array line again, this time by initializing it to the get_line(we are going to step into this function to look at it in more detail after we step out of append_to_buffer).
- We return line, which by now should contain a whole line that we read from the file pointed to by the fd.

- append_to_buffer defines a char array new_buffer(if the static buffer in get_next_line is empty, then new_buffer stores just whatever we read from the file, otherwise new_buffer is going to store whatever is in the static buffer in get_next_line + whatever we read from the file) and a size_t buffer_len(this is going to store the length of the static buffer from get_next_line)
- we set buffer_len to 0 unless buffer is not NULL, in which case we would set buffer_len to the len of buffer.
- we allocate enough memory to the new_buffer such as that if buffer has data inside, new_buffer can accomodate both the data inside the buffer and the bytes_read from the fd.
- if the buffer is not NULL, we then copy the contents of it into new_buffer and we free the buffer, because we won't need it anymore, since append_to_buffer is going to return new_buffer, thus making the static buffer in get_next_line to point at this new_buffer address in memory.
- In order to now copy the line we just read from the fd into new_buffer, we need to point at the correct address in memory, which would be new_buffer + buffer_len. If say, there was nothing in the original buffer, and buffer_len is 0, then we copy the line into new_buffer staring at index 0. If we did have data in the original buffer, then buffer len is going to point us at the next available index of the array, after the data from the original buffer.
- The function returns new_buffer, so that now the original static buffer in get_next_line points at this address in the computer memory.

- 
