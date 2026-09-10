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

    popq %rax  # result of scanf
    mov %rax, %rsi

    # check parity
    xor %rdx, %rdx
    mov $2, %rbx
    idiv %rbx
    test %rdx, %rdx
    jnz impair

    mov %rax, %rsi  # n/2
    jmp print

impair:
    imul $3, %rsi
    add $1, %rsi

print:
    # we call printf
    leaq int_fmt_printf(%rip), %rdi
    mov $0, %rax
    call printf

    xor %rax, %rax
    pop %rbp
    ret
