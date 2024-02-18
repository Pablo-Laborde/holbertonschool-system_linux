BITS 64


global asm_memcpy


section .text
	asm_memcpy:
		mov		rcx, 0

	cpy_char:
		cmp		rcx, rdx
		je		return
		mov		bl, byte [rsi + rcx]
		cmp		bl, 0
		jz		return
		cmp		byte [rdi + rcx], 0
		jz		return
		mov		byte [rdi + rcx], bl
		inc		rcx
		jmp		cpy_char

	return:
		mov		rax, rdi
		ret
