BITS 64

section .data
	msg db "Hello World", 0xa, 0

section .text
	global _start

_start:
	mov		edx, 13
	mov		ecx, msg
	mov		ebx, 1
	mov		eax, 4
	int		0x80

	mov		eax, 1	; set exit_status
	mov		ebx, 0	; exit 0
	int		0x80		; call Kernel

; nasm -f elf64 write.asm
; ld write.o
