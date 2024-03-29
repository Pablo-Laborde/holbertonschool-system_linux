#ifndef READELF_H
#define READELF_H


/* Libraries */
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

	/* def_data.c */
		void def_data(int fd, data_t *data);
		void def_32(int fd, data_t *data);
		void def_64(int fd, data_t *data);

	/* p1.c */
		void hexamaker(int n, char *c);
		void p_mc(data_t *data);
		void p_dv(data_t *data);
		void p_oa(data_t *data);
		void p_at(data_t *data);

	/* p2.c */
		void p_m(data_t *data);
		void p_many(data_t *data);

#endif
