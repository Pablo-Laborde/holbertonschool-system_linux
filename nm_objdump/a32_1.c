#include "hnm.h"



/**
* abs_32 - func
* @sym: symbol
* Return: char
*/
char abs_32(Elf32_Sym *sym)
{
	char c = 0;

	if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
		c = ((sym->st_other == STV_DEFAULT) ||
				(sym->st_other == STV_PROTECTED)) ? 'A' : 'a';
	else
		c = (ELF32_ST_BIND(sym->st_info) == STB_GLOBAL) ? 'A' : 'a';
	return (c);
}


/**
* func_32 - func
* @sym: symbol
* Return: char
*/
char func_32(Elf32_Sym *sym)
{
	char c = 0;

	if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
		c = ((sym->st_other == STV_DEFAULT) ||
				(sym->st_other == STV_PROTECTED)) ? 'W' : 'w';
	else
		c = (ELF32_ST_BIND(sym->st_info) == STB_GLOBAL) ? 'T' : 't';
	return (c);
}


/**
* stt_common_32 - func
* @sym: symbol
* Return: char
*/
char stt_common_32(Elf32_Sym *sym)
{
	char c = 0;

	if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
		c = ((sym->st_other == STV_DEFAULT) ||
				(sym->st_other == STV_PROTECTED)) ? 'C' : 'c';
	else
		c = (ELF32_ST_BIND(sym->st_info) == STB_GLOBAL) ? 'C' : 'c';
	return (c);
}
