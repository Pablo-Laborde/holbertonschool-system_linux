BITS 64


section .text
	global asm_strlen


asm_strlen:

	push	rbp
	mov		rbp, rsp

	;mov		rsi, rax
	mov		r8, 0h

len:
	cmp		byte [rdi], 0
	je		end
	inc		rdi
	inc		r8
	jne		len


end:
	mov		rax, r8

	mov		rsp, rbp
	pop		rbp

	ret
