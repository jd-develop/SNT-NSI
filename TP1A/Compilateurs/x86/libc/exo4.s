
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

    mov $1, %rsi
    popq %rax
    cmp $0, %rax
    jz print

boucle:
    imul %rax, %rsi
    dec %rax
    jnz boucle

print:
    # we call printf
    leaq int_fmt_printf(%rip), %rdi
    mov $0, %rax
    call printf

    xor %rax, %rax
    pop %rbp
    ret
