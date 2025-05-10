#include "hnm.h"

#define SS32 sizeof(Elf32_Sym)

/**
* manage_32 - func
* @fd: int
* Return: 0 on Success, 1 on Failure
*/
int manage_32(int fd)
{
	data32_t	d;
	Elf32_Shdr	sh;
	uint16_t	i = 0, symflag = 16;
	uint32_t	shdr_pos = 0, sh_type = 0, sh_offset = 0, sh_size = 0;

	lseek(fd, 0, SEEK_SET);
	if (set_d32(fd, &d))
		return (1);
	if (d.e_shstrndx == SHN_XINDEX)
	{
		lseek(fd, d.e_shoff, SEEK_SET);
		if (read(fd, &sh, sizeof(Elf32_Shdr)) != sizeof(Elf32_Shdr))
			return (1);
		d.e_shstrndx = (d.ends) ? bswap_32(sh.sh_link) : sh.sh_link;
	}
	shdr_pos = lseek(fd, d.e_shoff, SEEK_SET);
	for (; i < d.e_shnum; i++)
	{
		lseek(fd, shdr_pos, SEEK_SET);
		if (read(fd, &sh, sizeof(Elf32_Shdr)) != sizeof(Elf32_Shdr))
			return (1);
		shdr_pos += sizeof(Elf32_Shdr);
		sh_size = ((d.ends) ? bswap_32(sh.sh_size) : sh.sh_size) / SS32;
		if (!sh_size)
			continue;
		sh_type = (d.ends) ? bswap_32(sh.sh_type) : sh.sh_type;
		d.sh_link = (d.ends) ? bswap_32(sh.sh_link) : sh.sh_link;
		if (sh_type == SHT_SYMTAB)
		{
			symflag = 0;
			sh_offset = (d.ends) ? bswap_32(sh.sh_offset) : sh.sh_offset;
			lseek(fd, sh_offset, SEEK_SET);
			if (manage_sym32_list(fd, &d, sh_size))
				return (1);
		}
	}
	return (symflag);
}


/**
* set_d32 - func
* @fd: int
* @d: data32_t
* Return: int
*/
int set_d32(int fd, data32_t *d)
{
	Elf32_Ehdr	h;

	if (read(fd, &h, sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr))
		return (1);
	d->ends = h.e_ident[EI_DATA] == ELFDATA2MSB;
	d->e_shnum = (d->ends) ? bswap_16(h.e_shnum) : h.e_shnum;
	d->e_shoff = (d->ends) ? bswap_32(h.e_shoff) : h.e_shoff;
	d->e_shstrndx = (d->ends) ? bswap_16(h.e_shstrndx) : h.e_shstrndx;
	return (0);
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
		if (!sym.st_name)
			continue;
		m32(fd, d, &sym);
	}
	return (0);
}


/**
* m32 - func
* @fd: int
* @d: data32_t
* @sym: symbol
* Return: int
*/
int m32(int fd, data32_t *d, Elf32_Sym *sym)
{
	char		c = 0, name_buf[1024];
	uint16_t	st_shndx = 0;
	uint32_t	st_name = 0, sh_strtab_off = 0, strtab_off = 0, st_value = 0,
				n = -1;
	Elf32_Shdr	sh_strtab;

	st_value = (d->ends) ? bswap_32(sym->st_value) : sym->st_value;
	st_shndx = (d->ends) ? bswap_16(sym->st_shndx) : sym->st_shndx;
	memset(name_buf, 0, 1024);
	if (st_shndx == SHN_UNDEF)
		c = (ELF32_ST_BIND(sym->st_info) == STB_WEAK) ? 'w' : 'U';
	else if (ELF32_ST_TYPE(sym->st_info) == STT_FILE)
	{
		if (!sym->st_value)
			return (1);
		c = (ELF32_ST_BIND(sym->st_info) == STB_GLOBAL) ? 'F' : 'f';
	}
	else if (st_shndx == SHN_ABS)
		c = abs_32(sym);
	else if (ELF32_ST_TYPE(sym->st_info) == STT_FUNC)
		c = func_32(sym);
	else if ((ELF32_ST_TYPE(sym->st_info) == STT_OBJECT) ||
		(ELF32_ST_TYPE(sym->st_info) == STT_NOTYPE))
	{
		c = mon_32(fd, d, sym, st_shndx);
		if (c == -1)
			return (1);
	}
	else if (ELF32_ST_TYPE(sym->st_info) == STT_COMMON)
		c = stt_common_32(sym);
	else if (ELF32_ST_TYPE(sym->st_info) == STT_SECTION)
		c = (ELF32_ST_BIND(sym->st_info) == STB_GLOBAL) ? 'S' : 's';
	else if ((ELF32_ST_TYPE(sym->st_info) == STT_LOPROC) ||
			(ELF32_ST_TYPE(sym->st_info) == STT_HIPROC))
		c = 'p';
	else
		return (1);
	st_name = (d->ends) ? bswap_32(sym->st_name) : sym->st_name;
	sh_strtab_off = d->e_shoff + (d->sh_link * sizeof(Elf32_Shdr));
	lseek(fd, sh_strtab_off, SEEK_SET);
	if (read(fd, &sh_strtab, sizeof(Elf32_Shdr)) != sizeof(Elf32_Shdr))
		return (1);
	strtab_off = (d->ends) ? bswap_32(sh_strtab.sh_offset) : sh_strtab.sh_offset;
	lseek(fd, (strtab_off + st_name), SEEK_SET);
	do {
		n++;
		if (read(fd, name_buf + n, 1) != 1)
			return (1);
	} while (name_buf[n]);
	if (st_shndx == SHN_UNDEF)
		printf("         %c %s\n", c, name_buf);
	else
		printf("%08x %c %s\n", st_value, c, name_buf);
	return (0);
}
