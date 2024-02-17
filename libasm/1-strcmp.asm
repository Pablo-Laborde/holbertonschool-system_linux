BITS 64

; export functions
	global asm_strcmp


section .text
	asm_strcmp:
		mov		r8, 0			; initialize counter to 0
		mov		r9, 0			;	save string 1
		mov		r10, 0		;	save string 2

	cmp_str:
		movzx	r9, byte [rdi]
		movzx	r10, byte [rsi]
		cmp		r9, r10
		jg		greater
		jl		lower
		cmp		r9, 0
		je		end
		inc		rdi
		inc		rsi
		jmp		cmp_str

	greater:
		mov		r8, 1
		jmp		end

	lower:
		mov		r8, -1
		jmp		end

	end:
		mov 	rax, r8	; return counter
		ret
