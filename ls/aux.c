/*	ls program - excersie 0	*/

#include "ls.h"


/**
* tosum- func
* @env: char**
* @dirpath: char*
* @filename: char*
* @av: char*
* @mode: int
* Return: void
*/
void tosum(char **env, char *dirpath, char *filename, char *av, int mode)
{
	char *path = NULL;
	DIR *directory = NULL;

	if (dirpath)
	{
		directory = dirch(dirpath);
		pdf(directory, dirpath, filename, mode);
		free(dirpath);
	}
	else
	{
		path = getpath(env);
		directory = dirch(path);
		pdf(directory, path, av, mode);
	}
	closedir(directory);
}
