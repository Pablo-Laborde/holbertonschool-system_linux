#include "hnm.h"


/**
* manage_64 - func
* @fd: int
* Return: 0 on Success, 1 on Failure
*/
int manage_64(int fd)
{
	data64_t	d;
	Elf64_Ehdr	h;
	Elf64_Shdr	sh;
	uint16_t	i = 0,
				symflag = 16;
	uint32_t	sh_type = 0;
	uint64_t	shdr_pos = 0,
				sh_size = 0,
				sh_offset = 0;

	lseek(fd, 0, SEEK_SET);
	if (read(fd, &h, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr))
		return (1);
	d.endianness = h.e_ident[EI_DATA] == ELFDATA2MSB;
	d.e_shnum = (d.endianness) ? bswap_16(h.e_shnum) : h.e_shnum;
	d.e_shoff = (d.endianness) ? bswap_64(h.e_shoff) : h.e_shoff;
	d.e_shstrndx = (d.endianness) ? bswap_16(h.e_shstrndx) : h.e_shstrndx;
	if (d.e_shstrndx == SHN_XINDEX)
	{
		lseek(fd, d.e_shoff, SEEK_SET);
		if (read(fd, &sh, sizeof(Elf64_Shdr)) != sizeof(Elf64_Shdr))
			return (1);
		d.e_shstrndx = (d.endianness) ? bswap_64(sh.sh_link) : sh.sh_link;
	}
	shdr_pos = lseek(fd, d.e_shoff, SEEK_SET);
	for (; i < d.e_shnum; i++)
	{
		lseek(fd, shdr_pos, SEEK_SET);
		if (read(fd, &sh, sizeof(Elf64_Shdr)) != sizeof(Elf64_Shdr))
			return (1);
		shdr_pos += sizeof(Elf64_Shdr);
		sh_size = ((d.endianness) ? bswap_64(sh.sh_size) : sh.sh_size) / sizeof(Elf64_Sym);
		if (!sh_size)
			continue;
		sh_type = (d.endianness) ? bswap_32(sh.sh_type) : sh.sh_type;
		d.sh_link = (d.endianness) ? bswap_64(sh.sh_link) : sh.sh_link;
		if (sh_type == SHT_SYMTAB)
		{
			if (filename)
				printf("%d: ", i);
			symflag = 0;
			sh_offset = (d.endianness) ? bswap_64(sh.sh_offset) : sh.sh_offset;
			lseek(fd, sh_offset, SEEK_SET);
			if (manage_sym64_list(fd, &d, sh_size))
				return (1);
		}
	}
	return (symflag);
}


/**
* manage_sym64_list - func
* @fd: int
* @d: data64_t
* @size: amount of sym structs to read
* Return: 0 on Success, 1 on Failure
*/
int manage_sym64_list(int fd, data64_t *d, uint64_t size)
{
	uint64_t j = 0, pos = 0;
	Elf64_Sym sym;

	pos = lseek(fd, 0, SEEK_CUR);
	for (; j < size; j++)
	{
		if (filename)
			printf("%ld ", j);
		lseek(fd, pos, SEEK_SET);
		if (read(fd, &sym, sizeof(Elf64_Sym)) != sizeof(Elf64_Sym))
			return (1);
		pos += sizeof(Elf64_Sym);
		if (filename  && (j == 37))
		{
			uint64_t st_value = (d->endianness) ? bswap_64(sym.st_value) : sym.st_value;
			uint32_t name = (d->endianness) ? bswap_64(sym.st_name) : sym.st_name;
			printf("%016lx - %d\n", st_value, name);
		}
		if (!sym.st_name)
			continue;
		if (filename  && (j == 37))
			printf("check\n");
		m64(fd, d, &sym);
	}
	if (filename)
		printf("\n");
	return (0);
}


