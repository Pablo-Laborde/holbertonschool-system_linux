#include "readelf.h"



/**
 * p_phentsize - func
 * @phentsize: int
 */
void p_phentsize(int phentsize)
{
	printf("  Size of program headers:           %d (bytes)\n"
				, phentsize);
}


/**
 * p_phnum - func
 * @phnum: int
 */
void p_phnum(int phnum)
{
	printf("  Number of program headers:         %d\n", phnum);
}


/**
 * p_shentsize - func
 * @shentsize: int
 */
void p_shentsize(int shentsize)
{
	printf("  Size of section headers:           %d (bytes)\n"
				, shentsize);
}


/**
 * p_shnum - func
 * @shnum: int
 */
void p_shnum(int shnum)
{
	printf("  Number of section headers:         %d\n", shnum);
}


/**
 * p_shstrndx - func
 * @shstrndx: int
 */
void p_shstrndx(int shstrndx)
{
	printf("  Section header string table index: %d\n", shstrndx);
}
