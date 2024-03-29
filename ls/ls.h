#ifndef LS_FILE_H
#define LS_FILE_H


/*	Libraries	*/
#include <dirent.h>

#include <errno.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>


/*	Functions	*/

/*  print directory or file */
int pdf(DIR *dir, char *dp, char *fn, int mode);

void tosum(char **env, char *dirpath, char *filename, char *av, int mode);

/*  check folder    */
char *folch(char *str, char **filename, int *mode);

/*  checks if path is a directory   */
DIR *dirch(char *path);

/*	getpath returns the current path	*/
char *getpath(char **env);

/*	pwdch checks if the string begins with "PWD"	*/
int pwdch(char *str);

/*  string compare  */
int strc(char *str1, char *str2);

#endif
