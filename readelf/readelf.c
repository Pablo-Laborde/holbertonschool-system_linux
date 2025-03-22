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
	int i = 0, ibe = (data->e_ident[EI_DATA] == ELFDATA2MSB);
	char hexa[3], *str;

	printf("ELF Header:\n");

	/* Magic */
	hexa[2] = '\0';
	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
	{
		hexamaker(data->e_ident[i], hexa);
		printf("%s", hexa);
		printf(" ");
	}
	printf("\n");

	/* Class */
	switch (data->e_ident[EI_CLASS]) {
		case ELFCLASS32:
			str = "ELF32";
			break;
		case ELFCLASS64:
			str = "ELF64";
			break;
	}
	printf("  Class:                             %s\n", str);

	/* Data */
	switch (data->e_ident[EI_DATA]) {
		case ELFDATANONE:
			str = "Unknown data format";
			break;
		case ELFDATA2LSB:
			str = "2's complement, little endian";
			break;
		case ELFDATA2MSB:
			str = "2's complement, big endian";
			break;
	}
	printf("  Data:                              %s\n", str);

	/* Version */
	switch (data->e_ident[EI_VERSION]) {
		case EV_NONE:
			str = "Invalid version";
			break;
		case EV_CURRENT:
			str = "(current)";
			break;
	}
	printf("  Version:                           %d %s\n"
				, data->e_ident[EI_VERSION], str);

	/* OS/ABI */
	p_osabi(data);

	/* ABI Version */
	p_abiv(data);

	/* Type */
	p_type(data, ((ibe) ? bswap_16(data->e_type) : data->e_type));

	/* Machine */
	p_machine(data, ((ibe) ? bswap_16(data->e_machine) : data->e_machine));

	/* Version */
	p_version(((ibe) ? bswap_16(data->e_version) : data->e_version));

	/* Entry */
	printf("  Entry point address:               0x%lx\n", data->e_entry);

	/* PHOFF */
	printf("  Start of program headers:          %ld (bytes into file)\n"
				, data->e_phoff);

	/* SHOFF */
	printf("  Start of section headers:          %ld (bytes into file)\n"
				, data->e_shoff);

	/* Flags */
	printf("  Flags:                             0x%d\n", data->e_flags);

	/* Size of header */
	printf("  Size of this header:               %d (bytes)\n"
				, data->e_ehsize);

	/* Size of program headers */
	printf("  Size of program headers:           %d (bytes)\n"
				, data->e_phentsize);

	/* Number program headers */
	printf("  Number of program headers:         %d\n", data->e_phnum);

	/* Size of section headers */
	printf("  Size of section headers:           %d (bytes)\n"
				, data->e_shentsize);

	/* Number section headers */
	printf("  Number of section headers:         %d\n", data->e_shnum);

	/* Section header string table index */
	printf("  Section header string table index: %d\n", data->e_shstrndx);
}


/**
* hexamaker- func
* @n: int
* @c: char *
* Return: void
*/
void hexamaker(int n, char *c)
{
	char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
									'8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

	c[1] = hex[n % 16];
	c[0] = hex[n / 16];
}


/**
* def_dat- func
* @fd: int
* @data: data_t *
* Return: void
*/
void def_data(int fd, data_t *data)
{
	int i = 0, mode = 0;
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
	}
	else if (mode == 2)
	{
		if (read(fd, &h2, sizeof(Elf64_Ehdr)) == -1)
			exit(errno);
	}
	else
		exit(EXIT_FAILURE);

	if (mode == 1)
	{
		for (i = 0; i < EI_NIDENT; i++)
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
	else
	{
		for (i = 0; i < EI_NIDENT; i++)
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
}
