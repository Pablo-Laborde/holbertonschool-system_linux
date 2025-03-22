#include "readelf.h"


/**
 * p_osabi - func
 * @data: data_t *
 * @ibe: endianess
 */
void p_osabi(data_t *data, int ibe)
{
	char *str = NULL;

	(void) ibe;
	/* OS/ABI */
	switch (data->e_ident[EI_OSABI]) {
		case ELFOSABI_SYSV:
			str = "UNIX - System V";
			break;
		case ELFOSABI_HPUX:
			str = "UNIX - HP-UX";
			break;
		case ELFOSABI_NETBSD:
			str = "UNIX - NetBSD";
			break;
		case ELFOSABI_LINUX:
			str = "UNIX - Linux";
			break;
		case ELFOSABI_SOLARIS:
			str = "UNIX - Solaris";
			break;
		case ELFOSABI_IRIX:
			str = "UNIX - IRIX";
			break;
		case ELFOSABI_FREEBSD:
			str = "UNIX - FreeBSD";
			break;
		case ELFOSABI_TRU64:
			str = "UNIX - TRU64";
			break;
		case ELFOSABI_ARM:
			str = "UNIX - ARM";
			break;
		case ELFOSABI_STANDALONE:
			str = "UNIX - Stand-alone (embedded)";
			break;
		default:
			printf("  OS/ABI:                            <unknown: %x>\n",
				data->e_ident[EI_OSABI]);
			return;
	}
	printf("  OS/ABI:                            %s\n", str);
}


/**
 * p_type - func
 * @data: data_t *
 * @ibe: endianess
 */
void p_type(data_t *data, int ibe)
{
	char *str = NULL;
	int type = (ibe == ELFDATA2MSB) ? bswap_16(data->e_type) : data->e_type;

	switch (type) {
		case ET_NONE:
			str = "NONE (Unknown type)";
			break;
		case ET_REL:
			str = "REL (Relocatable file)";
			break;
		case ET_EXEC:
			str = "EXEC (Executable file)";
			break;
		case ET_DYN:
			str = "DYN (Position-Independent Executable file)";
			break;
		case ET_CORE:
			str = "CORE (Core file)";
			break;
	}
	printf("  Type:                              %s\n", str);
}
