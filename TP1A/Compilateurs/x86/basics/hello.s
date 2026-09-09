.data

hello:
    .string "Hello world!\n"

.text
    .globl _start

_start:
    mov $1, %rax
    mov $1, %rdi
    mov $13, %rdx
    lea hello(%rip), %rsi
    syscall
    mov $60, %rax
    mov $0, %rdi
    syscall

.section .note.GNU-stack
