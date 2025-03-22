#include "readelf.h"


/**
* main- function
* @ac: int
* @av: char **
* Return: int
*/
int main(int ac, char **av)
{
	int fd = 0;
	data_t data;

	if (ac != 2)
	{
		printf("Usage: ./0-hreadelf <filename>\n");
		exit(EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);

	def_data(fd, &data);
	header_printer(&data);

	close(fd);
	exit(EXIT_SUCCESS);
}


/**
* header_printer- function
* @data: data_t *
* Return: void
*/
void header_printer(data_t *data)
{
	int ibe = (data->e_ident[EI_DATA] == ELFDATA2MSB);

	printf("ELF Header:\n");
	p_magic(data);
	p_class(data->e_ident[EI_CLASS]);
	p_data(data->e_ident[EI_DATA]);
	p_ver(data->e_ident[EI_VERSION]);
	p_osabi(data);
	p_abiv(data);
	p_type(data, ((ibe) ? bswap_16(data->e_type) : data->e_type));
	p_machine(data, ((ibe) ? bswap_16(data->e_machine) : data->e_machine));
	p_version(((ibe) ? bswap_32(data->e_version) : data->e_version));
	p_entry(((ibe) ? bswap_32(data->e_entry) : data->e_entry));
	p_phoff(((ibe) ? bswap_32(data->e_phoff) : data->e_phoff));
	p_shoff(((ibe) ? bswap_32(data->e_shoff) : data->e_shoff));
	p_flags(((ibe) ? bswap_32(data->e_flags) : data->e_flags));
	p_ehsize(((ibe) ? bswap_16(data->e_ehsize) : data->e_ehsize));
	p_phentsize(((ibe) ? bswap_16(data->e_phentsize) : data->e_phentsize));
	p_phnum(((ibe) ? bswap_16(data->e_phnum) : data->e_phnum));
	p_shentsize(((ibe) ? bswap_16(data->e_shentsize) : data->e_shentsize));
	p_shnum(((ibe) ? bswap_16(data->e_shnum) : data->e_shnum));
	p_shstrndx(((ibe) ? bswap_16(data->e_shstrndx) : data->e_shstrndx));
}


/**
* def_dat- func
* @fd: int
* @data: data_t *
* Return: void
*/
void def_data(int fd, data_t *data)
{
	int mode = 0;
	Elf32_Ehdr h1;
	Elf64_Ehdr h2;

	lseek(fd, 4, SEEK_SET);
	read(fd, &mode, 1);
	if ((mode == 0) || (mode > 2))
		exit(EXIT_FAILURE);
	lseek(fd, 0, SEEK_SET);

	if (mode == 1)
	{
		if (read(fd, &h1, sizeof(Elf32_Ehdr)) == -1)
			exit(errno);
		init_32(&h1, data);
	}
	else if (mode == 2)
	{
		if (read(fd, &h2, sizeof(Elf64_Ehdr)) == -1)
			exit(errno);
		init_64(&h2, data);
	}
	else
		exit(EXIT_FAILURE);
}


/**
 * init_32 - func
 * @head: struct size 32
 * @data: data
 */
void init_32(Elf32_Ehdr *head, data_t *data)
{
	int i = 0;

	for (i = 0; i < EI_NIDENT; i++)
		data->e_ident[i] = head->e_ident[i];
	data->e_type = head->e_type;
	data->e_machine = head->e_machine;
	data->e_version = head->e_version;
	data->e_entry = (long int)head->e_entry;
	data->e_phoff = (long int)head->e_phoff;
	data->e_shoff = (long int)head->e_shoff;
	data->e_flags = head->e_flags;
	data->e_ehsize = head->e_ehsize;
	data->e_phentsize = head->e_phentsize;
	data->e_phnum = head->e_phnum;
	data->e_shentsize = head->e_shentsize;
	data->e_shnum = head->e_shnum;
	data->e_shstrndx = head->e_shstrndx;
}


/**
 * init_64 - func
 * @head: struct size 64
 * @data: data
 */
void init_64(Elf64_Ehdr *head, data_t *data)
{
	int i = 0;

	for (i = 0; i < EI_NIDENT; i++)
		data->e_ident[i] = head->e_ident[i];
	data->e_type = head->e_type;
	data->e_machine = head->e_machine;
	data->e_version = head->e_version;
	data->e_entry = head->e_entry;
	data->e_phoff = head->e_phoff;
	data->e_shoff = head->e_shoff;
	data->e_flags = head->e_flags;
	data->e_ehsize = head->e_ehsize;
	data->e_phentsize = head->e_phentsize;
	data->e_phnum = head->e_phnum;
	data->e_shentsize = head->e_shentsize;
	data->e_shnum = head->e_shnum;
	data->e_shstrndx = head->e_shstrndx;
}
