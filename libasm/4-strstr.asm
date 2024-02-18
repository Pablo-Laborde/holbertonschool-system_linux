BITS 64


section .text
	global asm_strstr

asm_strstr:
	mov		r8, rdi
	mov		r9, rsi
	mov		r10, 0
	mov		r11, 0

ch_snull:
	cmp		byte [r9], 0
	jnz		ch_both_null
	jz		ret_str

ch_both_null:
	cmp		byte [r8], 0
	jz		ret_null
	jnz		ch_str

ch_str:
	mov		r12, 0
	add		r12, r10
	add		r12, r11
	mov		al, byte [r8 + r12]
	mov		bl, byte [r9 + r11]
	cmp		bl, 0
	jz		ret_str
	cmp		al, 0
	jz		ret_null
	cmp		al, bl
	jz		ch_next
	jnz		adv_in_str

adv_in_str:
	inc		r10
	mov		r11, 0
	jmp		ch_str

ch_next:
	inc		r11
	jmp		ch_str

ret_str:
	lea		rax, [r8 + r10]
	ret

ret_null:
	mov		rax, 0
	ret
