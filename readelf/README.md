readelf readme


to fix:
	In Elf32_Ehdr and Elf64_Ehdr, fields like e_shoff (type Elf32_Off or Elf64_Off) are not handled correctly for endianness.
	Should use bswap32 for 32-bit ELF files and bswap64 for 64-bit ELF files, depending on e_ident[EI_CLASS] and e_ident[EI_DATA].
