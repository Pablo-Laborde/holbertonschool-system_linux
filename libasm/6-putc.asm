BITS 64


global asm_putc

section .text
	asm_putc:
		mov		rax, 1		; write instruction
		mov		rdx, 1		;	amount of char
		mov		rsi, rdi	;	pointer to output
		mov		rdi, 1		; file destriptor to std_out
		ret
