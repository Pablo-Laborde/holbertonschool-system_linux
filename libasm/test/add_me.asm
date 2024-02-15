BITS 64

global add_me

section .text

add_me:
	add		rax, rsi
	ret
