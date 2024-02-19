BITS 64


global asm_strcspn

section .text
	asm_strcspn:
		mov		r8, 0

	cmp_fs:
		movzx	rax, byte [rdi + r8]
		cmp		rax, 0
		jz		return
		mov		r9, 0

	cmp_ss:
		movzx	rbx, byte [rsi + r9]
		cmp		rbx, 0
		jz		continue
		cmp		rax, rbx
		je		return
		inc		r9
		jmp		cmp_ss

	continue:
		inc		r8
		jmp		cmp_fs

	return:
		mov		rax, r8
		ret
