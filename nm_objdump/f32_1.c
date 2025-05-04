#include "hnm.h"


/**
* m32_p1 - func
* @fd: int
* @d: data32_t
* @sym: symbol
* Return: int
*/
int m32_p1(int fd, data32_t *d, Elf32_Sym *sym)
{
	m32_t m;

	memset(&m, 0, sizeof(m32_t));
	m.st_value = (d->endianness) ? bswap_32(sym->st_value) : sym->st_value;
	m.st_shndx = (d->endianness) ? bswap_16(sym->st_shndx) : sym->st_shndx;
	if (m.st_shndx == SHN_UNDEF)
		m.c = (ELF32_ST_BIND(sym->st_info) == STB_WEAK) ? 'w' : 'U';
	else if (ELF32_ST_TYPE(sym->st_info) == STT_FILE)
	{
		if (!sym->st_value)
			return (1);
		m.c = (ELF32_ST_BIND(sym->st_info) == STB_GLOBAL) ? 'F' : 'f';
	}
	else if (m.st_shndx == SHN_ABS)
	{
		if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
			m.c = ((sym->st_other == STV_DEFAULT) ||
				(sym->st_other == STV_PROTECTED)) ? 'A' : 'a';
		else
			m.c = (ELF32_ST_BIND(sym->st_info) == STB_GLOBAL) ? 'A' : 'a';
	}
	else if (ELF32_ST_TYPE(sym->st_info) == STT_FUNC)
	{
		if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
			m.c = ((sym->st_other == STV_DEFAULT) ||
				(sym->st_other == STV_PROTECTED)) ? 'W' : 'w';
		else
			m.c = (ELF32_ST_BIND(sym->st_info) == STB_GLOBAL) ? 'T' : 't';
	}
	return (m32_p2(fd, d, sym, &m));
}


/**
* m32_p2 - func
* @fd: int
* @d: data32_t
* @sym: symbol
* @m: m32_t
* Return: int
*/
int m32_p2(int fd, data32_t *d, Elf32_Sym *sym, m32_t *m)
{
	uint32_t n = -1;

	if ((ELF32_ST_TYPE(sym->st_info) == STT_OBJECT) ||
		(ELF32_ST_TYPE(sym->st_info) == STT_NOTYPE))
	{
		if (m32_p3(fd, d, sym, m))
			return (1);
	}
	else if (ELF32_ST_TYPE(sym->st_info) == STT_COMMON)
	{
		if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
			m->c = ((sym->st_other == STV_DEFAULT) ||
				(sym->st_other == STV_PROTECTED)) ? 'C' : 'c';
		else
			m->c = (ELF32_ST_BIND(sym->st_info) == STB_GLOBAL) ? 'C' : 'c';
	}
	else if (ELF32_ST_TYPE(sym->st_info) == STT_SECTION)
		m->c = (ELF32_ST_BIND(sym->st_info) == STB_GLOBAL) ? 'S' : 's';
	else if (ELF32_ST_TYPE(sym->st_info) == STT_LOPROC ||
			ELF32_ST_TYPE(sym->st_info) == STT_HIPROC)
		m->c = 'p';
	else
		return (1);
	m->st_name = (d->endianness) ? bswap_32(sym->st_name) : sym->st_name;
	m->sh_strtab_off = d->e_shoff + (d->sh_link * sizeof(Elf32_Shdr));
	lseek(fd, m->sh_strtab_off, SEEK_SET);
	if (read(fd, &m->sh_strtab, sizeof(Elf32_Shdr)) != sizeof(Elf32_Shdr))
		return (1);
	m->strtab_off = (d->endianness) ? bswap_32(m->sh_strtab.sh_offset)
		: m->sh_strtab.sh_offset;
	lseek(fd, (m->strtab_off + m->st_name), SEEK_SET);
	do {
		n++;
		if (read(fd, m->name_buf + n, 1) != 1)
			return (1);
	} while (m->name_buf[n]);
	(m->st_shndx == SHN_UNDEF) ?
		(printf("         %c %s\n", m->c, m->name_buf)) :
		(printf("%08x %c %s\n", m->st_value, m->c, m->name_buf));
	return (0);
}


