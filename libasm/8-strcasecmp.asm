BITS 64

global asm_strcasecmp

section .text
	asm_strcasecmp:
		mov		r8, 0
		mov		r9, 0

	cmp_char:
		mov		r10, 0
		cmp		r8, 0
			jnz		return
		cmp		byte [rsi + r9], 0
			jz		ch_fsn
		cmp		byte [rdi + r9], 0
			jz		ch_ssn
		jmp		add_n_sub

	ch_fsn:
		cmp		byte [rdi + r9], 0
			jz		return
		movzx	rax, byte [rdi + r9]
		add		r8, rax
		jmp		return

	ch_ssn:
		cmp		byte [rsi + r9], 0
			jz		return
		movzx	rax, byte [rsi + r9]
		sub		r8, rax
		jmp		return

	add_n_sub:
		cmp		r10, 1
		jle		load_rax
		inc		r9
		jmp		cmp_char

	do_maths:
		cmp		r10, 0
		jz		add_maths
		jnz		sub_maths

	add_maths:
		cmp		rax, 65
		jl		add_any
		cmp		rax, 90
		jle		add_upper
		cmp		rax, 97
		jl		add_any
		cmp		rax, 122
		jle		add_lower
		jg		add_any

	sub_maths:
		cmp		rax, 65
		jl		sub_any
		cmp		rax, 90
		jle		sub_upper
		cmp		rax, 97
		jl		sub_any
		cmp		rax, 122
		jle		sub_lower
		jg		sub_any

	load_rax:
		cmp		r10, 0
		jz		load_rdi
		jnz		load_rsi

	load_rdi:
		movzx	rax, byte [rdi + r9]
		jmp		do_maths

	load_rsi:
		movzx	rax, byte [rsi + r9]
		jmp		do_maths

	next_char:
		inc		r10
		jmp		add_n_sub

	add_any:
		add		r8, rax
		jmp		next_char

	sub_any:
		sub		r8, rax
		jmp		next_char

	add_upper:
		add		r8, rax
		sub		r8, 65
		jmp		next_char

	sub_upper:
		sub		r8, rax
		add		r8, 65
		jmp		next_char

	add_lower:
		add		r8, rax
		sub		r8, 97
		jmp		next_char

	sub_lower:
		sub		r8, rax
		add		r8, 97
		jmp		next_char

	return:
		mov		rax, r8
		ret
