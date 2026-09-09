# Prints the char stored in r8

.text
    .globl _start
_start:
    mov $0x4c, %r8  # capital L

    mov %r8, -4(%rsp)
    movb $10, -3(%rsp)
    lea -4(%rsp), %rsi
    mov $1, %rax
    mov $1, %rdi
    mov $2, %rdx
    syscall

    mov $60, %rax
    mov $0, %rdi
    syscall
