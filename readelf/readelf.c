#include "readelf.h"


/**
* main- function
* @ac: int
* @av: char **
* Return: int
*/
int main(int ac, char **av)
{
	int fd = 0;
	data_t data;

	if (ac != 2)
	{
		printf("Usage: ./0-hreadelf <filename>\n");
		exit(EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);

	def_data(fd, &data);
	header_printer(&data);

	close(fd);
	exit(EXIT_SUCCESS);
}


/**
* header_printer- function
* @data: data_t *
* Return: void
*/
void header_printer(data_t *data)
{
	printf("ELF Header:\n");
	p_mc(data);
	p_dv(data);
	p_oa(data);
	p_at(data);
	p_m(data);
	p_many(data);
}
