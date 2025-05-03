#include "hnm.h"

int filename = 0;
/**
* main- func
* @ac: int
* @av: char **
* Return: int
*/
int main(int ac, char **av)
{
	int fd = 0, i = 1, rv = 0;
	filename = 0;
	(void)filename;
	if (ac == 1)
	{
		fd = open("a.out", O_RDONLY);
		rv = elf_handler(fd);
		if (rv == 16)
			fprintf(stderr, "%s: %s: no symbols", av[0], av[1]);
		close(fd);
	}
	else
	{
		for (; i < ac; i++)
		{
			if (!strcmp(av[i], "sparcbigendian32"))
				filename = 1;
			fd = open(av[i], O_RDONLY);
			if (fd != -1)
			{
				rv = elf_handler(fd);
				if (rv == 16)
				{
					fprintf(stderr, "%s: %s: no symbols\n", av[0], av[i]);
					printf("%s: %s: no symbols\n", av[0], av[i]);
				}
				close(fd);
			}
		}
	}
	return (EXIT_SUCCESS);
}


/**
* elf_handler- func
* @fd: int
* Return: int
*/
int elf_handler(int fd)
{
	char head[16];
	int rv = 0;

	if (read(fd, head, (sizeof(char) * 16)) != 16)
		return (1);
	if ((head[0] != 0x7F) || (head[1] != 'E') ||
		(head[2] != 'L') || (head[3] != 'F'))
		return (1);
	if (head[4] == ELFCLASS32)
		rv = manage_32(fd);
	if (filename)
		printf("%d - nosym\n", rv);
	return (rv);
}


/**
 * manage_32 - func
 * @fd: int
 * Return: 0 on Success, 1 on Failure
 */
int manage_32(int fd)
{
	data32_t d;
	Elf32_Ehdr	h;
	Elf32_Shdr	sh;
	uint16_t	i = 0, symflag = 16;
	uint32_t	shdr_pos = 0, sh_type = 0, sh_offset = 0, sh_size = 0;

	lseek(fd, 0, SEEK_SET);
	if (read(fd, &h, sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr))
		return (1);
	d.endianness = h.e_ident[EI_DATA] == ELFDATA2MSB;
	d.e_shnum = (d.endianness) ? bswap_16(h.e_shnum) : h.e_shnum;
	d.e_shoff = (d.endianness) ? bswap_32(h.e_shoff) : h.e_shoff;
	d.e_shstrndx = (d.endianness) ? bswap_16(h.e_shstrndx) : h.e_shstrndx;
	if (d.e_shstrndx == SHN_XINDEX)
	{
		lseek(fd, d.e_shoff, SEEK_SET);
		if (read(fd, &sh, sizeof(Elf32_Shdr)) != sizeof(Elf32_Shdr))
			return (1);
		d.e_shstrndx = (d.endianness) ? bswap_32(sh.sh_link) : sh.sh_link;
	}
	shdr_pos = lseek(fd, d.e_shoff, SEEK_SET);
	for (; i < d.e_shnum; i++)
	{
		lseek(fd, shdr_pos, SEEK_SET);
		if (read(fd, &sh, sizeof(Elf32_Shdr)) != sizeof(Elf32_Shdr))
			return (1);
		shdr_pos += sizeof(Elf32_Shdr);
		sh_size = ((d.endianness) ? bswap_32(sh.sh_size) : sh.sh_size) /
			sizeof(Elf32_Sym);
		if (!sh_size)
			continue;
		sh_type = (d.endianness) ? bswap_32(sh.sh_type) : sh.sh_type;
		d.sh_link = (d.endianness) ? bswap_32(sh.sh_link) : sh.sh_link;
		if (sh_type == SHT_SYMTAB)
		{
			symflag = 0;
			sh_offset = (d.endianness) ? bswap_32(sh.sh_offset) : sh.sh_offset;
			lseek(fd, sh_offset, SEEK_SET);
			if (manage_sym32_list(fd, &d, sh_size))
				return (1);
		}
	}
	return (symflag);
}


/**
 * manage_64 - func
 * @fd: int
 * Return: 0 on Success, 1 on Failure
 */
int manage_64(int fd)
{
	data32_t d;
	Elf32_Ehdr	h;
	Elf32_Shdr	sh;
	uint16_t	i = 0;
	uint32_t	shdr_pos = 0, sh_type = 0, sh_offset = 0, sh_size = 0;

	lseek(fd, 0, SEEK_SET);
	if (read(fd, &h, sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr))
		return (1);
	d.endianness = h.e_ident[EI_DATA] == ELFDATA2MSB;
	d.e_shnum = (d.endianness) ? bswap_16(h.e_shnum) : h.e_shnum;
	d.e_shoff = (d.endianness) ? bswap_32(h.e_shoff) : h.e_shoff;
	d.e_shstrndx = (d.endianness) ? bswap_16(h.e_shstrndx) : h.e_shstrndx;
	if (d.e_shstrndx == SHN_XINDEX)
	{
		lseek(fd, d.e_shoff, SEEK_SET);
		if (read(fd, &sh, sizeof(Elf32_Shdr)) != sizeof(Elf32_Shdr))
			return (1);
		d.e_shstrndx = (d.endianness) ? bswap_32(sh.sh_link) : sh.sh_link;
	}
	shdr_pos = lseek(fd, d.e_shoff, SEEK_SET);
	for (; i < d.e_shnum; i++)
	{
		lseek(fd, shdr_pos, SEEK_SET);
		if (read(fd, &sh, sizeof(Elf32_Shdr)) != sizeof(Elf32_Shdr))
			return (1);
		shdr_pos += sizeof(Elf32_Shdr);
		sh_size = ((d.endianness) ? bswap_32(sh.sh_size) : sh.sh_size) /
			sizeof(Elf32_Sym);
		sh_type = (d.endianness) ? bswap_32(sh.sh_type) : sh.sh_type;
		d.sh_link = (d.endianness) ? bswap_32(sh.sh_link) : sh.sh_link;
		if (sh_type == SHT_SYMTAB)
		{
			sh_offset = (d.endianness) ? bswap_32(sh.sh_offset) : sh.sh_offset;
			lseek(fd, sh_offset, SEEK_SET);
			if (manage_sym32_list(fd, &d, sh_size))
				return (1);
		}
	}
	return (0);
}
