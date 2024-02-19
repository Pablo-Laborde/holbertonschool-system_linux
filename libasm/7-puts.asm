BITS 64

global asm_puts
extern asm_strlen

section .text
	asm_puts:
		lea r8, [rdi]
		push	rbp
		mov		rbp, rsp

		mov		rax, rdi
		call	asm_strlen

		mov		rsp, rbp
		pop 	rbp

		push r8

		mov		rdx, rax		;	amount of char
		mov		rsi, rsp	;	pointer to output
		mov		rdi, 1		; file destriptor to std_out
		mov		rax, 1		; write instruction
		syscall
		mov		rax, rdx
		pop r8
		ret
