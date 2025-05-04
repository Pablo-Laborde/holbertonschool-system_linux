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
 * struct m32_s - structure
 * @c: char
 * @buf: char *
 * @name_buf: char *
 * @st_shndx: uint16_t
 * @st_value: uint32_t
 * @st_name: uint32_t
 * @sh_strtab_off: uint32_t
 * @strtab_off: uint32_t
 * @sh_name: uint32_t
 * @offset: uint32_t
 * @sto: uint32_t
 * @sh_strtab: Elf32_Shdr
 * @sobj: Elf32_Shdr
 * @strtab: Elf32_Shdr
 */
typedef struct m32_s
{
	
	
	uint32_t	
	
} m32_t;

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


#endif
