#include "readelf.h"


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
* p_mc- func
* @data: data_t *
* Return: void
*/
void p_mc(data_t *data)
{
	int i = 0;
	char hexa[3], *str;

	/* Magic */
	hexa[2] = '\0';
	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
	{
		hexamaker(data->e_ident[i], hexa);
		if (i)
			printf(" ");
		printf("%s", hexa);
	}
	printf("\n");

	/* Class */
	switch (data->e_ident[EI_CLASS]) {
		case ELFCLASS32:
			str = "Elf32";
			break;
		case ELFCLASS64:
			str = "Elf64";
			break;
	}
	printf("  Class:                             %s\n", str);
}


/**
* p_dv- func
* @data: data_t *
* Return: void
*/
void p_dv(data_t *data)
{
	char *str;

	/* Data */
	switch (data->e_ident[EI_DATA]) {
		case ELFDATANONE:
			str = "Unknown data format";
			break;
		case ELFDATA2LSB:
			str = "2's complement, little-endian";
			break;
		case ELFDATA2MSB:
			str = "2's complement, big-endian";
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
}


/**
* p_oa- func
* @data: data_t *
* Return: void
*/
void p_oa(data_t *data)
{
	char *str;

	/* OS/ABI */
	switch (data->e_ident[EI_OSABI]) {
		case ELFOSABI_SYSV:
			str = "Unix - System V";
			break;
		case ELFOSABI_HPUX:
			str = "Unix - HP-UX";
			break;
		case ELFOSABI_NETBSD:
			str = "Unix - NetBSD";
			break;
		case ELFOSABI_LINUX:
			str = "Unix - Linux";
			break;
		case ELFOSABI_SOLARIS:
			str = "Unix - Solaris";
			break;
		case ELFOSABI_IRIX:
			str = "Unix - IRIX";
			break;
		case ELFOSABI_FREEBSD:
			str = "Unix - FreeBSD";
			break;
		case ELFOSABI_TRU64:
			str = "Unix - TRU64";
			break;
		case ELFOSABI_ARM:
			str = "Unix - ARM";
			break;
		case ELFOSABI_STANDALONE:
			str = "Unix - Stand-alone (embedded)";
			break;
	}
	printf("  OS/ABI:                            %s\n", str);
}


/**
* p_at- func
* @data: data_t *
* Return: void
*/
void p_at(data_t *data)
{
	char *str;

	/* ABI Version */
	printf("  ABI Version:                       %d\n"
				, data->e_ident[EI_ABIVERSION]);

	/* Type */
	switch (data->e_type) {
		case ET_NONE:
			str = "NONE (Unknown type)";
			break;
		case ET_REL:
			str = "REL (Relocatable file)";
			break;
		case ET_EXEC:
			str = "EXEC (Executable file)";
			break;
		case ET_DYN:
			str = "DYN (Position-Independent Executable file)";
			break;
		case ET_CORE:
			str = "CORE (Core file)";
			break;
	}
	printf("  Type:                              %s\n", str);
}
