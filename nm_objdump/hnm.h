#ifndef HNM_H
#define HNM_H



/* Libraries */
	#include <byteswap.h>

	#include <elf.h>

	#include <fcntl.h>

	#include <stdio.h>
	#include <stdlib.h>

	#include <sys/stat.h>

	#include <unistd.h>



/* Functions */

/* hnm.c */
	int main(int ac, char **av);
	void elf_handler(int fd);
	void display_content(int fd);

/* dnm_32.c */
	void manage_32(int fd);


#endif
