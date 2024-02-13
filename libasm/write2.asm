BITS 64

global print_alphabet

section .text

print_alphabet:
	push	rbp
	mov		rbp, rsp

	push	rax
	push	rdi
	push	rsi
	push	rdx

	add		rsp, -2
	mov		byte [rsp], 97
	mov		byte [rsp + 1], 98

	mov		rdx, 2
	mov		rsi, rsp
	mov		rdi, 1
	mov		rax, 1
	syscall

	add		rsp, 1

	pop		rdx
	pop		rsi
	pop		rdi
	pop		rax

	mov rsp, rbp
	pop rbp

	ret
