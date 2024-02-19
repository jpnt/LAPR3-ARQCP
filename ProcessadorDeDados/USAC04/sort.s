.section .text
.global sort # sort(int * arr, int length)
	     #         rdi        esi

sort: # i = ecx, j = edx, temp = r9d
	xor %ecx, %ecx # i = ecx = 0

.outer_loop:
	movl %esi, %r9d
	subl $1, %r9d # length-1
	cmpl %r9d, %ecx # i >= length-1
	jge .end

	xor %edx, %edx # j = edx = 0

.inner_loop:
	movl %esi, %r9d
	subl %ecx, %r9d # length-i
	decl %r9d # r9d = length-i-1
	cmpl %r9d, %edx # j >= length-i-1
	jge .outer_increment

	movl (%rdi, %rdx, 4), %r9d # r9d = *(arr+j)
	movl 4(%rdi, %rdx, 4), %r10d # r10d = *(arr+j+1)
	cmpl %r10d, %r9d # *(arr+j) > *(arr+j+1)
	jg .swap

	incl %edx # j++
	jmp .inner_loop

.outer_increment:
	incl %ecx
	jmp .outer_loop

.swap:
	movl 4(%rdi, %rdx, 4), %eax
	movl %r9d, 4(%rdi, %rdx, 4)
	movl %eax, (%rdi, %rdx, 4)
	jmp .inner_loop

.end:
	ret

