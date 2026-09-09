.data
hello:
    .string "Hello, world!\n"

.text
    .globl _start

_start:
    mov $10, %r8
boucle:
    mov $1, %rax
    mov $1, %rdi
    mov $14, %rdx
    lea hello(%rip), %rsi
    syscall
    dec %r8
    jnz boucle
    mov $60, %rax
    mov $0, %rdi
    syscall

.section .note.GNU-stack
