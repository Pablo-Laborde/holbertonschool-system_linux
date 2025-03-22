#ifndef READELF_H
#define READELF_H


/* Libraries */
	#include <byteswap.h>

	#include <elf.h>
	#include <errno.h>

	#include <fcntl.h>

	#include <stdio.h>
	#include <stdlib.h>

	#include <unistd.h>


/* Structures */
	typedef struct data_s {
		unsigned char e_ident[EI_NIDENT];
		uint16_t      e_type;
		uint16_t      e_machine;
		uint32_t      e_version;
		long int      e_entry;
		long int      e_phoff;
		long int      e_shoff;
		uint32_t      e_flags;
		uint16_t      e_ehsize;
		uint16_t      e_phentsize;
		uint16_t      e_phnum;
		uint16_t      e_shentsize;
		uint16_t      e_shnum;
		uint16_t      e_shstrndx;
	} data_t;


/* Functions */
	void header_printer(data_t *data);
	void hexamaker(int n, char *c);
	void def_data(int fd, data_t *data);

/* aux_func_one.c */
	void p_osabi(data_t *data);
	void p_abiv(data_t *data);
	void p_type(data_t *data, int type);
	void p_machine(data_t *data, int machine);
	void p_version(int version);

/* aux_func_two.c */
	void p_entry(int entry);
	void p_phoff(int phoff);
	void p_shoff(int shoff);
	void p_flags(int flags);
	void p_ehsize(int ehsize);

/* aux_func_three.c */
	void p_phentsize(int phentsize);



#endif
