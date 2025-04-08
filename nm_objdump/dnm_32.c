#include "hnm.h"



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
		if (p_address(d, &sym))
			return (1);
		if (p_type(fd, d, &sym))
			return (1);
		putchar(' ');
		if (p_name(fd, d, &sym))
			return (1);
	}
	return (0);
}


/**
 * p_address - func
 * @d: data32_t
 * @sym: symbol
 * Return: 0 on Success, 1 on Failure
 */
int p_address(data32_t *d, Elf32_Sym *sym)
{
	uint16_t st_shndx = 0;
	uint32_t st_value = 0;

	st_value = (d->endianness) ? bswap_32(sym->st_value) : sym->st_value;
	st_shndx = (d->endianness) ? bswap_16(sym->st_shndx) : sym->st_shndx;
	if (st_shndx == SHN_UNDEF)
		printf("        ");
	else
		printf("%08x", st_value);
	fflush(NULL);
	putchar(' ');
	return (0);
}


/**
 * p_type - func
 * @fd: int
 * @d: data32_t
 * @sym: symbol
 * Return: int
 */
int p_type(int fd, data32_t *d, Elf32_Sym *sym)
{
	char c = 0, buffer[8];
	uint8_t pos = -1;
	uint16_t st_shndx = 0;
	uint32_t offset = 0, sh_name = 0, sto = 0;
	Elf32_Shdr sobj, strtab;

	memset(buffer, 0, 8);
	st_shndx = (d->endianness) ? bswap_16(sym->st_shndx) : sym->st_shndx;
	if (st_shndx == SHN_UNDEF)
		c = (ELF32_ST_BIND(sym->st_info) == STB_WEAK) ? 'w' : 'U';
	else if (ELF32_ST_TYPE(sym->st_info) == STT_FILE)
		c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 'f' : 'F';
	else if (st_shndx == SHN_ABS)
		c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 'a' : 'A';
	else if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
		c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 'w' : 'W';
	else if (ELF32_ST_TYPE(sym->st_info) == STT_FUNC)
		c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 't' : 'T';
	else if ((ELF32_ST_TYPE(sym->st_info) == STT_OBJECT) ||
		(ELF32_ST_TYPE(sym->st_info) == STT_NOTYPE))
	{
		offset = d->e_shoff + st_shndx * sizeof(Elf32_Shdr);
		lseek(fd, offset, SEEK_SET);
		if (read(fd, &sobj, sizeof(Elf32_Shdr)) != sizeof(Elf32_Shdr))
			return (1);
		offset = d->e_shoff + d->e_shstrndx * sizeof(Elf32_Shdr);
		lseek(fd, offset, SEEK_SET);
		if (read(fd, &strtab, sizeof(Elf32_Shdr)) != sizeof(Elf32_Shdr))
			return (1);
		sto = (d->endianness) ? bswap_32(strtab.sh_offset) : strtab.sh_offset;
		sh_name = (d->endianness) ? bswap_32(sobj.sh_name) : sobj.sh_name;
		lseek(fd, sto + sh_name, SEEK_SET);
		do {
			pos++;
			if (read(fd, buffer + pos, 1) != 1)
				return (1);
		} while (buffer[pos] && (pos < 8));
		if (ELF32_ST_TYPE(sym->st_info) == STT_OBJECT)
		{
			if (!strcmp(buffer, ".bss"))
				c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 'b' : 'B';
			else if (!strcmp(buffer, ".rodata"))
				c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 'r' : 'R';
			else /* (!strcmp(buffer, ".data")) */
				c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 'd' : 'D';
		}
		else
		{
			if (!strcmp(buffer, ".text"))
				c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 't' : 'T';
			else
				c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 'n' : 'N';
		}
	}
	else if (ELF32_ST_TYPE(sym->st_info) == STT_COMMON)
		c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 'c' : 'C';
	else
		c = '?';
	putchar(c);
	return (0);
}


/**
 * p_name - func
 * @fd: int
 * @d: data32_t
 * @sym: symbol
 * Return: int
 */
int p_name(int fd, data32_t *d, Elf32_Sym *sym)
{
	char c = 0;
	uint32_t st_name = 0, sh_strtab_off = 0, strtab_off = 0;
	Elf32_Shdr sh_strtab;

	st_name = (d->endianness) ? bswap_32(sym->st_name) : sym->st_name;
	sh_strtab_off = d->e_shoff + (d->sh_link * sizeof(Elf32_Shdr));
	lseek(fd, sh_strtab_off, SEEK_SET);
	if (read(fd, &sh_strtab, sizeof(Elf32_Shdr)) != sizeof(Elf32_Shdr))
		return (1);
	strtab_off = (d->endianness) ? bswap_32(sh_strtab.sh_offset)
		: sh_strtab.sh_offset;
	lseek(fd, (strtab_off + st_name), SEEK_SET);
	do {
		if (read(fd, &c, 1) != 1)
			return (1);
		putchar(c);
	} while (c);
	printf("\n");
	return (0);
}
