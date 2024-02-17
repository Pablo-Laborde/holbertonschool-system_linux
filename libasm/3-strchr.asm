BITS 64


section .text
	global asm_strchr

asm_strchr:
	mov		r8, 0h
	mov		r9, rdi
	mov		r10, rsi

cmp_chars:
	cmp		byte [r9 + r8], r10b
	je		ret_add
	cmp		byte [r9 + r8], 0h
	je		null
	inc		r8
	jmp		cmp_chars

	ret_add:
		lea		rax, [r9 + r8]
		jmp		return

	null:
		mov		rax, 0

	return:
		ret
