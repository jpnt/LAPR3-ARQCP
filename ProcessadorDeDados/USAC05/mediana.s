.extern sort
.section .text
.global mediana

mediana:
	call sort
	shr $1, %esi
	movl (%rdi, %rsi, 4), %eax
	ret
