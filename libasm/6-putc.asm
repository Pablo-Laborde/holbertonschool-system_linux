BITS 64


global asm_putc

section .text
	asm_putc:
		push	rdi
		mov		rdx, 1		;	amount of char
		mov		rsi, rsp	;	pointer to output
		mov		rdi, 1		; file destriptor to std_out
		mov		rax, 1		; write instruction
		syscall
		pop		rdi
		ret