#ifndef _GETLINE_H
#define _GETLINE_H

/*	Libraries		*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*	Functions		*/
char *_getline(const int fd);
char* c_line(char* buff, int* p);
char* two_in_one(char* s1, char* s2);

#endif
