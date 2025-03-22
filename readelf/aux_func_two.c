#include "readelf.h"



/**
 * p_version - func
 * @entry: int
 */
void p_entry(int entry)
{
	printf("  Entry point address:               0x%lx\n", entry);
}


/**
 * p_phoff - func
 * @phoff: int
 */
void p_phoff(int phoff)
{
	printf("  Start of program headers:          %ld (bytes into file)\n"
				, phoff);
}


/**
 * p_shoff - func
 * @shoff: int
 */
void p_shoff(int shoff)
{
	printf("  Start of section headers:          %ld (bytes into file)\n"
				, shoff);
}


/**
 * p_flags - func
 * @flags: int
 */
void p_flags(int flags)
{
	printf("  Flags:                             %x\n", flags);
}


/**
 * p_ehsize - func
 * @ehsize: int
 */
void p_ehsize(int ehsize)
{
	printf("  Size of this header:               %d (bytes)\n"
				, ehsize);
}
