
.data
int_fmt_scanf:
    .string "%d"
int_fmt_printf:
    .string "%d\n"

.text
    .globl main

fact:
    # input in rax, output in rax
    cmp $0, %rax
    jz zero
    push %rax
    dec %rax
    call fact
    pop %rbx
    imul %rbx, %rax
    ret
zero:
    mov $1, %rax
    ret

main:
    push %rbp

    # we call scanf
    pushq $0
    leaq (%rsp), %rsi
    leaq int_fmt_scanf(%rip), %rdi
    mov $0, %rax
    call scanf

    popq %rax
    call fact
    mov %rax, %rsi

    # we call printf
    leaq int_fmt_printf(%rip), %rdi
    mov $0, %rax
    call printf

    xor %rax, %rax
    pop %rbp
    ret
