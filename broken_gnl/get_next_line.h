#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H


#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>


char *get_next_line(int fd);

#endif