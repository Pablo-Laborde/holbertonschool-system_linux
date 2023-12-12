#ifndef LS_FILE_H
#define LS_FILE_H


/*	Libraries	*/
#include <dirent.h>

#include <errno.h>

#include <stdio.h>
#include <string.h>
#include <sys/types.h>


/*	Functions	*/

/*	display files in the directory	*/
int dirdis(DIR*	directory, char* filename);

/*  lists directory recusively  */
void reclist(DIR* directory, char* filename);

/*  checks if path is a directory   */
DIR* dirch(char* path);

/*	getpath returns the current path	*/
char* getpath(char** env);

/*	pwdch checks if the string begins with "PWD"	*/
int pwdch(char* str);

#endif
