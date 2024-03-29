#include "readelf.h"


/**
* def_dat- func
* @fd: int
* @data: data_t *
* Return: void
*/
void def_data(int fd, data_t *data)
{
	int mode = 0;

	lseek(fd, 4, SEEK_SET);
	read(fd, &mode, 1);
	if ((mode == 0) || (mode > 2))
		exit(EXIT_FAILURE);
	lseek(fd, 0, SEEK_SET);

	if (mode == 1)
		def_32(fd, data);
	else if (mode == 2)
		def_64(fd, data);
	else
		exit(EXIT_FAILURE);
}

/**
* def_32- func
* @fd: int
* @data: data_t *
* Return: void
*/
void def_32(int fd, data_t *data)
{
	int i = 0;
	Elf32_Ehdr h1;

	if (read(fd, &h1, sizeof(Elf32_Ehdr)) == -1)
		exit(errno);
	for (; i < EI_NIDENT; i++)
		data->e_ident[i] = h1.e_ident[i];
	data->e_type = h1.e_type;
	data->e_machine = h1.e_machine;
	data->e_version = h1.e_version;
	data->e_entry = (long int)h1.e_entry;
	data->e_phoff = (long int)h1.e_phoff;
	data->e_shoff = (long int)h1.e_shoff;
	data->e_flags = h1.e_flags;
	data->e_ehsize = h1.e_ehsize;
	data->e_phentsize = h1.e_phentsize;
	data->e_phnum = h1.e_phnum;
	data->e_shentsize = h1.e_shentsize;
	data->e_shnum = h1.e_shnum;
	data->e_shstrndx = h1.e_shstrndx;
}


/**
* def_64- func
* @fd: int
* @data: data_t *
* Return: void
*/
void def_64(int fd, data_t *data)
{
	int i = 0;
	Elf64_Ehdr h2;

	if (read(fd, &h2, sizeof(Elf64_Ehdr)) == -1)
		exit(errno);
	for (; i < EI_NIDENT; i++)
		data->e_ident[i] = h2.e_ident[i];
	data->e_type = h2.e_type;
	data->e_machine = h2.e_machine;
	data->e_version = h2.e_version;
	data->e_entry = h2.e_entry;
	data->e_phoff = h2.e_phoff;
	data->e_shoff = h2.e_shoff;
	data->e_flags = h2.e_flags;
	data->e_ehsize = h2.e_ehsize;
	data->e_phentsize = h2.e_phentsize;
	data->e_phnum = h2.e_phnum;
	data->e_shentsize = h2.e_shentsize;
	data->e_shnum = h2.e_shnum;
	data->e_shstrndx = h2.e_shstrndx;
}
