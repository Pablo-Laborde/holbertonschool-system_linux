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
 */
typedef struct data32_s
{
	uint8_t		endianness;
	uint16_t	e_shnum;
	uint32_t	e_shoff,
				e_shstrndx,
				sh_link,
				seen_arr[1024],
				seen_count;
} data32_t;



/* Functions */

/* hnm.c */
int main(int ac, char **av);
void elf_handler(int fd);
int manage_32(int fd);
int manage_64(int fd);

/* dnm_32.c */
int manage_sym32_list(int fd, data32_t *d, uint32_t size);
int p_address(data32_t *d, Elf32_Sym *sym);
int p_type(int fd, data32_t *d, Elf32_Sym *sym);
int p_name(int fd, data32_t *d, Elf32_Sym *sym);

/* dnm_64.c */


#endif
