#ifndef LS_FILE_H
#define LS_FILE_H


/*	Libraries	*/
#include <dirent.h>

#include <errno.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


/*	Functions	*/
void pf(char *path, int flags);
int manage_files(int ac, char **av, int flags);
int check_condition(int flags, char *fn);
int print_dir(int flags, char *path);
int set_flags(int ac, char **av, int *flags);


#endif
