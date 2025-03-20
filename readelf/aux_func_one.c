#include "readelf.h"


/**
 * p_osabi - func
 * @data: data_t *
 */
void p_osabi(data_t *data)
{
	char *str = NULL;

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