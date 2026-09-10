.data

int_fmt_scanf:
    .string "%d"
int_fmt_printf:
    .string "%d\n"

.text
    .globl main

main:
    push %rbp

    # we call scanf
    pushq $0
    leaq (%rsp), %rsi
    leaq int_fmt_scanf(%rip), %rdi
    mov $0, %rax
    call scanf

    # we call printf
    popq %rsi  # result of scanf
    leaq int_fmt_printf(%rip), %rdi
    mov $0, %rax
    call printf

    xor %rax, %rax
    pop %rbp
    ret
