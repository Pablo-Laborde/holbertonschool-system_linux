BITS 64

global swap

section .text

swap:
	mov		r8d, dword [rax]
	mov		r9d, dword [rsi]
	mov		dword [rax], r9d
	mov		dword [rsi], r8d
	ret
