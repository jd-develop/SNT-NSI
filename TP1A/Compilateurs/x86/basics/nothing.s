.globl _start

_start:
    mov $60, %rax
    mov $0, %rdi
    syscall

.section .note.GNU-stack
