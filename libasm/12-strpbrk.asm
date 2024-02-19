BITS 64


global asm_strpbrk

section .text
	asm_strpbrk:
		mov		r8, 0

	cmp_str:
		movzx	rax, byte [rdi + r8]
		cmp		rax, 0
		jz		ret_null
		mov		r9, 0

	cmp_eq:
		movzx	rbx, byte [rsi + r9]
		cmp		rbx, 0
		jz		continue
		cmp		rax, rbx
		je		return
		inc		r9
		jmp		cmp_eq

	continue:
		inc		r8
		jmp		cmp_str

	ret_null:
		mov		rax, 0
		ret

	return:
		lea		rax, [rdi + r8]
		ret
