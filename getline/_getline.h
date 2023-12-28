#ifndef _GETLINE_H
#define _GETLINE_H

#define READ_SIZE 1024

/*	Libraries		*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*	Functions		*/
char *_getline(const int fd);
char *join_strings(char *str1, char *str2);
char *cpy_string(char *str, int amt);

#endif
