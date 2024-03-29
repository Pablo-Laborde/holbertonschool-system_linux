#include "readelf.h"


/**
* p_m- func
* @data: data_t *
* Return: void
*/
void p_m(data_t *data)
{
	char *str;

	/* Machine */
	if (data->e_machine == EM_NONE)
		str = "An unknown machine";
	else if (data->e_machine == EM_M32)
		str = "AT&T WE 32100";
	else if (data->e_machine == EM_SPARC)
		str = "Sun Microsystems SPARC";
	else if (data->e_machine == EM_386)
		str = "Intel 80386";
	else if (data->e_machine == EM_68K)
		str = "Motorola 68000";
	else if (data->e_machine == EM_88K)
		str = "Motorola 88000";
	else if (data->e_machine == EM_860)
		str = "Intel 80860";
	else if (data->e_machine == EM_MIPS)
		str = "MIPS RS3000 (big-endian only)";
	else if (data->e_machine == EM_PARISC)
		str = "HP/PA";
	else if (data->e_machine == EM_SPARC32PLUS)
		str = "SPARC with enhanced instruction set";
	else if (data->e_machine == EM_PPC)
		str = "PowerPC";
	else if (data->e_machine == EM_PPC64)
		str = "PowerPC 64-bit";
	else if (data->e_machine == EM_S390)
		str = "IBM S/390";
	else if (data->e_machine == EM_ARM)
		str = "Advanced RISC Machines";
	else if (data->e_machine == EM_SH)
		str = "Renesas SuperH";
	else if (data->e_machine == EM_SPARCV9)
		str = "SPARC v9 64-bit";
	else if (data->e_machine == EM_IA_64)
		str = "Intel Itanium";
	else if (data->e_machine == EM_X86_64)
		str = "AMD x86-64";
	else if (data->e_machine == EM_VAX)
		str = "DEC Vax";
	else
		str = "Unknown";
	printf("  Machine:                           %s\n", str);
}


/**
* p_many- func
* @data: data_t *
* Return: void
*/
void p_many(data_t *data)
{
	/* Version */
	printf("  Version:                           0x%d\n", data->e_version);

	/* Entry */
	printf("  Entry point address:               0x%lx\n", data->e_entry);

	/* PHOFF */
	printf("  Start of program headers:          %ld (bytes into the file)\n"
				, data->e_phoff);

	/* SHOFF */
	printf("  Start of section headers:          %ld (bytes into the file)\n"
				, data->e_shoff);

	/* Flags */
	printf("  Flags:                             0x%d\n", data->e_flags);

	/* Size of header */
	printf("  Size of this header:               %d (bytes)\n"
				, data->e_ehsize);

	/* Size of program headers */
	printf("  Size of program headers:           %d (bytes)\n"
				, data->e_phentsize);

	/* Number program headers */
	printf("  Number of program headers:         %d\n", data->e_phnum);

	/* Size of section headers */
	printf("  Size of section headers:           %d (bytes)\n"
				, data->e_shentsize);

	/* Number section headers */
	printf("  Number of section headers:         %d\n", data->e_shnum);

	/* Section header string table index */
	printf("  Section header string table index: %d\n", data->e_shstrndx);
}
