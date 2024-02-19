.section .text
# void extract_token(char* input, char* token, int* output)
# rdi - char* input
# rsi - char* token
# rdx - int* output
# TOKEN:VALUE# (...)
.global extract_token

extract_token:
	movl $0, (%rdx) # *output = 0
	cmpb $0, (%rdi) # *input == '\0'
	je .end_verification;
	movb (%rsi), %cl
	cmpb %cl, (%rdi) # *input == *token
	je .cmp_second_char
	jmp .loop_until_token

.cmp_second_char:
	addq $1, %rdi # input++
	addq $1, %rsi # token++
	movb (%rsi), %cl
	cmpb %cl, (%rdi) # *input == *token
	je .loop_until_value;
	subq $1, %rsi # token--
	jmp .loop_until_token;

.loop_until_token: # go until value is #
	addq $1, %rdi # offset 1 byte
	movb (%rdi), %cl
	cmpb $0, %cl # *input == 0
	je .end_verification;
	cmpb $'#', %cl # *input != '#'
	jne .loop_until_token
	jmp .get_token

.loop_until_value: # go until value is :
	addq $1, %rdi # input++
	cmpb $0, (%rdi) # *input == '\0'
	je .end_verification
	cmpb $':', (%rdi) # *input != ':'
	jne .loop_until_value
	jmp .get_value

.get_token:
	addq $1, %rdi # input++
	jmp extract_token # goto extract_token

.get_value:
	addq $1, %rdi # input++
	cmpb $0, (%rdi) # *input == 0
	je .end_verification

	cmpb $'.', (%rdi) # *input == '.'
	je .get_value # go to next input address

	cmpb $'9', (%rdi) # *input > '9'
	jg .end_verification

	cmpb $'0', (%rdi) # *input < '0'
	jl .end_verification

	movl (%rdx), %ecx # ecx = *output
	imull $10, %ecx # ecx = ecx * 10

	movl %ecx, (%rdx) # *output = ecx

	movb (%rdi), %cl # al = *input
	subb $'0', %cl # *input - '0' this sh*t wasted me 3 hours
	movsbl %cl, %ecx

	addl %ecx, (%rdx) # *output = *output + *input

	## new try with shifts and load effective address
	#movl (%rdx), %eax
	## how to get eax = eax * 10
	#leal (%rax, %rax, 2), %eax # eax=eax*5
	#shlq $1, %rax # eax=eax*2

	#subb $'0', (%rdi)
	#movzbl (%rdi), %ecx
	#addl %ecx, %eax
	#movl %eax, (%rdx)

	jmp .get_value

.end_verification:
	movl $0, %eax
	cmpl $0, (%rdx)
	je .end
	movl $1, %eax

.end:
	ret