/**
* m32_p3 - func
* @fd: int
* @d: data32_t
* @sym: symbol
* @m: m32_t
* Return: int
*/
int m32_p3(int fd, data32_t *d, Elf32_Sym *sym, m32_t *m)
{
	uint32_t pos = -1;

	m->offset = d->e_shoff + m->st_shndx * sizeof(Elf32_Shdr);
	lseek(fd, m->offset, SEEK_SET);
	if (read(fd, &m->sobj, sizeof(Elf32_Shdr)) != sizeof(Elf32_Shdr))
		return (1);
	m->offset = d->e_shoff + d->e_shstrndx * sizeof(Elf32_Shdr);
	lseek(fd, m->offset, SEEK_SET);
	if (read(fd, &m->strtab, sizeof(Elf32_Shdr)) != sizeof(Elf32_Shdr))
		return (1);
	m->sto = (d->endianness) ? bswap_32(m->strtab.sh_offset) :
		m->strtab.sh_offset;
	m->sh_name = (d->endianness) ? bswap_32(m->sobj.sh_name) :
		m->sobj.sh_name;
	lseek(fd, m->sto + m->sh_name, SEEK_SET);
	do {
		pos++;
		if (read(fd, m->buf + pos, 1) != 1)
			return (1);
	} while (m->buf[pos] && (pos < 1024));
	if (ELF32_ST_TYPE(sym->st_info) == STT_OBJECT)
		m32_p4(fd, d, sym, m);
	else /* if (ELF32_ST_TYPE(sym->st_info) == STT_NOTYPE) */
		m32_p5(fd, d, sym, m);
	return (0);
}


/**
* m32_p4 - func
* @fd: int
* @d: data32_t
* @sym: symbol
* @m: m32_t
* Return: int
*/
int m32_p4(int fd, data32_t *d, Elf32_Sym *sym, m32_t *m)
{
(void)fd;
(void)d;
if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
	m->c = ((sym->st_other == STV_DEFAULT) ||
		(sym->st_other == STV_PROTECTED)) ? 'V' : 'v';
else if (!strcmp(m->buf, ".bss"))
	m->c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 'b' : 'B';
else if (!strcmp(m->buf, ".rodata") || !strcmp(m->buf, ".interp")
	|| !strcmp(m->buf, ".init") || !strcmp(m->buf, ".fini"))
	m->c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 'r' : 'R';
else if (!strcmp(m->buf, ".text") || !strcmp(m->buf, ".plt")
	|| !strcmp(m->buf, ".text.startup"))
	m->c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 't' : 'T';
else
	m->c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 'd' : 'D';
return (0);
}


/**
* m32_p5 - func
* @fd: int
* @d: data32_t
* @sym: symbol
* @m: m32_t
* Return: int
*/
int m32_p5(int fd, data32_t *d, Elf32_Sym *sym, m32_t *m)
{
	(void)fd;
	(void)d;
	if (!strcmp(m->buf, ".text") || !strcmp(m->buf, ".plt"))
	{
		if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
			m->c = ((sym->st_other == STV_DEFAULT) ||
				(sym->st_other == STV_PROTECTED)) ? 'W' : 'w';
		else
			m->c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 't' : 'T';
	}
	else if (!strcmp(m->buf, ".rodata") || !strcmp(m->buf, ".interp")
		|| !strcmp(m->buf, ".init") || !strcmp(m->buf, ".fini"))
	{
		if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
		{
			m->c = ((sym->st_other == STV_DEFAULT) ||
				(sym->st_other == STV_PROTECTED)) ? 'V' : 'v';
		}
		else
			m->c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 'r' : 'R';
	}
	else if (!strcmp(m->buf, ".data") || !strcmp(m->buf, ".jcr") ||
			!strcmp(m->buf, ".ctors") || !strcmp(m->buf, ".dtors") ||
			!strcmp(m->buf, ".got"))
	{
		if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
			m->c = ((sym->st_other == STV_DEFAULT) ||
				(sym->st_other == STV_PROTECTED)) ? 'V' : 'v';
		else
			m->c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 'd' : 'D';
	}
	else
	{
		if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
			m->c = ((sym->st_other == STV_DEFAULT) ||
				(sym->st_other == STV_PROTECTED)) ? 'W' : 'w';
		else
			m->c = (ELF32_ST_BIND(sym->st_info) == STB_LOCAL) ? 'n' : 'N';
	}
	return (0);
}
