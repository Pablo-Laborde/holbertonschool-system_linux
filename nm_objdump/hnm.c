#include "hnm.h"


/**
* main- func
* @ac: int
* @av: char **
* Return: int
*/
int main(int ac, char **av)
{
	int fd = 0;

	if (ac != 2)
	{
		printf("usage: ./hnm <filename>\n");
		return (EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	display_content(fd);
	/* end */
	close(fd);
	return (EXIT_SUCCESS);
}


/**
* elf_handler- func
* @fd: int
* Return: void
*/
void elf_handler(int fd)
{
	(void)fd;
}



/**
* display_content-	displays the content of the file, the code was used to 
* 									understand the how the data was stored.
* @fd: int
* Return: void
*/
void display_content(int fd)
{
	Elf64_Ehdr eheader;
	Elf64_Shdr sheader;
	char tab[1], *symtab = NULL, *symtab2 = NULL;
	Elf64_Off i = 0, j = 0, k = 0;
	off_t cur, cur2;
	int symtaboff = 0, index = 0, symoff, amount, x = 0;
	Elf64_Sym sym;

	printf("begin\n");
	while (read(fd, tab, 1))
		printf("%c", tab[0]);
	printf("\nend\n\n\n\n\n");

	lseek(fd, 0, SEEK_SET);
	read(fd, &eheader, sizeof(Elf64_Ehdr));
	printf("CLASS: %d\n", eheader.e_ident[4]);
	printf("SHOFF: %ld\n", eheader.e_shoff);
	printf("SHSTRNDX: %d\n", eheader.e_shstrndx);

	lseek(fd, eheader.e_shoff, SEEK_SET);
	while (read(fd, &sheader, sizeof(Elf64_Shdr)))
	{
		cur = lseek(fd, 0, SEEK_CUR);
		printf("-----		BEGIN  -%d  -%ld\n", index, cur);
		index++;
		printf("SH_NAME: %d\n", sheader.sh_name);
		printf("SH_TYPE: %d\n", sheader.sh_type);
		printf("SH_SIZE: %ld\n", sheader.sh_size);
		printf("SH_OFFSET: %ld\n", sheader.sh_offset);
		
		lseek(fd, sheader.sh_offset, SEEK_SET);
		if ((sheader.sh_type == 3) && (sheader.sh_name == 9))
		{
			cur2 = lseek(fd, 0, SEEK_CUR);
			symtab = malloc(sheader.sh_size);
			read(fd, symtab, sheader.sh_size);
			lseek(fd, cur2, SEEK_SET);
		}
		for (i = 0; i < sheader.sh_size; i++)
		{
			read(fd, tab, 1);
			if (sheader.sh_type == 3)
				if (tab[0] < 12)
					printf(".");
				else
				printf("%c", tab[0]);
			else
				printf("%c", tab[0]);
		}
		lseek(fd, cur, SEEK_SET);
		printf("\n-----		END\n\n");
	}
	printf("symtab\n%s\n%s\n", symtab+1, symtab+9);
	free(symtab);

	printf("shstrndx: %d\n", eheader.e_shstrndx);
	printf("shentsize: %d\n", eheader.e_shentsize);
	symtaboff = eheader.e_shoff + eheader.e_shstrndx * eheader.e_shentsize;
	printf("symtaboff: %d\n", symtaboff);
	lseek(fd, symtaboff, SEEK_SET);
	read(fd, &sheader, sizeof(Elf64_Shdr));
	printf("SH_NAME: %d\n", sheader.sh_name);
	printf("SH_TYPE: %d\n", sheader.sh_type);
	printf("SH_SIZE: %ld\n", sheader.sh_size);
	printf("SH_OFFSET: %ld\n", sheader.sh_offset);
	lseek(fd, sheader.sh_offset, SEEK_SET);
	symtab2 = malloc(sheader.sh_size);
	read(fd, symtab2, sheader.sh_size);
	for (; j < sheader.sh_size; j++)
		if (symtab2[j] < 12)
			printf("./");
		else
			printf("%c", symtab2[j]);
	printf("\n");
	free(symtab2);

	printf("\nlooping, searching for symtab -> %d\n", SHT_SYMTAB);
	symtab2 = malloc(sheader.sh_size);
	for (k = 0; k < eheader.e_shnum; k++)
	{
		symtaboff = eheader.e_shoff + k * eheader.e_shentsize;
		lseek(fd, symtaboff, SEEK_SET);
		read(fd, &sheader, sizeof(Elf64_Shdr));
		if (sheader.sh_type == SHT_SYMTAB)
		{
			printf("SH_NAME: %d\n", sheader.sh_name);
			printf("SH_TYPE: %d\n", sheader.sh_type);
			printf("SH_SIZE: %ld\n", sheader.sh_size);
			printf("SH_OFFSET: %ld\n", sheader.sh_offset);
			lseek(fd, sheader.sh_offset, SEEK_SET);
			read(fd, symtab2, sheader.sh_size);
			for (j = 0; j < sheader.sh_size; j++)
				printf("%c", symtab2[j]);
			symoff = sheader.sh_size;
			amount = sheader.sh_size / sizeof(Elf64_Sym);
			printf("\namount: %d\n", amount);
		}
	}

	printf("Symbols\n");
	lseek(fd, symoff, SEEK_SET);
	for (; x < amount; x++)
	{
		read(fd, &sym, sizeof(Elf64_Sym));
		if (sym.st_name != 0)
		{
			printf("%d BEGIN\n", x);
			printf("NAME: %d\n", sym.st_name);
			printf("INFO: %d\n", sym.st_info);
			printf("OTHER: %d\n", sym.st_other);
			printf("SHNDX: %d\n", sym.st_shndx);
			printf("VALUE: %ld\n", sym.st_value);
			printf("SIZE: %ld\n", sym.st_size);
			printf("%d END\n\n", x);
		}
	}
	free(symtab2);
}
