#include "readelf.h"



/**
 * p_osabi - func
 * @data: data_t *
 */
void p_osabi(data_t *data)
{
	printf("  OS/ABI:                            ");
	if (data->e_ident[EI_OSABI] == ELFOSABI_SYSV)
		printf("UNIX - System V\n");
	else if (data->e_ident[EI_OSABI] == ELFOSABI_HPUX)
		printf("UNIX - HP-UX\n");
	else if (data->e_ident[EI_OSABI] == ELFOSABI_NETBSD)
		printf("UNIX - NetBSD\n");
	else if (data->e_ident[EI_OSABI] == ELFOSABI_LINUX)
		printf("UNIX - Linux\n");
	else if (data->e_ident[EI_OSABI] == ELFOSABI_SOLARIS)
		printf("UNIX - Solaris\n");
	else if (data->e_ident[EI_OSABI] == ELFOSABI_IRIX)
		printf("UNIX - IRIX\n");
	else if (data->e_ident[EI_OSABI] == ELFOSABI_FREEBSD)
		printf("UNIX - FreeBSD\n");
	else if (data->e_ident[EI_OSABI] == ELFOSABI_TRU64)
		printf("UNIX - TRU64\n");
	else if (data->e_ident[EI_OSABI] == ELFOSABI_ARM)
		printf("UNIX - ARM\n");
	else if (data->e_ident[EI_OSABI] == ELFOSABI_STANDALONE)
		printf("UNIX - Stand-alone (embedded)\n");
	else
		printf("<unknown: %x>\n", data->e_ident[EI_OSABI]);
}


/**
 * p_abiv - func
 * @data: data_t *
 */
void p_abiv(data_t *data)
{
	printf("  ABI Version:                       %d\n"
		, data->e_ident[EI_ABIVERSION]);
}


/**
 * p_type - func
 * @data: data_t *
 * @type: int
 */
void p_type(data_t *data, int type)
{
	(void)data;
	printf("  Type:                              ");
	if (type == ET_NONE)
		printf("NONE (Unknown type)\n");
	else if (type == ET_REL)
		printf("REL (Relocatable file)\n");
	else if (type == ET_EXEC)
		printf("EXEC (Executable file)\n");
	else if (type == ET_DYN)
		printf("DYN (Position-Independent Executable file)\n");
	else if (type == ET_CORE)
		printf("CORE (Core file)\n");
}


/**
 * p_machine - func
 * @data: data_t *
 * @machine: int
 */
void p_machine(data_t *data, int machine)
{
	(void)data;
	printf("  Machine:                           ");
	if (machine == EV_NONE)
		printf("An unknown machine\n");
	else if (machine == EM_M32)
		printf("AT&T WE 32100\n");
	else if (machine == EM_SPARC)
		printf("Sparc\n");
	else if (machine == EM_386)
		printf("Intel 80386\n");
	else if (machine == EM_68K)
		printf("Motorola 68000\n");
	else if (machine == EM_88K)
		printf("Motorola 88000\n");
	else if (machine == EM_860)
		printf("Intel 80860\n");
	else if (machine == EM_MIPS)
		printf("MIPS RS3000 (big-endian only)\n");
	else if (machine == EM_PARISC)
		printf("HP/PA\n");
	else if (machine == EM_SPARC32PLUS)
		printf("SPARC with enhanced instruction set\n");
	else if (machine == EM_PPC)
		printf("PowerPC\n");
	else if (machine == EM_PPC64)
		printf("PowerPC 64-bit\n");
	else if (machine == EM_S390)
		printf("IBM S/390\n");
	else if (machine == EM_ARM)
		printf("Advanced RISC Machines\n");
	else if (machine == EM_SH)
		printf("Renesas SuperH\n");
	else if (machine == EM_SPARCV9)
		printf("SPARC v9 64-bit\n");
	else if (machine == EM_IA_64)
		printf("Intel Itanium\n");
	else if (machine == EM_X86_64)
		printf("AMD x86-64\n");
	else if (machine == EM_VAX)
		printf("DEC Vax\n");
}


/**
 * p_version - func
 * @version: int
 */
void p_version(int version)
{
	printf("  Version:                           0x%x\n", version);
}
