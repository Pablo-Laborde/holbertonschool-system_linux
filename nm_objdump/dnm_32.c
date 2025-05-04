#include "hnm.h"


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
		sh_type = (d.endianness) ? bswap_32(sh.sh_type) : sh.sh_type;
		d.sh_link = (d.endianness) ? bswap_32(sh.sh_link) : sh.sh_link;
		if (sh_size && (sh_type == SHT_SYMTAB))
		{
			symflag = 0;
			sh_offset = (d.endianness) ? bswap_32(sh.sh_offset) : sh.sh_offset;
			lseek(fd, sh_offset, SEEK_SET);
			manage_sym32_list(fd, &d, sh_size);
		}
	}
	return (symflag);
}


/**
* manage_sym32_list - func
* @fd: int
* @d: data32_t
* @size: amount of sym structs to read
* Return: 0 on Success, 1 on Failure
*/
int manage_sym32_list(int fd, data32_t *d, uint32_t size)
{
	uint32_t j = 0, pos = 0;
	Elf32_Sym sym;

	pos = lseek(fd, 0, SEEK_CUR);
	for (; j < size; j++)
	{
		lseek(fd, pos, SEEK_SET);
		if (read(fd, &sym, sizeof(Elf32_Sym)) != sizeof(Elf32_Sym))
			return (1);
		pos += sizeof(Elf32_Sym);
		if (/* !sym.st_value ||*/ !sym.st_name)
			continue;
		if (m32_p1(fd, d, &sym))
			continue;
	}
	return (0);
}
