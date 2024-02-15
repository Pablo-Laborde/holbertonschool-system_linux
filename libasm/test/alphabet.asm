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

	add		rsp, -1
	mov		byte [rsp], 97


set_a:
	mov		rdx, 1
	mov		rsi, rsp
	mov		rdi, 1
	mov		rax, 1


print_loop:
	syscall
	inc		byte [rsp]
	cmp		byte [rsp], 122
	jle		print_loop


end:
	add		rsp, 1

	pop		rdx
	pop		rsi
	pop		rdi
	pop		rax

	mov rsp, rbp
	pop rbp

	ret
