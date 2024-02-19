.section .text
.global move_num_vec

move_num_vec:
	movq	%rdi, %rcx	# Copy array to rcx (source pointer)
	cmpl	%esi, %r8d	# Compare num with length
	jg	.exit		# num > length, exit
	testl	%r8d, %r8d	# if num is <= 0
	jle	.exit		# exit
	leal	-1(%r8), %edi	# calculate num - 1, store in edi
	movl	(%rdx), %eax	# copy *read into eax
	leaq	4(%r9,%rdi,4), %r8 # destination address for vec, store in r8
	xorl	%edi, %edi	# initialize i = 0
.copy_nums:
	cltq				# i to 64 bits
	movl	(%rcx,%rax,4), %eax	# array[*read] into eax
	movl	%eax, (%r9)		# vec[i] = array[*read]
	movslq	(%rdx), %rax		# *read into rax
	movl	$0, (%rcx,%rax,4)	# clear array[*read]
	movl	(%rdx), %eax
	addl	$1, %eax		# Increment *read
	cmpl	%eax, %esi		# Compare *read with num
	cmovle	%edi, %eax		# *read <= num, set eax = 0
	addq	$4, %r9			# Move to the next position in vec
	movl	%eax, (%rdx)		# store updated *read
	cmpq	%r8, %r9		# Compare vec end with current position
	jne	.copy_nums		# continue if not at the end
	movl	$1, %eax		# return value to 1
	ret
.exit:
	xorl	%eax, %eax		# return value to 0
	ret
