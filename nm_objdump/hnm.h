#ifndef HNM_H
#define HNM_H



/* Libraries */
	#include <byteswap.h>

	#include <elf.h>

	#include <fcntl.h>

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	#include <sys/stat.h>

	#include <unistd.h>


/**
 * struct data32_s - structure
 * @endianness: uint8_t
 * @e_shnum: uint16_t
 * @e_shstrndx: uint16_t
 * @e_shoff: uint32_t
 * @sh_link: uint32_t
 */
typedef struct data32_s
{
	uint8_t		endianness;
	uint16_t	e_shnum;
	uint32_t	e_shoff,
				e_shstrndx,
				sh_link;
} data32_t;


/**
 * struct data64_s - structure
 * @endianness: uint8_t
 * @e_shnum: uint16_t
 * @e_shstrndx: uint16_t
 * @e_shoff: uint32_t
 * @sh_link: uint32_t
 */
typedef struct data64_s
{
	uint8_t		endianness;
	uint16_t	e_shnum;
	uint64_t	e_shoff,
				e_shstrndx,
				sh_link;
} data64_t;


extern int filename;

/* Functions */

/* hnm.c */
int main(int ac, char **av);
int elf_handler(int fd);


/* dnm_32.c */
int manage_32(int fd);
int manage_sym32_list(int fd, data32_t *d, uint32_t size);
int m32(int fd, data32_t *d, Elf32_Sym *sym);


/* dnm_64.c */
int manage_64(int fd);
int manage_sym64_list(int fd, data64_t *d, uint64_t size);
int m64(int fd, data64_t *d, Elf64_Sym *sym);


#endif
