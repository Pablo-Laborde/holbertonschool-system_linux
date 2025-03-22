#include "readelf.h"



/**
* hexamaker- func
* @n: int
* @c: char *
* Return: void
*/
void hexamaker(int n, char *c)
{
	char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
									'8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

	c[1] = hex[n % 16];
	c[0] = hex[n / 16];
}


/**
 * p_magic - func
 * @data: data_t *
 */
void p_magic(data_t *data)
{
	int i = 0;
	char hexa[3];

	hexa[2] = '\0';
	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
	{
		hexamaker(data->e_ident[i], hexa);
		printf("%s", hexa);
		printf(" ");
	}
	printf("\n");
}


/**
 * p_class - func
 * @class: int
 */
void p_class(int class)
{
	printf("  Class:                             ");
	if (class == ELFCLASS32)
		printf("ELF32\n");
	else if (class == ELFCLASS64)
		printf("ELF64\n");
}


/**
 * p_data - func
 * @data: int
 */
void p_data(int data)
{
	printf("  Data:                              ");
	if (data == ELFDATANONE)
		printf("Unknown data format\n");
	else if (data == ELFDATA2LSB)
		printf("2's complement, little endian\n");
	else if (data == ELFDATA2MSB)
		printf("2's complement, big endian\n");
}


/**
 * p_ver - func
 * @ver: int
 */
void p_ver(int ver)
{
	printf("  Version:                           %d ", ver);
	if (ver == EV_NONE)
		printf("Invalid version\n");
	else if (ver == EV_CURRENT)
		printf("(current)\n");
}
