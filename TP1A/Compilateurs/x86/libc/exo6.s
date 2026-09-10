
.data
int_fmt_scanf:
    .string "%d"
int_fmt_printf:
    .string "%d\n"

.text
    .globl main

read_int:
    # output in rax
    push %rbp

    pushq $0
    leaq (%rsp), %rsi
    leaq int_fmt_scanf(%rip), %rdi
    mov $0, %rax
    call scanf
    popq %rax

    pop %rbp
    ret

modulo_r12:
# calcule %rax modulo %r12 et stocke le résultat dans %rdx
    mov %r12, %rbx
    xor %rdx, %rdx
    idiv %rbx
    ret

# FIXME: r11 seems to be always 2???
expo_rapide_modulo:
    # inputs in r10, r11 and r12
    # result in rax
    mov $1, %r13  # result
    test %r11, %r11
    jz fin_expo_rapide

boucle:
    # if b%2 != 0
    mov %r11, %rax
    mov $2, %rbx
    xor %rdx, %rdx
    idiv %rbx
    test %rdx, %rdx
    jz pair
# impair
# res = res*a mod c
    imul %r10, %r13
    #mov %r13, %rax
    #call modulo_r12
    #mov %rdx, %r13
pair:
# a = (a*a) mod c
    imul %r10, %r10
    #mov %r10, %rax
    #call modulo_r12
    #mov %rdx, %r10
# b /= 2
    shr %r11
    test %r11, %r11
    jnz boucle

fin_expo_rapide:
    mov %r13, %rax
    ret


main:
    push %rbp

    # we call scanf 3 times
    # r10 is a, r11 is b and r12 is c
    call read_int
    mov %rax, %r10
    call read_int
    mov %rax, %r11
    #call read_int
    #mov %rax, %r12

    call expo_rapide_modulo

    # we call printf
    mov %rax, %rsi
    leaq int_fmt_printf(%rip), %rdi
    mov $0, %rax
    call printf

    xor %rax, %rax
    pop %rbp
    ret
