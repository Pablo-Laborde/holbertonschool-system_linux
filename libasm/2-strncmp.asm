BITS 64


section .text
	global asm_strncmp

asm_strncmp:
		mov		r8, 0			; initialize counter to 0
		mov		r9, 0			;	save string 1
		mov		r10, 0		;	save string 2
		mov		r11, 0		; amount of bytes compared

	cmp_str:
		cmp		rdx, r11
		je		end
		movzx	r9, byte [rdi]
		movzx	r10, byte [rsi]
		add		r11, 1
		cmp		r9, r10
		jne		dif
		cmp		r9, 0
		je		end
		inc		rdi
		inc		rsi
		jmp		cmp_str

	dif:
		add		r8, r9
		sub		r8, r10
		jmp		end

	end:
		mov 	rax, r8	; return counter
		ret

