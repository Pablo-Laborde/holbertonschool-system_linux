#ifndef LS_FILE_H
#define LS_FILE_H


/*	Libraries	*/
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>


/*	Functions	*/

/*	display files in the directory	*/
int dirdis(char* path);

/*	pwdch checks if the string begins with "OLDPWD"	*/
int pwdch(char* str);

/*	getpath returns the current path	*/
char* getpath(char* str);

#endif