/**
* m64 - func
* @fd: int
* @d: data64_t
* @sym: symbol
* Return: int
*/
int m64(int fd, data64_t *d, Elf64_Sym *sym) {
	char		c = 0, buffer[1024], name_buf[1024];
	uint16_t	st_shndx = 0;
	uint32_t	st_name = 0,
				sh_name = 0,
				sto = 0,
				pos = -1,
				n = -1;
	uint64_t	offset = 0,
				sh_strtab_off = 0,
				strtab_off = 0,
				st_value = 0;
	Elf64_Shdr sh_strtab, sobj, strtab;

	st_value = (d->endianness) ? bswap_64(sym->st_value) : sym->st_value;
	st_shndx = (d->endianness) ? bswap_16(sym->st_shndx) : sym->st_shndx;
	memset(buffer, 0, 1024);
	memset(name_buf, 0, 1024);
	if (st_shndx == SHN_UNDEF) {
		if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) /*{
			if ((sym->st_other == STV_DEFAULT) || (sym->st_other == STV_PROTECTED))
				c = 'W';
			else if ((sym->st_other == STV_HIDDEN) || (sym->st_other == STV_INTERNAL))
			}*/
				c = 'w';
		else
			c = 'U';
	} else if (ELF64_ST_TYPE(sym->st_info) == STT_FILE) {
		if (!sym->st_value)
			return (1);
		c = (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL) ? 'F' : 'f';
	} else if (st_shndx == SHN_ABS) {
		if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
			if ((sym->st_other == STV_DEFAULT) || (sym->st_other == STV_PROTECTED))
				c = 'A';
			else /* if ((sym->st_other == STV_HIDDEN) || (sym->st_other == STV_INTERNAL)) */
				c = 'a';
		} else
			c = (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL) ? 'A' : 'a';
	} else if (ELF64_ST_TYPE(sym->st_info) == STT_FUNC) {
		if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
			if ((sym->st_other == STV_DEFAULT) || (sym->st_other == STV_PROTECTED))
				c = 'W';
			else /* if ((sym->st_other == STV_HIDDEN) || (sym->st_other == STV_INTERNAL)) */
				c = 'w';
		} else
			c = (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL) ? 'T' : 't';
	} else if ((ELF64_ST_TYPE(sym->st_info) == STT_OBJECT) || (ELF64_ST_TYPE(sym->st_info) == STT_NOTYPE)) {
		offset = d->e_shoff + st_shndx * sizeof(Elf64_Shdr);
		lseek(fd, offset, SEEK_SET);
		if (read(fd, &sobj, sizeof(Elf64_Shdr)) != sizeof(Elf64_Shdr))
			return (1);
		offset = d->e_shoff + d->e_shstrndx * sizeof(Elf64_Shdr);
		lseek(fd, offset, SEEK_SET);
		if (read(fd, &strtab, sizeof(Elf64_Shdr)) != sizeof(Elf64_Shdr))
			return (1);
		sto = (d->endianness) ? bswap_64(strtab.sh_offset) : strtab.sh_offset;
		sh_name = (d->endianness) ? bswap_32(sobj.sh_name) : sobj.sh_name;
		lseek(fd, sto + sh_name, SEEK_SET);
		do {
			pos++;
			if (read(fd, buffer + pos, 1) != 1)
				return (1);
		} while (buffer[pos] && (pos < 1024));
		if (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT) {
			if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
				if ((sym->st_other == STV_DEFAULT) || (sym->st_other == STV_PROTECTED))
					c = 'V';
				else /* if ((sym->st_other == STV_HIDDEN) || (sym->st_other == STV_INTERNAL)) */
					c = 'v';
			} else if (!strcmp(buffer, ".bss") || !strcmp(buffer, "completed.7585"))
				c = (ELF64_ST_BIND(sym->st_info) == STB_LOCAL) ? 'b' : 'B';
			else if (!strcmp(buffer, ".rodata") || !strcmp(buffer, ".interp") || !strcmp(buffer, ".init") || !strcmp(buffer, ".fini") || !strcmp(buffer, ".eh_frame"))
				c = (ELF64_ST_BIND(sym->st_info) == STB_LOCAL) ? 'r' : 'R';
			else if (!strcmp(buffer, ".text") || !strcmp(buffer, ".plt") || !strcmp(buffer, ".text.startup") || !strcmp(buffer, ".fini_array") || !strcmp(buffer, ".init_array"))
				c = (ELF64_ST_BIND(sym->st_info) == STB_LOCAL) ? 't' : 'T';
			else /* (!strcmp(buffer, ".data") || !strcmp(buffer, ".jcr") || !strcmp(buffer, ".ctors") || !strcmp(buffer, ".dtors") || !strcmp(buffer, ".got")) */
				c = (ELF64_ST_BIND(sym->st_info) == STB_LOCAL) ? 'd' : 'D';
		} else /* if (ELF64_ST_TYPE(sym->st_info) == STT_NOTYPE) */ {
			if (!strcmp(buffer, ".fini_array") || !strcmp(buffer, ".init_array"))
				c = (ELF64_ST_BIND(sym->st_info) == STB_LOCAL) ? 't' : 'T';
			else if (!strcmp(buffer, ".bss") || !strcmp(buffer, "completed.7585"))
				c = (ELF64_ST_BIND(sym->st_info) == STB_LOCAL) ? 'b' : 'B';
			else if (!strcmp(buffer, ".text") || !strcmp(buffer, ".plt")) {
				if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
					if ((sym->st_other == STV_DEFAULT) || (sym->st_other == STV_PROTECTED))
						c = 'W';
					else /* if ((sym->st_other == STV_HIDDEN) || (sym->st_other == STV_INTERNAL)) */
						c = 'w';
				} else
					c = (ELF64_ST_BIND(sym->st_info) == STB_LOCAL) ? 't' : 'T';
			} else if (!strcmp(buffer, ".rodata") || !strcmp(buffer, ".interp") || !strcmp(buffer, ".init") || !strcmp(buffer, ".fini") || !strcmp(buffer, ".eh_frame_hdr")) {
				if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
					if ((sym->st_other == STV_DEFAULT) || (sym->st_other == STV_PROTECTED))
						c = 'V';
					else /* if ((sym->st_other == STV_HIDDEN) || (sym->st_other == STV_INTERNAL)) */
						c = 'v';
				} else
					c = (ELF64_ST_BIND(sym->st_info) == STB_LOCAL) ? 'r' : 'R';
			} else if (!strcmp(buffer, ".data") || !strcmp(buffer, ".jcr") || !strcmp(buffer, ".ctors") || !strcmp(buffer, ".dtors") || !strcmp(buffer, ".got")) {
				if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
					if ((sym->st_other == STV_DEFAULT) || (sym->st_other == STV_PROTECTED))
						c = 'W';
					else /* if ((sym->st_other == STV_HIDDEN) || (sym->st_other == STV_INTERNAL)) */
						c = 'w';
				} else
					c = (ELF64_ST_BIND(sym->st_info) == STB_LOCAL) ? 'd' : 'D';
			} else {
				if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
					if ((sym->st_other == STV_DEFAULT) || (sym->st_other == STV_PROTECTED))
						c = 'W';
					else /* if ((sym->st_other == STV_HIDDEN) || (sym->st_other == STV_INTERNAL)) */
						c = 'w';
				} else
					c = (ELF64_ST_BIND(sym->st_info) == STB_LOCAL) ? 'n' : 'N';
			}
		}
	} else if (ELF64_ST_TYPE(sym->st_info) == STT_COMMON) {
		if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
			if ((sym->st_other == STV_DEFAULT) || (sym->st_other == STV_PROTECTED))
				c = 'C';
			else /* if ((sym->st_other == STV_HIDDEN) || (sym->st_other == STV_INTERNAL)) */
				c = 'c';
		} else
			c = (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL) ? 'C' : 'c';
	} else if (ELF64_ST_TYPE(sym->st_info) == STT_SECTION)
		c = (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL) ? 'S' : 's';
	else if (ELF64_ST_TYPE(sym->st_info) == STT_LOPROC || ELF64_ST_TYPE(sym->st_info) == STT_HIPROC)
		c = 'p';
	else
		return (1);
	st_name = (d->endianness) ? bswap_32(sym->st_name) : sym->st_name;
	sh_strtab_off = d->e_shoff + (d->sh_link * sizeof(Elf64_Shdr));
	lseek(fd, sh_strtab_off, SEEK_SET);
	if (read(fd, &sh_strtab, sizeof(Elf64_Shdr)) != sizeof(Elf64_Shdr))
		return (1);
	strtab_off = (d->endianness) ? bswap_64(sh_strtab.sh_offset) : sh_strtab.sh_offset;
	lseek(fd, (strtab_off + st_name), SEEK_SET);
	do {
		n++;
		if (read(fd, name_buf + n, 1) != 1)
			return (1);
	} while (name_buf[n]);
	if (st_shndx == SHN_UNDEF)
		printf("                 %c %s\n", c, name_buf);
	else
		printf("%016lx %c %s\n", st_value, c, name_buf);
	return (0);
}
