.section .text
.global enqueue_value

# void enqueue_value(int* array, int length, int* read, int* write, int value)
# rdi rsi rdx rcx r8

enqueue_value:
        movq    %rdi, %rax # rax = array
        movq    %rdx, %rdi # rdi = read
        movslq  (%rcx), %rdx # rdx = *write
        movl    %r8d, (%rax,%rdx,4) # *(array + *write) = value
        movl    (%rcx), %eax # eax = *write
        addl    $1, %eax # *write + 1
        cltd    # long to double edx:eax
        idivl   %esi # eax / esi
        movl    %edx, (%rcx) # remainder is in edx, copy it to *write
        movl    (%rdi), %eax # eax = *read
        cmpl    %edx, %eax # if (*read == *write)
        je      .increment # increment(*read, length)
        ret     # else return
.increment:
        addl    $1, %eax # *read + 1
        cltd    # extend to edx:eax
        idivl   %esi # eax / esi
        movl    %edx, (%rdi) # copy remainder to *array
        ret
