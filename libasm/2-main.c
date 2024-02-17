#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "libasm.h"

#define N	strlen(S1)

#define S1  "Holberton School"
#define S2  ""
#define S3  "Holberton Socool"
#define S4	"Holberton"

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    assert(strncmp(S1, S3, 1) == asm_strncmp(S1, S3, 1));
    assert(strncmp(S1, S3, 11) == asm_strncmp(S1, S3, 11));
		assert(strncmp(S1, S2, 11) == asm_strncmp(S1, S2, 11));
    assert(strncmp(S1, S3, 15) == asm_strncmp(S1, S3, 15));
		assert(strncmp(S1, S4, 16) == asm_strncmp(S1, S4, 16));
		assert(strncmp(S1, S2, N) == asm_strncmp(S1, S2, N));
		assert(strncmp("Holberton School", "Holberton", strlen("Holberton School")) == asm_strncmp("Holberton School", "Holberton", strlen("Holberton School")));
		assert(strncmp("Holberton", "Holberton School", strlen("Holberton School")) == asm_strncmp("Holberton", "Holberton School", strlen("Holberton School")));

    printf("All good!\n");
    return (EXIT_SUCCESS);
}
