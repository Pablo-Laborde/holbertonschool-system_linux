#include "hnm.h"



/**
 * manage_32 - func
 * @fd: int
 */
void manage_32(int fd)
{
	char c = 0;
	off_t cur = 0;
	Elf32_Ehdr h;
	Elf32_Shdr sh, strt;
	Elf32_Sym sym;
	uint8_t flag = 0;
	uint16_t	e_shnum = 0, i = 0;
	uint32_t	e_shoff = 0, strt_off = 0,
				sh_type = 0, sh_offset = 0, sh_link = 0, sh_size = 0,
				st_name = 0, j = 0, stp = 0;

	lseek(fd, 0, SEEK_SET);
	if (read(fd, &h, sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr))
		return;
	flag = h.e_ident[EI_DATA] == ELFDATA2MSB;
	e_shnum = (flag) ? bswap_16(h.e_shnum) : h.e_shnum;
	e_shoff = (flag) ? bswap_32(h.e_shoff) : h.e_shoff;
	cur = lseek(fd, e_shoff, SEEK_SET);
	for (; i < e_shnum; i++)
	{
		lseek(fd, cur, SEEK_SET);
		if (read(fd, &sh, sizeof(Elf32_Shdr)) != sizeof(Elf32_Shdr))
			return;
		cur += sizeof(Elf32_Shdr);
		sh_size = ((flag) ? bswap_32(sh.sh_size) : sh.sh_size) /
			sizeof(Elf32_Sym);
		sh_type = (flag) ? bswap_32(sh.sh_type) : sh.sh_type;
		sh_link = (flag) ? bswap_32(sh.sh_link) : sh.sh_link;
		if (sh_type == SHT_SYMTAB)
		{
			sh_offset = (flag) ? bswap_32(sh.sh_offset) : sh.sh_offset;
			lseek(fd, sh_offset, SEEK_SET);
			for (j = 0; j < sh_size; j++)
			{
				if (read(fd, &sym, sizeof(Elf32_Sym)) != sizeof(Elf32_Sym))
					return;
				st_name = (flag) ? bswap_32(sym.st_name) : sym.st_name;
				stp = e_shoff + (sh_link * sizeof(Elf32_Shdr));
				lseek(fd, stp, SEEK_SET);
				if (read(fd, &strt, sizeof(Elf32_Shdr)) != sizeof(Elf32_Shdr))
					return;
				strt_off = (flag) ? bswap_32(strt.sh_offset) : strt.sh_offset;
				lseek(fd, (strt_off + st_name), SEEK_SET);
				do {
					if (read(fd, &c, 1) != 1)
						return;
					putchar(c);
				} while (c);
				printf("\n");
			}
		}
	}
}
